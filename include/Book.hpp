#ifndef BOOK_HPP
#define BOOK_HPP

#include "Limit.hpp"
#include "Order.hpp"
#include "Heap.hpp"
#include <unordered_map>
#include <mutex>

class Book {
  private:
    // Bid/Ask trees contain pointers to Limits
    Heap bid_tree;
    Heap ask_tree;
    unsigned int next_order_id;
    // Best bid/ask variables allow for reading concurrently
    // during add/cancel order operations
    int best_bid;
    int best_ask;
    // TODO:
    // best_bid_volume
    // best_ask_volume
    // last_trade_price
    // last_trade_volume
    // total_bid_volume
    // total_ask_volume
    // Depth of market data (10 levels)
    void queue_order(Order *order);
    int execute_buy(int volume, int price);
    int execute_sell(int volume, int price);

    int remove_order(int order_id);

    void update_best_bid();
    void update_best_ask();

    mutable std::mutex write_m;

  public:
    Book();
    std::unordered_map<int, Order*> orders;
    std::unordered_map<int, Limit*> limits;

    int place_order(bool is_buy_side, int volume, int price);
    int cancel_order(int order_id);
    // void modifyOrder
    bool isEmpty() {
        return bid_tree.is_empty() && ask_tree.is_empty();
    }

    int get_spread();

    int get_volume_at_limit(int limit);

    int get_best_ask() {
        return best_ask;
    }

    int get_best_bid() {
        return best_bid;
    }

    int get_num_open_orders() {
        return orders.size();
    }

    Limit* get_best_ask_limit() {
        return ask_tree.peek_root();
    }

    Limit* get_best_bid_limit() {
        return bid_tree.peek_root();
    }

    Book& operator=(const Book& b) {
        if (this != &b) {
            std::lock(write_m, b.write_m);
            std::lock_guard<std::mutex> l_lock(write_m, std::adopt_lock);
            std::lock_guard<std::mutex> r_lock(b.write_m, std::adopt_lock);
            bid_tree = b.bid_tree;
            ask_tree = b.ask_tree;
            next_order_id = b.next_order_id;
            best_bid = b.best_bid;
            best_ask = b.best_ask;
        }
        return *this;
    }
};

#endif