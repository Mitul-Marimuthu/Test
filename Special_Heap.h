// student id: 20538991

#include <iostream>
#include <vector>
#include "Heap.h"

#ifndef Special_Heap_h
#define Special_Heap_h

using namespace std;

template <typename T>
class Special_Heap : public Heap<T> {
    public:
        Special_Heap() : Heap<T>() {};
        Special_Heap(const vector<T> &vec) : Heap<T>(vec) {}

        const vector<T> &get_least_k(size_t k) {
            if ( k <= 0 || k > this->_size) return this->_elems;
            for (size_t i = 0; i < k; ++i) {
                T temp = this->peek_min();
                this->delete_min();
                this->_elems.at(this->_size + 1) = temp;
            }
            this->_size = 0;
            return this->_elems;
        }
        friend class Tests;
};

#endif /* Special_Heap_h */