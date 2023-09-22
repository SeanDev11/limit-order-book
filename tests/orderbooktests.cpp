#include <gtest/gtest.h>
#include "Order.hpp"
#include "Heap.hpp"
#include "Limit.hpp"
#include "Book.hpp"
#include <iostream>

TEST(OrderTests, InstantiateOrder) {
    Order order = Order(123, true, 20, 100);
    EXPECT_EQ(order.id, 123);
}

TEST(MinHeapTests, InstantiateMinHeap) {
    Heap min_heap = Heap(10);
    EXPECT_EQ(min_heap.height(), -1);
    EXPECT_EQ(min_heap.get_max_capacity(), 10);
    EXPECT_EQ(min_heap.get_size(), 0);
}

TEST(MinHeapTests, Insert) {
    Heap min_heap = Heap(10);
    Limit *new_limit = new Limit(100);
    min_heap.insert<tree_type::ask>(new_limit);
    EXPECT_EQ(min_heap.get_size(), 1);
    EXPECT_EQ(min_heap.height(), 0);
    EXPECT_EQ(min_heap.peek_root()->limit_price, 100);

    Limit *new_limit2 = new Limit(90);
    min_heap.insert<tree_type::ask>(new_limit2);
    EXPECT_EQ(min_heap.get_size(), 2);
    EXPECT_EQ(min_heap.height(), 1);
    EXPECT_EQ(min_heap.peek_root()->limit_price, 90);

    Limit *new_limit3 = new Limit(80);
    min_heap.insert<tree_type::ask>(new_limit3);
    EXPECT_EQ(min_heap.get_size(), 3);
    EXPECT_EQ(min_heap.height(), 1);
    EXPECT_EQ(min_heap.peek_root()->limit_price, 80);

    Limit *new_limit4 = new Limit(110);
    min_heap.insert<tree_type::ask>(new_limit4);
    EXPECT_EQ(min_heap.get_size(), 4);
    EXPECT_EQ(min_heap.height(), 2);
    EXPECT_EQ(min_heap.peek_root()->limit_price, 80);

    Limit *new_limit5 = new Limit(105);
    min_heap.insert<tree_type::ask>(new_limit5);
    EXPECT_EQ(min_heap.get_size(), 5);
    EXPECT_EQ(min_heap.height(), 2);
    EXPECT_EQ(min_heap.peek_root()->limit_price, 80);

    Limit *new_limit6 = new Limit(111);
    min_heap.insert<tree_type::ask>(new_limit6);
    EXPECT_EQ(min_heap.get_size(), 6);
    EXPECT_EQ(min_heap.height(), 2);
    EXPECT_EQ(min_heap.peek_root()->limit_price, 80);

    Limit *new_limit7 = new Limit(95);
    min_heap.insert<tree_type::ask>(new_limit7);
    EXPECT_EQ(min_heap.get_size(), 7);
    EXPECT_EQ(min_heap.height(), 2);
    EXPECT_EQ(min_heap.peek_root()->limit_price, 80);

    Limit *new_limit8 = new Limit(150);
    min_heap.insert<tree_type::ask>(new_limit8);
    EXPECT_EQ(min_heap.get_size(), 8);
    EXPECT_EQ(min_heap.height(), 3);
    EXPECT_EQ(min_heap.peek_root()->limit_price, 80);

    Limit *new_limit9 = new Limit(50);
    min_heap.insert<tree_type::ask>(new_limit9);
    EXPECT_EQ(min_heap.get_size(), 9);
    EXPECT_EQ(min_heap.height(), 3);
    EXPECT_EQ(min_heap.peek_root()->limit_price, 50);

    Limit *new_limit10 = new Limit(10);
    min_heap.insert<tree_type::ask>(new_limit10);
    EXPECT_EQ(min_heap.get_size(), 10);
    EXPECT_EQ(min_heap.height(), 3);
    EXPECT_EQ(min_heap.peek_root()->limit_price, 10);
}


