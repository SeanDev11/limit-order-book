#ifndef LIMIT_HPP
#define LIMIT_HPP

#include "Order.hpp"

class Order;

class Limit {

public:
    Limit() {}

    Limit(int price) : limit_price(price), tree_idx(-1), size(0),
                       total_volume(0), head_order(nullptr), tail_order(nullptr)
    {}

    int limit_price;
    int tree_idx;
    int total_volume;
    int size;
    Order *head_order;
    Order *tail_order;

    void add_order(Order *order);

    int get_size() {
        return size;
    }

    void set_tree_idx(int idx) {
        tree_idx = idx;
    }

    int get_tree_idx() {
        return tree_idx;
    }

    ~Limit();
};


#endif