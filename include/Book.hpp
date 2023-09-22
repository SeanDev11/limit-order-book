#ifndef BOOK_HPP
#define BOOK_HPP

#include "Limit.hpp"
#include "Order.hpp"
#include "Heap.hpp"
#include <unordered_map>

class Book {
  private:
    // Bid/Ask trees contain pointers to Limits
    Heap bidTree;
    Heap askTree;
    int nextOrderId;
    void queueOrder(Order *order);
    int executeBuy(int volume, int price);
    int executeSell(int volume, int price);

  public:
    Book();
    std::unordered_map<int, Order*> orders;
    std::unordered_map<int, Limit*> limits;

    // AddOrder, first check if we can fill, else add to book
    void placeOrder(bool isBuySide, int volume, int price, int securityId);
    void cancelOrder(int orderId);
    // void modifyOrder
    bool isEmpty() {
        // bids.isEmpty && asks.isEmpty
        return true;
    }
    // getSpread
    int getVolumeAtLimit(int limit);

};

#endif