TEST(MaxHeapTests, Insert) {
    Heap max_heap = Heap(10);
    Limit *new_limit = new Limit(100);
    max_heap.insert<tree_type::bid>(new_limit);
    EXPECT_EQ(max_heap.get_size(), 1);
    EXPECT_EQ(max_heap.height(), 0);
    EXPECT_EQ(max_heap.peek_root()->limit_price, 100);

    Limit *new_limit2 = new Limit(90);
    max_heap.insert<tree_type::bid>(new_limit2);
    EXPECT_EQ(max_heap.get_size(), 2);
    EXPECT_EQ(max_heap.height(), 1);
    EXPECT_EQ(max_heap.peek_root()->limit_price, 100);

    Limit *new_limit3 = new Limit(80);
    max_heap.insert<tree_type::bid>(new_limit3);
    EXPECT_EQ(max_heap.get_size(), 3);
    EXPECT_EQ(max_heap.height(), 1);
    EXPECT_EQ(max_heap.peek_root()->limit_price, 100);

    Limit *new_limit4 = new Limit(110);
    max_heap.insert<tree_type::bid>(new_limit4);
    EXPECT_EQ(max_heap.get_size(), 4);
    EXPECT_EQ(max_heap.height(), 2);
    EXPECT_EQ(max_heap.peek_root()->limit_price, 110);

    Limit *new_limit5 = new Limit(105);
    max_heap.insert<tree_type::bid>(new_limit5);
    EXPECT_EQ(max_heap.get_size(), 5);
    EXPECT_EQ(max_heap.height(), 2);
    EXPECT_EQ(max_heap.peek_root()->limit_price, 110);

    Limit *new_limit6 = new Limit(111);
    max_heap.insert<tree_type::bid>(new_limit6);
    EXPECT_EQ(max_heap.get_size(), 6);
    EXPECT_EQ(max_heap.height(), 2);
    EXPECT_EQ(max_heap.peek_root()->limit_price, 111);

    Limit *new_limit7 = new Limit(95);
    max_heap.insert<tree_type::bid>(new_limit7);
    EXPECT_EQ(max_heap.get_size(), 7);
    EXPECT_EQ(max_heap.height(), 2);
    EXPECT_EQ(max_heap.peek_root()->limit_price, 111);

    Limit *new_limit8 = new Limit(30);
    max_heap.insert<tree_type::bid>(new_limit8);
    EXPECT_EQ(max_heap.get_size(), 8);
    EXPECT_EQ(max_heap.height(), 3);
    EXPECT_EQ(max_heap.peek_root()->limit_price, 111);

    Limit *new_limit9 = new Limit(500);
    max_heap.insert<tree_type::bid>(new_limit9);
    EXPECT_EQ(max_heap.get_size(), 9);
    EXPECT_EQ(max_heap.height(), 3);
    EXPECT_EQ(max_heap.peek_root()->limit_price, 500);

    Limit *new_limit10 = new Limit(1000);
    max_heap.insert<tree_type::bid>(new_limit10);
    EXPECT_EQ(max_heap.get_size(), 10);
    EXPECT_EQ(max_heap.height(), 3);
    EXPECT_EQ(max_heap.peek_root()->limit_price, 1000);
}

TEST(MinHeapTests, Remove) {
    Heap min_heap = Heap(10);
    Limit *new_limit = new Limit(100);
    min_heap.insert<tree_type::ask>(new_limit);
    EXPECT_EQ(min_heap.get_size(), 1);
    EXPECT_EQ(min_heap.height(), 0);
    EXPECT_EQ(min_heap.peek_root()->limit_price, 100);

    Limit *new_limit2 = new Limit(90);
    min_heap.insert<tree_type::ask>(new_limit2);
    EXPECT_EQ(min_heap.get_size(), 2);
    EXPECT_EQ(min_heap.height(), 1);
    EXPECT_EQ(min_heap.peek_root()->limit_price, 90);

    Limit *new_limit3 = new Limit(80);
    min_heap.insert<tree_type::ask>(new_limit3);
    EXPECT_EQ(min_heap.get_size(), 3);
    EXPECT_EQ(min_heap.height(), 1);
    EXPECT_EQ(min_heap.peek_root()->limit_price, 80);

    Limit *new_limit4 = new Limit(110);
    min_heap.insert<tree_type::ask>(new_limit4);
    EXPECT_EQ(min_heap.get_size(), 4);
    EXPECT_EQ(min_heap.height(), 2);
    EXPECT_EQ(min_heap.peek_root()->limit_price, 80);

    Limit *new_limit5 = new Limit(105);
    min_heap.insert<tree_type::ask>(new_limit5);
    EXPECT_EQ(min_heap.get_size(), 5);
    EXPECT_EQ(min_heap.height(), 2);
    EXPECT_EQ(min_heap.peek_root()->limit_price, 80);

    Limit *new_limit6 = new Limit(111);
    min_heap.insert<tree_type::ask>(new_limit6);
    EXPECT_EQ(min_heap.get_size(), 6);
    EXPECT_EQ(min_heap.height(), 2);
    EXPECT_EQ(min_heap.peek_root()->limit_price, 80);

    Limit *new_limit7 = new Limit(95);
    min_heap.insert<tree_type::ask>(new_limit7);
    EXPECT_EQ(min_heap.get_size(), 7);
    EXPECT_EQ(min_heap.height(), 2);
    EXPECT_EQ(min_heap.peek_root()->limit_price, 80);

    min_heap.remove<tree_type::ask>(new_limit7);
    EXPECT_EQ(min_heap.get_size(), 6);
    EXPECT_EQ(min_heap.height(), 2);
    EXPECT_EQ(min_heap.peek_root()->limit_price, 80);

    Limit *new_limit8 = new Limit(150);
    min_heap.insert<tree_type::ask>(new_limit8);
    EXPECT_EQ(min_heap.get_size(), 7);
    EXPECT_EQ(min_heap.height(), 2);
    EXPECT_EQ(min_heap.peek_root()->limit_price, 80);

    Limit *new_limit9 = new Limit(50);
    min_heap.insert<tree_type::ask>(new_limit9);
    EXPECT_EQ(min_heap.get_size(), 8);
    EXPECT_EQ(min_heap.height(), 3);
    EXPECT_EQ(min_heap.peek_root()->limit_price, 50);

    Limit *new_limit10 = new Limit(10);
    min_heap.insert<tree_type::ask>(new_limit10);
    EXPECT_EQ(min_heap.get_size(), 9);
    EXPECT_EQ(min_heap.height(), 3);
    EXPECT_EQ(min_heap.peek_root()->limit_price, 10);

    new_limit10->size = 20;
    EXPECT_EQ(new_limit10, min_heap.peek_root());
    EXPECT_EQ(min_heap.peek_root()->size, 20);

}

