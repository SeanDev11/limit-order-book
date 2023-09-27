#ifndef BOOKMANAGER_HPP
#define BOOKMANAGER_HPP

#include <unordered_map>
#include "Book.hpp"

class BookManager {
  private:
    std::unordered_map<unsigned int, Book> books;
    int check_book_exists(unsigned int security_id);
  public:
    int place_order(unsigned int security_id, bool is_buy_side, int volume, int price);
    int cancel_order(unsigned int security_id, unsigned int order_id);
    int get_volume_at_limit(unsigned int security_id, int limit_price);
    int get_spread(unsigned int security_id);
    int get_num_open_orders(unsigned int security_id);
    int get_best_bid(unsigned int security_id);
    int get_best_ask(unsigned int security_id);
};

#endif
