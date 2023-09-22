#ifndef ORDER_HPP
#define ORDER_HPP

#include "Limit.hpp"

class Limit;

class Order {

public:
    Order(int id, bool isBuySide, int volume, int limit);
    int id;
    int securityId;
    bool isBuySide;
    int volume;
    int limitPrice;
    int entryTime;
    int eventTime;
    Order *nextOrder;
    Order *prevOrder;
    Limit *parentLimit; // associated limit object
    // Add initial volume / executed volume

    ~Order() {
        nextOrder = nullptr;
        prevOrder = nullptr;
        parentLimit = nullptr;
    }
};



#endif