TEST(MaxHeapTests, Remove) {
    Heap max_heap = Heap(10);
    Limit *new_limit = new Limit(100);
    max_heap.insert<tree_type::bid>(new_limit);
    EXPECT_EQ(max_heap.get_size(), 1);
    EXPECT_EQ(max_heap.height(), 0);
    EXPECT_EQ(max_heap.peek_root()->limit_price, 100);

    Limit *new_limit2 = new Limit(90);
    max_heap.insert<tree_type::bid>(new_limit2);
    EXPECT_EQ(max_heap.get_size(), 2);
    EXPECT_EQ(max_heap.height(), 1);
    EXPECT_EQ(max_heap.peek_root()->limit_price, 100);

    Limit *new_limit3 = new Limit(110);
    max_heap.insert<tree_type::bid>(new_limit3);
    EXPECT_EQ(max_heap.get_size(), 3);
    EXPECT_EQ(max_heap.height(), 1);
    EXPECT_EQ(max_heap.peek_root()->limit_price, 110);

    Limit *new_limit4 = new Limit(70);
    max_heap.insert<tree_type::bid>(new_limit4);
    EXPECT_EQ(max_heap.get_size(), 4);
    EXPECT_EQ(max_heap.height(), 2);
    EXPECT_EQ(max_heap.peek_root()->limit_price, 110);

    Limit *new_limit5 = new Limit(105);
    max_heap.insert<tree_type::bid>(new_limit5);
    EXPECT_EQ(max_heap.get_size(), 5);
    EXPECT_EQ(max_heap.height(), 2);
    EXPECT_EQ(max_heap.peek_root()->limit_price, 110);

    Limit *new_limit6 = new Limit(111);
    max_heap.insert<tree_type::bid>(new_limit6);
    EXPECT_EQ(max_heap.get_size(), 6);
    EXPECT_EQ(max_heap.height(), 2);
    EXPECT_EQ(max_heap.peek_root()->limit_price, 111);

    Limit *new_limit7 = new Limit(30);
    max_heap.insert<tree_type::bid>(new_limit7);
    EXPECT_EQ(max_heap.get_size(), 7);
    EXPECT_EQ(max_heap.height(), 2);
    EXPECT_EQ(max_heap.peek_root()->limit_price, 111);

    max_heap.remove<tree_type::bid>(new_limit7);

    EXPECT_EQ(max_heap.get_size(), 6);
    EXPECT_EQ(max_heap.height(), 2);
    EXPECT_EQ(max_heap.peek_root()->limit_price, 111);

    Limit *new_limit8 = new Limit(150);
    max_heap.insert<tree_type::bid>(new_limit8);
    EXPECT_EQ(max_heap.get_size(), 7);
    EXPECT_EQ(max_heap.height(), 2);
    EXPECT_EQ(max_heap.peek_root()->limit_price, 150);

    Limit *new_limit9 = new Limit(10);
    max_heap.insert<tree_type::bid>(new_limit9);
    EXPECT_EQ(max_heap.get_size(), 8);
    EXPECT_EQ(max_heap.height(), 3);
    EXPECT_EQ(max_heap.peek_root()->limit_price, 150);

    Limit *new_limit10 = new Limit(170);
    max_heap.insert<tree_type::bid>(new_limit10);
    EXPECT_EQ(max_heap.get_size(), 9);
    EXPECT_EQ(max_heap.height(), 3);
    EXPECT_EQ(max_heap.peek_root()->limit_price, 170);

    new_limit10->size = 20;
    EXPECT_EQ(new_limit10, max_heap.peek_root());
    EXPECT_EQ(max_heap.peek_root()->size, 20);

}

