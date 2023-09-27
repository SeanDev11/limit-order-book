#ifndef HEAP_HPP
#define HEAP_HPP

#include <cmath>
#include <vector>
#include "iostream"
#include "Limit.hpp"

enum tree_type { ask, bid };

class Heap {
  private:
    //Limit **limits;
    std::vector<Limit*> limits;
    int max_capacity;
    int size;

    int parent(int i) {
      return (i-1)/2;
    }

    int left(int i) {
        return (2*i) + 1;
    }

    int right(int i) {
        return (2*i) + 2;
    }

    void swap(Limit* &x, Limit* &y) {
        Limit *temp = x;
        int temp_idx = x->get_tree_idx();
        x->set_tree_idx(y->get_tree_idx());
        y->set_tree_idx(temp_idx);
        x = y;
        y = temp;
    }

  public:
    Heap(int cap) {
        size = 0;
        max_capacity = cap;
        //limits = new Limit*[cap];
        limits.reserve(max_capacity);
    }

    int height() {
        return ceil(log2(size + 1)) - 1;
    }

    template<tree_type>
    void insert(Limit *limit);

    template<>
    void insert<ask>(Limit *limit) {
        if (size == max_capacity) {
            std::cout << "Overflow, could not insert" << std::endl;
            return;
        }

        // Insert new limit at end
        size++;
        int i = size - 1;
        limits[i] = limit;
        limits[i]->set_tree_idx(i);
        // Maintain heap property
        while (i != 0 && limits[parent(i)]->limit_price > limits[i]->limit_price) {
            swap(limits[i], limits[parent(i)]);
            i = parent(i);
        }
    }

    template<>
    void insert<bid>(Limit *limit) {
        if (size == max_capacity) {
            std::cout << "Overflow, could not insert" << std::endl;
            return;
        }

        // Insert new limit at end
        size++;
        int i = size - 1;
        limits[i] = limit;
        limits[i]->set_tree_idx(i);
        // Maintain heap property
        while (i != 0 && limits[parent(i)]->limit_price < limits[i]->limit_price) {
            swap(limits[i], limits[parent(i)]);
            i = parent(i);
        }
    }

    template<tree_type>
    void remove(Limit *limit);

    template<>
    void remove<ask>(Limit *limit) {
        size--;
        /*Limit *toDelete = limit;
        size_t swapped_idx = toDelete - limits[0];*/
        int swapped_idx = limit->get_tree_idx();
        if (swapped_idx == size) {
            // Delete limit object
            delete limits[size];
            limits[size] = nullptr;
            return;
        }

        bool is_greater = limits[size]->limit_price > limit->limit_price;

        swap(limits[swapped_idx], limits[size]);

        if (is_greater) {
            sift_down_min(swapped_idx);
        } else {
            sift_up_min(swapped_idx);
        }

        // Should also check if the orders LL needs deleting
        // Would increase time complexity
    }

    template<>
    void remove<bid>(Limit *limit) {
        size--;
        /*Limit *toDelete = limit;
        std::cout << "TEST " << &limit - &limits[0] << std::endl;
        std::cout << limits[0] << std::endl;
        size_t swapped_idx = limit - limits[0];*/
        int swapped_idx = limit->get_tree_idx();
        if (swapped_idx == size) {
            // Delete limit object
            //delete toDelete;
            //toDelete = nullptr;
            delete limits[size];
            limits[size] = nullptr;
            return;
        }

        bool is_greater = limits[size]->limit_price > limit->limit_price;
        swap(limits[swapped_idx], limits[size]);

        if (is_greater) {
            sift_up_max(swapped_idx);
        } else {
            sift_down_max(swapped_idx);
        }
    }

    void sift_up_min(int i) {
        while (i > 0) {
            int j = parent(i);
            if (limits[i]->limit_price < limits[j]->limit_price) {
                swap(limits[i], limits[j]);
                i = j;
            } else {
                break;
            }
        }
    }

    void sift_down_min(int i) {
        while (true) {
            int l = left(i);
            int r = right(i);

            int max_idx = i;
            if (l < size && (limits[l]->limit_price < limits[i]->limit_price)) {
                max_idx = l;
            }
            if ((r < size) && (limits[r]->limit_price < limits[l]->limit_price)
            && (limits[r]->limit_price < limits[i]->limit_price)) {
                max_idx = r;
            }
            if (max_idx == i) {
                break;
            }
            swap(limits[i], limits[max_idx]);
            i = max_idx;
        }
    }

    void sift_up_max(int i) {
        while (i > 0) {
            int j = parent(i);
            if (limits[i]->limit_price > limits[j]->limit_price) {
                swap(limits[i], limits[j]);
                i = j;
            } else {
                break;
            }
        }
    }

    void sift_down_max(int i) {
        while (true) {
            int l = left(i);
            int r = right(i);

            int max_idx = i;
            if ((l < size) && (limits[l]->limit_price > limits[i]->limit_price)) {
                max_idx = l;
            }
            if ((r < size) && (limits[r]->limit_price > limits[l]->limit_price)
            && (limits[r]->limit_price > limits[i]->limit_price)) {
                max_idx = r;
            }
            if (max_idx == i) {
                break;
            }
            swap(limits[i], limits[max_idx]);
            i = max_idx;
        }
    }

    int get_size() {
        return size;
    }

    int get_max_capacity() {
        return max_capacity;
    }

    Limit* peek_root() {
        return limits[0];
    }

    Limit* get_limit_at(int i) {
        return limits[i];
    }

    int is_empty() {
        return size == 0;
    }

    ~Heap() {
        for (int i = 0; i < size; i++) {
            delete limits[i];
            limits[i] = nullptr;
        }
        //delete[] limits;
        //limits = nullptr;
    }
};

#endif
