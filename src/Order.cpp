#include "Order.hpp"

Order::Order(int id, bool is_buy_side, int volume, int limit) : id(id), is_buy_side(is_buy_side), volume(volume), limit_price(limit)
{}