TEST(MaxHeapTests, RemoveSwapInLesser) {
    Heap max_heap = Heap(10);
    Limit *new_limit = new Limit(100);
    max_heap.insert<tree_type::bid>(new_limit);
    EXPECT_EQ(max_heap.get_size(), 1);
    EXPECT_EQ(max_heap.height(), 0);
    EXPECT_EQ(max_heap.peek_root()->limit_price, 100);

    Limit *new_limit2 = new Limit(90);
    max_heap.insert<tree_type::bid>(new_limit2);
    EXPECT_EQ(max_heap.get_size(), 2);
    EXPECT_EQ(max_heap.height(), 1);
    EXPECT_EQ(max_heap.peek_root()->limit_price, 100);

    Limit *new_limit3 = new Limit(85);
    max_heap.insert<tree_type::bid>(new_limit3);
    EXPECT_EQ(max_heap.get_size(), 3);
    EXPECT_EQ(max_heap.height(), 1);
    EXPECT_EQ(max_heap.peek_root()->limit_price, 100);

    Limit *new_limit4 = new Limit(80);
    max_heap.insert<tree_type::bid>(new_limit4);
    EXPECT_EQ(max_heap.get_size(), 4);
    EXPECT_EQ(max_heap.height(), 2);
    EXPECT_EQ(max_heap.peek_root()->limit_price, 100);

    Limit *new_limit5 = new Limit(70);
    max_heap.insert<tree_type::bid>(new_limit5);
    EXPECT_EQ(max_heap.get_size(), 5);
    EXPECT_EQ(max_heap.height(), 2);
    EXPECT_EQ(max_heap.peek_root()->limit_price, 100);

    max_heap.remove<tree_type::bid>(new_limit2);

    EXPECT_EQ(max_heap.get_size(), 4);
    EXPECT_EQ(max_heap.height(), 2);
    EXPECT_EQ(max_heap.peek_root()->limit_price, 100);

    EXPECT_EQ(max_heap.get_limit_at(0)->limit_price, 100);
    EXPECT_EQ(max_heap.get_limit_at(1)->limit_price, 80);
    EXPECT_EQ(max_heap.get_limit_at(2)->limit_price, 85);
    EXPECT_EQ(max_heap.get_limit_at(3)->limit_price, 70);
}

TEST(MaxHeapTests, RemoveSwapInGreater) {
    Heap max_heap = Heap(10);
    Limit *new_limit = new Limit(100);
    max_heap.insert<tree_type::bid>(new_limit);
    EXPECT_EQ(max_heap.get_size(), 1);
    EXPECT_EQ(max_heap.height(), 0);
    EXPECT_EQ(max_heap.peek_root()->limit_price, 100);

    Limit *new_limit2 = new Limit(90);
    max_heap.insert<tree_type::bid>(new_limit2);
    EXPECT_EQ(max_heap.get_size(), 2);
    EXPECT_EQ(max_heap.height(), 1);
    EXPECT_EQ(max_heap.peek_root()->limit_price, 100);

    Limit *new_limit3 = new Limit(85);
    max_heap.insert<tree_type::bid>(new_limit3);
    EXPECT_EQ(max_heap.get_size(), 3);
    EXPECT_EQ(max_heap.height(), 1);
    EXPECT_EQ(max_heap.peek_root()->limit_price, 100);

    Limit *new_limit4 = new Limit(88);
    max_heap.insert<tree_type::bid>(new_limit4);
    EXPECT_EQ(max_heap.get_size(), 4);
    EXPECT_EQ(max_heap.height(), 2);
    EXPECT_EQ(max_heap.peek_root()->limit_price, 100);

    Limit *new_limit5 = new Limit(89);
    max_heap.insert<tree_type::bid>(new_limit5);
    EXPECT_EQ(max_heap.get_size(), 5);
    EXPECT_EQ(max_heap.height(), 2);
    EXPECT_EQ(max_heap.peek_root()->limit_price, 100);

    Limit *new_limit6 = new Limit(70);
    max_heap.insert<tree_type::bid>(new_limit6);
    EXPECT_EQ(max_heap.get_size(), 6);
    EXPECT_EQ(max_heap.height(), 2);
    EXPECT_EQ(max_heap.peek_root()->limit_price, 100);

    Limit *new_limit7 = new Limit(60);
    max_heap.insert<tree_type::bid>(new_limit7);
    EXPECT_EQ(max_heap.get_size(), 7);
    EXPECT_EQ(max_heap.height(), 2);
    EXPECT_EQ(max_heap.peek_root()->limit_price, 100);

    Limit *new_limit8 = new Limit(87);
    max_heap.insert<tree_type::bid>(new_limit8);
    EXPECT_EQ(max_heap.get_size(), 8);
    EXPECT_EQ(max_heap.height(), 3);
    EXPECT_EQ(max_heap.peek_root()->limit_price, 100);

    max_heap.remove<tree_type::bid>(new_limit6);

    EXPECT_EQ(max_heap.get_size(), 7);
    EXPECT_EQ(max_heap.height(), 2);
    EXPECT_EQ(max_heap.peek_root()->limit_price, 100);

    EXPECT_EQ(max_heap.get_limit_at(0)->limit_price, 100);
    EXPECT_EQ(max_heap.get_limit_at(1)->limit_price, 90);
    EXPECT_EQ(max_heap.get_limit_at(2)->limit_price, 87);
    EXPECT_EQ(max_heap.get_limit_at(3)->limit_price, 88);
    EXPECT_EQ(max_heap.get_limit_at(4)->limit_price, 89);
    EXPECT_EQ(max_heap.get_limit_at(5)->limit_price, 85);
    EXPECT_EQ(max_heap.get_limit_at(6)->limit_price, 60);
}

