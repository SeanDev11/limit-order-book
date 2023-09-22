#include "Order.hpp"

Order::Order(int id, bool isBuySide, int volume, int limit) : id(id), isBuySide(isBuySide), volume(volume), limitPrice(limit)
{}
