#include "Book.hpp"
#include "Heap.hpp"

Book::Book() : askTree(Heap(1000)), bidTree(Heap(1000)), orders(std::unordered_map<int, Order*>()),
limits(std::unordered_map<int, Limit*>()), nextOrderId(0)
{}

void Book::queueOrder(Order *order) {
    int price = order->limitPrice;

    // Check if limit at price already exists
    if (limits.find(price) != limits.end()) {
        if (limits[price]->head_order == nullptr) {
            limits[price]->head_order = limits[price]->tail_order = order;
        } else {
            limits[price]->tail_order->nextOrder = order;
            order->prevOrder = limits[price]->tail_order;
            limits[price]->tail_order = order;
        }
    } else {
        // Create new limit and insert into heap
        Limit *newLimit = new Limit(price);
        newLimit->head_order = newLimit->tail_order = order;
        if (order->isBuySide) {
            bidTree.insert<bid>(newLimit);
        } else {
            askTree.insert<ask>(newLimit);
        }
        limits[price] = newLimit;
    }
    limits[price]->total_volume += order->volume;
    limits[price]->size += 1;
    // Set parent limit object of order
    order->parentLimit = limits[price];
}

int Book::executeBuy(int volume, int price) {
    int remaining_volume = volume;
    std::cout << "Executing buy for " << volume << " @" << price << std::endl;
    while (remaining_volume > 0 && !askTree.is_empty()
           && askTree.peek_root()->limit_price <= price) {
        Order *seller = askTree.peek_root()->head_order;
        int tradePrice = std::min(price, seller->limitPrice);
        int tradeVolume = std::min(remaining_volume, seller->volume);
        seller->volume -= tradeVolume;
        seller->parentLimit->total_volume -= tradeVolume;
        remaining_volume -= tradeVolume;
        std::cout << "Made buy for " << tradeVolume << " @" << tradePrice << std::endl;

        if (seller->volume == 0) {
            cancelOrder(seller->id);
        }

    }
    return remaining_volume;
}

int Book::executeSell(int volume, int price) {
    int remaining_volume = volume;
    std::cout << "Executing sell for " << volume << " @" << price << std::endl;
    while (remaining_volume > 0 && !bidTree.is_empty()
           && bidTree.peek_root()->limit_price >= price) {
        Order *buyer = bidTree.peek_root()->head_order;
        int tradePrice = std::min(price, buyer->limitPrice);
        int tradeVolume = std::min(remaining_volume, buyer->volume);
        buyer->volume -= tradeVolume;
        buyer->parentLimit->total_volume -= tradeVolume;
        remaining_volume -= tradeVolume;
        std::cout << "Made sale for " << tradeVolume << " @" << tradePrice << std::endl;
        std::cout << remaining_volume << std::endl;
        if (buyer->volume == 0) {
            cancelOrder(buyer->id);
        }

    }

    return remaining_volume;
}

void Book::placeOrder(bool isBuySide, int volume, int price, int securityId) {
    // TODO: Generate entryTime, id
    const int newOrderId = nextOrderId;

    int remaining_volume = volume;

    if (isBuySide) {
        remaining_volume = executeBuy(remaining_volume, price);
    } else {
        remaining_volume = executeSell(remaining_volume, price);
    }

    // Check if order was fully executed
    if (remaining_volume == 0) {
        return;
    }
    // Create the order
    Order *newOrder = new Order(newOrderId, isBuySide, remaining_volume, price);

    // Handle limit creation / insertion
    queueOrder(newOrder);

    // Insert new order into orders map
    orders[newOrderId] = newOrder;

    nextOrderId++;
}

void Book::cancelOrder(int orderId) {
    if (orders.find(orderId) == orders.end()) {
        return;
    }
    // If not the only order at limit, just remove from LL & orders dict
    Order *order = orders[orderId];
    Limit *orderLimit = order->parentLimit;
    if (orderLimit->get_size() > 1) {
        // Remove from limit LL
        if (orderLimit->head_order == order) {
            orderLimit->head_order = order->nextOrder;
            orderLimit->head_order->prevOrder = nullptr;
        } else if (orderLimit->tail_order == order) {
            orderLimit->tail_order = order->prevOrder;
            orderLimit->tail_order->nextOrder = nullptr;
        } else {
            order->prevOrder->nextOrder = order->nextOrder;
            order->nextOrder->prevOrder = order->prevOrder;
        }

        // Modify limit
        orderLimit->total_volume -= order->volume;
        orderLimit->size -= 1;

        // Delete order object and remove from map
        delete order;
        order = nullptr;
        orders.erase(orderId);
     } else {
        // Else remove limit and remove from orders dict
        if (order->isBuySide) {
            bidTree.remove<bid>(orderLimit);
        } else {
            askTree.remove<ask>(orderLimit);
        }
        orders[orderId] = nullptr;
        orders.erase(orderId);
        limits[orderLimit->limit_price] = nullptr;
        limits.erase(orderLimit->limit_price);
    }

}

int Book::getVolumeAtLimit(int limit) {
    if (limits.find(limit) != limits.end()) {
        return limits[limit]->total_volume;
    }
    return 0;
}