TEST(MaxHeapTests, RemoveRoot) {
    Heap max_heap = Heap(10);
    Limit *new_limit = new Limit(100);
    max_heap.insert<tree_type::bid>(new_limit);
    EXPECT_EQ(max_heap.get_size(), 1);
    EXPECT_EQ(max_heap.height(), 0);
    EXPECT_EQ(max_heap.peek_root()->limit_price, 100);

    Limit *new_limit2 = new Limit(90);
    max_heap.insert<tree_type::bid>(new_limit2);
    EXPECT_EQ(max_heap.get_size(), 2);
    EXPECT_EQ(max_heap.height(), 1);
    EXPECT_EQ(max_heap.peek_root()->limit_price, 100);

    Limit *new_limit3 = new Limit(85);
    max_heap.insert<tree_type::bid>(new_limit3);
    EXPECT_EQ(max_heap.get_size(), 3);
    EXPECT_EQ(max_heap.height(), 1);
    EXPECT_EQ(max_heap.peek_root()->limit_price, 100);

    Limit *new_limit4 = new Limit(88);
    max_heap.insert<tree_type::bid>(new_limit4);
    EXPECT_EQ(max_heap.get_size(), 4);
    EXPECT_EQ(max_heap.height(), 2);
    EXPECT_EQ(max_heap.peek_root()->limit_price, 100);

    Limit *new_limit5 = new Limit(89);
    max_heap.insert<tree_type::bid>(new_limit5);
    EXPECT_EQ(max_heap.get_size(), 5);
    EXPECT_EQ(max_heap.height(), 2);
    EXPECT_EQ(max_heap.peek_root()->limit_price, 100);

    Limit *new_limit6 = new Limit(70);
    max_heap.insert<tree_type::bid>(new_limit6);
    EXPECT_EQ(max_heap.get_size(), 6);
    EXPECT_EQ(max_heap.height(), 2);
    EXPECT_EQ(max_heap.peek_root()->limit_price, 100);

    Limit *new_limit7 = new Limit(60);
    max_heap.insert<tree_type::bid>(new_limit7);
    EXPECT_EQ(max_heap.get_size(), 7);
    EXPECT_EQ(max_heap.height(), 2);
    EXPECT_EQ(max_heap.peek_root()->limit_price, 100);

    Limit *new_limit8 = new Limit(87);
    max_heap.insert<tree_type::bid>(new_limit8);
    EXPECT_EQ(max_heap.get_size(), 8);
    EXPECT_EQ(max_heap.height(), 3);
    EXPECT_EQ(max_heap.peek_root()->limit_price, 100);

    max_heap.remove<tree_type::bid>(new_limit);

    EXPECT_EQ(max_heap.get_size(), 7);
    EXPECT_EQ(max_heap.height(), 2);
    EXPECT_EQ(max_heap.peek_root()->limit_price, 90);

    EXPECT_EQ(max_heap.get_limit_at(0)->limit_price, 90);
    EXPECT_EQ(max_heap.get_limit_at(1)->limit_price, 89);
    EXPECT_EQ(max_heap.get_limit_at(2)->limit_price, 85);
    EXPECT_EQ(max_heap.get_limit_at(3)->limit_price, 88);
    EXPECT_EQ(max_heap.get_limit_at(4)->limit_price, 87);
    EXPECT_EQ(max_heap.get_limit_at(5)->limit_price, 70);
    EXPECT_EQ(max_heap.get_limit_at(6)->limit_price, 60);
}

