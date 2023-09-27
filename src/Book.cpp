#include "Book.hpp"
#include "Heap.hpp"

Book::Book() : ask_tree(Heap(1000)), bid_tree(Heap(1000)), orders(std::unordered_map<int, Order*>()),
               limits(std::unordered_map<int, Limit*>()), next_order_id(0), best_bid(-1), best_ask(-1)
{}

void Book::queue_order(Order *order) {
    int price = order->limit_price;

    // Check if limit at price already exists
    if (limits.find(price) != limits.end()) {
        if (limits[price]->head_order == nullptr) {
            limits[price]->head_order = limits[price]->tail_order = order;
        } else {
            limits[price]->tail_order->next_order = order;
            order->prev_order = limits[price]->tail_order;
            limits[price]->tail_order = order;
        }
    } else {
        // Create new limit and insert into heap
        Limit *new_limit = new Limit(price);
        new_limit->head_order = new_limit->tail_order = order;
        if (order->is_buy_side) {
            bid_tree.insert<bid>(new_limit);
        } else {
            ask_tree.insert<ask>(new_limit);
        }
        limits[price] = new_limit;
    }
    limits[price]->total_volume += order->volume;
    limits[price]->size += 1;
    // Set parent limit object of order
    order->parent_limit = limits[price];
}

int Book::execute_buy(int volume, int price) {
    int remaining_volume = volume;
    std::cout << "Executing buy for " << volume << " @" << price << std::endl;
    while (remaining_volume > 0 && !ask_tree.is_empty()
           && ask_tree.peek_root()->limit_price <= price) {
        Order *seller = ask_tree.peek_root()->head_order;
        int trade_price = std::min(price, seller->limit_price);
        int trade_volume = std::min(remaining_volume, seller->volume);
        seller->volume -= trade_volume;
        seller->parent_limit->total_volume -= trade_volume;
        remaining_volume -= trade_volume;
        std::cout << "Made buy for " << trade_volume << " @" << trade_price << std::endl;

        if (seller->volume == 0) {
            remove_order(seller->id);
        }

    }
    return remaining_volume;
}

int Book::execute_sell(int volume, int price) {
    int remaining_volume = volume;
    std::cout << "Executing sell for " << volume << " @" << price << std::endl;
    while (remaining_volume > 0 && !bid_tree.is_empty()
           && bid_tree.peek_root()->limit_price >= price) {
        Order *buyer = bid_tree.peek_root()->head_order;
        int trade_price = std::min(price, buyer->limit_price);
        int trade_volume = std::min(remaining_volume, buyer->volume);
        buyer->volume -= trade_volume;
        buyer->parent_limit->total_volume -= trade_volume;
        remaining_volume -= trade_volume;
        std::cout << "Made sale for " << trade_volume << " @" << trade_price << std::endl;
        std::cout << "Remaining volume: " << remaining_volume << std::endl;
        if (buyer->volume == 0) {
            remove_order(buyer->id);
        }

    }

    return remaining_volume;
}

int Book::place_order(bool is_buy_side, int volume, int price) {

    std::scoped_lock lock {write_m};

    // TODO: Generate entry_time
    const unsigned int new_order_id = next_order_id;

    int remaining_volume = volume;

    if (is_buy_side) {
        remaining_volume = execute_buy(remaining_volume, price);
    } else {
        remaining_volume = execute_sell(remaining_volume, price);
    }

    // Check if order was fully executed
    if (remaining_volume == 0) {

        if (is_buy_side) {
            update_best_ask();
        } else {
            update_best_bid();
        }
        
        return volume;
    }
    // Create the order
    Order *new_order = new Order(new_order_id, is_buy_side, remaining_volume, price);

    // Handle limit creation / insertion
    queue_order(new_order);

    // Insert new order into orders map
    orders[new_order_id] = new_order;

    next_order_id++;
    
    if (is_buy_side) {
        update_best_bid();
    } else {
        update_best_ask();
    }
    return volume - remaining_volume;
}

int Book::remove_order(int order_id) {
    if (orders.find(order_id) == orders.end()) {
        return -1;
    }
    // If not the only order at limit, just remove from LL & orders dict
    Order *order = orders[order_id];
    Limit *order_limit = order->parent_limit;
    int limit_price = order_limit->limit_price;
    bool is_buy_side = order->is_buy_side;
    // Move to limit.cpp
    if (order_limit->get_size() > 1) {
        // Remove from limit LL
        if (order_limit->head_order == order) {
            order_limit->head_order = order->next_order;
            order_limit->head_order->prev_order = nullptr;
        } else if (order_limit->tail_order == order) {
            order_limit->tail_order = order->prev_order;
            order_limit->tail_order->next_order = nullptr;
        } else {
            order->prev_order->next_order = order->next_order;
            order->next_order->prev_order = order->prev_order;
        }

        // Modify limit
        order_limit->total_volume -= order->volume;
        order_limit->size -= 1;

        // Delete order object and remove from map
        delete order;
        order = nullptr;
        orders.erase(order_id);
    } else {
        // Else remove limit and remove from orders dict
        if (order->is_buy_side) {
            bid_tree.remove<bid>(order_limit);
        } else {
            ask_tree.remove<ask>(order_limit);
        }
        orders[order_id] = nullptr;
        orders.erase(order_id);
        limits[limit_price] = nullptr;
        limits.erase(limit_price);
    }

    if (is_buy_side) {
        update_best_bid();
    } else {
        update_best_ask();
    }
    return 1;
}

int Book::cancel_order(int order_id) {

    std::scoped_lock lock {write_m};

    return remove_order(order_id);
}

int Book::get_volume_at_limit(int limit) {
    // Possible that limit gets deleted between find
    // and return (on diff threads)
    if (limits.find(limit) != limits.end()) {
        return limits[limit]->total_volume;
    }
    return 0;
}

int Book::get_spread() {
    // Avoid accessing changing bid/ask trees
    if (best_ask == -1 || best_bid == -1) {
        return -1;
    }
    return best_ask - best_bid;
}

void Book::update_best_bid() {
    best_bid = bid_tree.is_empty() ? -1 : bid_tree.peek_root()->limit_price;
}

void Book::update_best_ask() {
    best_ask = ask_tree.is_empty() ? -1 : ask_tree.peek_root()->limit_price;
}