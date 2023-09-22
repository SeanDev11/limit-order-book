#include "Limit.hpp"

void Limit::add_order(Order *order) {
    if (size == 0) {
        head_order = order;
    } else {
        tail_order->nextOrder = order;
        order->prevOrder = tail_order;
        tail_order = order;
    }

    size++;
    // TODO: Int overflow check
    if (total_volume + order->volume < 1000000) {
        total_volume += order->volume;
    }

}

Limit::~Limit() {
    // Limit should only be deleted if there are no orders? What if we are cancelling an order

    // Delete orders
    Order *curr = head_order;
    Order *next;
    while (curr && curr != tail_order) {
        next = head_order->nextOrder;
        // Calls order destructor
        delete curr;
        curr = next;
    }
    delete curr;
    head_order = tail_order = curr = next = nullptr;
}