TEST(MaxHeapTests, RemoveLast) {
    Heap max_heap = Heap(10);
    Limit *new_limit = new Limit(100);
    max_heap.insert<tree_type::bid>(new_limit);
    EXPECT_EQ(max_heap.get_size(), 1);
    EXPECT_EQ(max_heap.height(), 0);
    EXPECT_EQ(max_heap.peek_root()->limit_price, 100);

    Limit *new_limit2 = new Limit(90);
    max_heap.insert<tree_type::bid>(new_limit2);
    EXPECT_EQ(max_heap.get_size(), 2);
    EXPECT_EQ(max_heap.height(), 1);
    EXPECT_EQ(max_heap.peek_root()->limit_price, 100);

    Limit *new_limit3 = new Limit(85);
    max_heap.insert<tree_type::bid>(new_limit3);
    EXPECT_EQ(max_heap.get_size(), 3);
    EXPECT_EQ(max_heap.height(), 1);
    EXPECT_EQ(max_heap.peek_root()->limit_price, 100);

    Limit *new_limit4 = new Limit(88);
    max_heap.insert<tree_type::bid>(new_limit4);
    EXPECT_EQ(max_heap.get_size(), 4);
    EXPECT_EQ(max_heap.height(), 2);
    EXPECT_EQ(max_heap.peek_root()->limit_price, 100);

    Limit *new_limit5 = new Limit(89);
    max_heap.insert<tree_type::bid>(new_limit5);
    EXPECT_EQ(max_heap.get_size(), 5);
    EXPECT_EQ(max_heap.height(), 2);
    EXPECT_EQ(max_heap.peek_root()->limit_price, 100);

    Limit *new_limit6 = new Limit(70);
    max_heap.insert<tree_type::bid>(new_limit6);
    EXPECT_EQ(max_heap.get_size(), 6);
    EXPECT_EQ(max_heap.height(), 2);
    EXPECT_EQ(max_heap.peek_root()->limit_price, 100);

    Limit *new_limit7 = new Limit(60);
    max_heap.insert<tree_type::bid>(new_limit7);
    EXPECT_EQ(max_heap.get_size(), 7);
    EXPECT_EQ(max_heap.height(), 2);
    EXPECT_EQ(max_heap.peek_root()->limit_price, 100);

    Limit *new_limit8 = new Limit(87);
    max_heap.insert<tree_type::bid>(new_limit8);
    EXPECT_EQ(max_heap.get_size(), 8);
    EXPECT_EQ(max_heap.height(), 3);
    EXPECT_EQ(max_heap.peek_root()->limit_price, 100);

    max_heap.remove<tree_type::bid>(new_limit8);

    EXPECT_EQ(max_heap.get_size(), 7);
    EXPECT_EQ(max_heap.height(), 2);
    EXPECT_EQ(max_heap.peek_root()->limit_price, 100);

    EXPECT_EQ(max_heap.get_limit_at(0)->limit_price, 100);
    EXPECT_EQ(max_heap.get_limit_at(1)->limit_price, 90);
    EXPECT_EQ(max_heap.get_limit_at(2)->limit_price, 85);
    EXPECT_EQ(max_heap.get_limit_at(3)->limit_price, 88);
    EXPECT_EQ(max_heap.get_limit_at(4)->limit_price, 89);
    EXPECT_EQ(max_heap.get_limit_at(5)->limit_price, 70);
    EXPECT_EQ(max_heap.get_limit_at(6)->limit_price, 60);
}

TEST(MinHeapTests, RemoveSwapInGreater) {
    Heap min_heap = Heap(10);

    Limit *new_limit = new Limit(100);
    min_heap.insert<tree_type::ask>(new_limit);
    EXPECT_EQ(min_heap.get_size(), 1);
    EXPECT_EQ(min_heap.height(), 0);
    EXPECT_EQ(min_heap.peek_root()->limit_price, 100);

    Limit *new_limit2 = new Limit(110);
    min_heap.insert<tree_type::ask>(new_limit2);
    EXPECT_EQ(min_heap.get_size(), 2);
    EXPECT_EQ(min_heap.height(), 1);
    EXPECT_EQ(min_heap.peek_root()->limit_price, 100);

    Limit *new_limit3 = new Limit(120);
    min_heap.insert<tree_type::ask>(new_limit3);
    EXPECT_EQ(min_heap.get_size(), 3);
    EXPECT_EQ(min_heap.height(), 1);
    EXPECT_EQ(min_heap.peek_root()->limit_price, 100);

    Limit *new_limit4 = new Limit(129);
    min_heap.insert<tree_type::ask>(new_limit4);
    EXPECT_EQ(min_heap.get_size(), 4);
    EXPECT_EQ(min_heap.height(), 2);
    EXPECT_EQ(min_heap.peek_root()->limit_price, 100);

    Limit *new_limit5 = new Limit(121);
    min_heap.insert<tree_type::ask>(new_limit5);
    EXPECT_EQ(min_heap.get_size(), 5);
    EXPECT_EQ(min_heap.height(), 2);
    EXPECT_EQ(min_heap.peek_root()->limit_price, 100);

    Limit *new_limit6 = new Limit(130);
    min_heap.insert<tree_type::ask>(new_limit6);
    EXPECT_EQ(min_heap.get_size(), 6);
    EXPECT_EQ(min_heap.height(), 2);
    EXPECT_EQ(min_heap.peek_root()->limit_price, 100);

    Limit *new_limit7 = new Limit(140);
    min_heap.insert<tree_type::ask>(new_limit7);
    EXPECT_EQ(min_heap.get_size(), 7);
    EXPECT_EQ(min_heap.height(), 2);
    EXPECT_EQ(min_heap.peek_root()->limit_price, 100);

    min_heap.remove<tree_type::ask>(new_limit3);

    EXPECT_EQ(min_heap.get_size(), 6);
    EXPECT_EQ(min_heap.height(), 2);
    EXPECT_EQ(min_heap.peek_root()->limit_price, 100);

    EXPECT_EQ(min_heap.get_limit_at(0)->limit_price, 100);
    EXPECT_EQ(min_heap.get_limit_at(1)->limit_price, 110);
    EXPECT_EQ(min_heap.get_limit_at(2)->limit_price, 130);
    EXPECT_EQ(min_heap.get_limit_at(3)->limit_price, 129);
    EXPECT_EQ(min_heap.get_limit_at(4)->limit_price, 121);
    EXPECT_EQ(min_heap.get_limit_at(5)->limit_price, 140);
}

