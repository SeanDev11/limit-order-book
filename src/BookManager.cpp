#include "BookManager.hpp"

int BookManager::place_order(unsigned int security_id, bool is_buy_side, int volume, int price) {
    if (books.find(security_id) == books.end()) {
        books[security_id] = Book();
    }
    return books[security_id].place_order(is_buy_side, volume, price);
}

int BookManager::cancel_order(unsigned int security_id, unsigned int order_id) {
    return books[security_id].cancel_order(order_id);
}

int BookManager::get_volume_at_limit(unsigned int security_id, int limit_price) {
    return books[security_id].get_volume_at_limit(limit_price);
}

int BookManager::get_spread(unsigned int security_id) {
    return books[security_id].get_spread();
}

int BookManager::get_num_open_orders(unsigned int security_id) {
    if (check_book_exists(security_id) < 0) {
        return 0;
    }
    return books[security_id].get_num_open_orders();
}

int BookManager::get_best_bid(unsigned int security_id) {
    return books[security_id].get_best_bid();
}

int BookManager::get_best_ask(unsigned int security_id) {
    return books[security_id].get_best_ask();
}

int BookManager::check_book_exists(unsigned int security_id) {
    if (books.find(security_id) != books.end()) {
        return 1;
    }
    return -1;
}