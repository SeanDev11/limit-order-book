#ifndef ORDER_HPP
#define ORDER_HPP

#include "Limit.hpp"

class Limit;

class Order {

public:
    Order(int id, bool is_buy_side, int volume, int limit);
    int id;
    int security_id;
    bool is_buy_side;
    int volume;
    int limit_price;
    int entry_time;
    int event_time;
    Order *next_order;
    Order *prev_order;
    Limit *parent_limit; // associated limit object
    // Add initial volume / executed volume

    ~Order() {
        next_order = nullptr;
        prev_order = nullptr;
        parent_limit = nullptr;
    }
};



#endif