TEST(MinHeapTests, RemoveSwapInLesser) {
    Heap min_heap = Heap(10);

    Limit *new_limit = new Limit(100);
    min_heap.insert<tree_type::ask>(new_limit);
    EXPECT_EQ(min_heap.get_size(), 1);
    EXPECT_EQ(min_heap.height(), 0);
    EXPECT_EQ(min_heap.peek_root()->limit_price, 100);

    Limit *new_limit2 = new Limit(110);
    min_heap.insert<tree_type::ask>(new_limit2);
    EXPECT_EQ(min_heap.get_size(), 2);
    EXPECT_EQ(min_heap.height(), 1);
    EXPECT_EQ(min_heap.peek_root()->limit_price, 100);

    Limit *new_limit3 = new Limit(101);
    min_heap.insert<tree_type::ask>(new_limit3);
    EXPECT_EQ(min_heap.get_size(), 3);
    EXPECT_EQ(min_heap.height(), 1);
    EXPECT_EQ(min_heap.peek_root()->limit_price, 100);

    Limit *new_limit4 = new Limit(120);
    min_heap.insert<tree_type::ask>(new_limit4);
    EXPECT_EQ(min_heap.get_size(), 4);
    EXPECT_EQ(min_heap.height(), 2);
    EXPECT_EQ(min_heap.peek_root()->limit_price, 100);

    Limit *new_limit5 = new Limit(130);
    min_heap.insert<tree_type::ask>(new_limit5);
    EXPECT_EQ(min_heap.get_size(), 5);
    EXPECT_EQ(min_heap.height(), 2);
    EXPECT_EQ(min_heap.peek_root()->limit_price, 100);

    Limit *new_limit6 = new Limit(102);
    min_heap.insert<tree_type::ask>(new_limit6);
    EXPECT_EQ(min_heap.get_size(), 6);
    EXPECT_EQ(min_heap.height(), 2);
    EXPECT_EQ(min_heap.peek_root()->limit_price, 100);

    min_heap.remove<tree_type::ask>(new_limit4);

    EXPECT_EQ(min_heap.get_size(), 5);
    EXPECT_EQ(min_heap.height(), 2);
    EXPECT_EQ(min_heap.peek_root()->limit_price, 100);

    EXPECT_EQ(min_heap.get_limit_at(0)->limit_price, 100);
    EXPECT_EQ(min_heap.get_limit_at(1)->limit_price, 102);
    EXPECT_EQ(min_heap.get_limit_at(2)->limit_price, 101);
    EXPECT_EQ(min_heap.get_limit_at(3)->limit_price, 110);
    EXPECT_EQ(min_heap.get_limit_at(4)->limit_price, 130);
}

TEST(MinHeapTests, RemoveRoot) {
    Heap min_heap = Heap(10);

    Limit *new_limit = new Limit(100);
    min_heap.insert<tree_type::ask>(new_limit);
    EXPECT_EQ(min_heap.get_size(), 1);
    EXPECT_EQ(min_heap.height(), 0);
    EXPECT_EQ(min_heap.peek_root()->limit_price, 100);

    Limit *new_limit2 = new Limit(110);
    min_heap.insert<tree_type::ask>(new_limit2);
    EXPECT_EQ(min_heap.get_size(), 2);
    EXPECT_EQ(min_heap.height(), 1);
    EXPECT_EQ(min_heap.peek_root()->limit_price, 100);

    Limit *new_limit3 = new Limit(120);
    min_heap.insert<tree_type::ask>(new_limit3);
    EXPECT_EQ(min_heap.get_size(), 3);
    EXPECT_EQ(min_heap.height(), 1);
    EXPECT_EQ(min_heap.peek_root()->limit_price, 100);

    Limit *new_limit4 = new Limit(129);
    min_heap.insert<tree_type::ask>(new_limit4);
    EXPECT_EQ(min_heap.get_size(), 4);
    EXPECT_EQ(min_heap.height(), 2);
    EXPECT_EQ(min_heap.peek_root()->limit_price, 100);

    Limit *new_limit5 = new Limit(121);
    min_heap.insert<tree_type::ask>(new_limit5);
    EXPECT_EQ(min_heap.get_size(), 5);
    EXPECT_EQ(min_heap.height(), 2);
    EXPECT_EQ(min_heap.peek_root()->limit_price, 100);

    Limit *new_limit6 = new Limit(130);
    min_heap.insert<tree_type::ask>(new_limit6);
    EXPECT_EQ(min_heap.get_size(), 6);
    EXPECT_EQ(min_heap.height(), 2);
    EXPECT_EQ(min_heap.peek_root()->limit_price, 100);

    Limit *new_limit7 = new Limit(140);
    min_heap.insert<tree_type::ask>(new_limit7);
    EXPECT_EQ(min_heap.get_size(), 7);
    EXPECT_EQ(min_heap.height(), 2);
    EXPECT_EQ(min_heap.peek_root()->limit_price, 100);

    min_heap.remove<tree_type::ask>(new_limit);

    EXPECT_EQ(min_heap.get_size(), 6);
    EXPECT_EQ(min_heap.height(), 2);
    EXPECT_EQ(min_heap.peek_root()->limit_price, 110);

    EXPECT_EQ(min_heap.get_limit_at(0)->limit_price, 110);
    EXPECT_EQ(min_heap.get_limit_at(1)->limit_price, 121);
    EXPECT_EQ(min_heap.get_limit_at(2)->limit_price, 120);
    EXPECT_EQ(min_heap.get_limit_at(3)->limit_price, 129);
    EXPECT_EQ(min_heap.get_limit_at(4)->limit_price, 140);
    EXPECT_EQ(min_heap.get_limit_at(5)->limit_price, 130);
}

TEST(MinHeapTests, RemoveLast) {
    Heap min_heap = Heap(10);

    Limit *new_limit = new Limit(100);
    min_heap.insert<tree_type::ask>(new_limit);
    EXPECT_EQ(min_heap.get_size(), 1);
    EXPECT_EQ(min_heap.height(), 0);
    EXPECT_EQ(min_heap.peek_root()->limit_price, 100);

    Limit *new_limit2 = new Limit(110);
    min_heap.insert<tree_type::ask>(new_limit2);
    EXPECT_EQ(min_heap.get_size(), 2);
    EXPECT_EQ(min_heap.height(), 1);
    EXPECT_EQ(min_heap.peek_root()->limit_price, 100);

    Limit *new_limit3 = new Limit(120);
    min_heap.insert<tree_type::ask>(new_limit3);
    EXPECT_EQ(min_heap.get_size(), 3);
    EXPECT_EQ(min_heap.height(), 1);
    EXPECT_EQ(min_heap.peek_root()->limit_price, 100);

    Limit *new_limit4 = new Limit(129);
    min_heap.insert<tree_type::ask>(new_limit4);
    EXPECT_EQ(min_heap.get_size(), 4);
    EXPECT_EQ(min_heap.height(), 2);
    EXPECT_EQ(min_heap.peek_root()->limit_price, 100);

    Limit *new_limit5 = new Limit(121);
    min_heap.insert<tree_type::ask>(new_limit5);
    EXPECT_EQ(min_heap.get_size(), 5);
    EXPECT_EQ(min_heap.height(), 2);
    EXPECT_EQ(min_heap.peek_root()->limit_price, 100);

    Limit *new_limit6 = new Limit(130);
    min_heap.insert<tree_type::ask>(new_limit6);
    EXPECT_EQ(min_heap.get_size(), 6);
    EXPECT_EQ(min_heap.height(), 2);
    EXPECT_EQ(min_heap.peek_root()->limit_price, 100);

    Limit *new_limit7 = new Limit(140);
    min_heap.insert<tree_type::ask>(new_limit7);
    EXPECT_EQ(min_heap.get_size(), 7);
    EXPECT_EQ(min_heap.height(), 2);
    EXPECT_EQ(min_heap.peek_root()->limit_price, 100);

    min_heap.remove<tree_type::ask>(new_limit7);

    EXPECT_EQ(min_heap.get_size(), 6);
    EXPECT_EQ(min_heap.height(), 2);
    EXPECT_EQ(min_heap.peek_root()->limit_price, 100);

    EXPECT_EQ(min_heap.get_limit_at(0)->limit_price, 100);
    EXPECT_EQ(min_heap.get_limit_at(1)->limit_price, 110);
    EXPECT_EQ(min_heap.get_limit_at(2)->limit_price, 120);
    EXPECT_EQ(min_heap.get_limit_at(3)->limit_price, 129);
    EXPECT_EQ(min_heap.get_limit_at(4)->limit_price, 121);
    EXPECT_EQ(min_heap.get_limit_at(5)->limit_price, 130);
}

TEST(OrderPointerTests, SameOrderObject) {
    // Same order object in tree as in map


}

TEST(BookTests, Basic1) {
    Book *book = new Book();
    book->placeOrder(true, 10, 100, 5);
    EXPECT_EQ(book->getVolumeAtLimit(100), 10);
}

TEST(BookTests, Basic2) {
    Book *book = new Book();
    // Buy:
    // 10 @ 100
    book->placeOrder(true, 10, 100, 5);
    EXPECT_EQ(book->getVolumeAtLimit(100), 10);
    // Buy:
    // 10 @ 100
    // 5 @ 101
    book->placeOrder(true, 5, 101, 5);
    // Buy:
    // 10 @ 100
    // 5 @ 101
    // 10 @ 100
    book->placeOrder(true, 10, 100, 5);
    // Sell:
    // 10 @ 110
    book->placeOrder(false, 10, 110, 5);
    // Buy:
    // 10 @ 100
    // 5 @ 101
    // 10 @ 100
    // Sell:
    // 5 @ 110
    book->placeOrder(true, 5, 110, 5);
    // Sell:
    // 5 @ 110
    // 5 @ 120
    book->placeOrder(false, 5, 120, 5);
    // Sell:
    // 5 @ 110
    // 5 @ 120
    book->placeOrder(false, 100, 25, 5);
}

TEST(BookTests, Basic3) {
    Book *book = new Book();
}

// Test both removals..through the book? yup
