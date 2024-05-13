//student id: 20538991

#include <iostream>
#include <vector>
#include <cmath>
#include "Hash_Table_LP.h"

#ifndef Hash_Table_QP_h
#define Hash_Table_QP_h

template <typename T> 
class Hash_Table_QP : public Hash_Table_LP<T> {
    public :
        Hash_Table_QP(size_t n = Hash_Table_LP<T>::DEFAULT_INIT_CAPACITY) : Hash_Table_LP<T>(n) {
            this->_max_load_factor = this->_get_biggest_allowed_max_load_factor();
        }
    protected:
        virtual float _get_biggest_allowed_max_load_factor() const {
            return 0.49;
        }
        virtual size_t _find_pos(const T& item) const {
            if (this->_size >= this->_elems.size()) return string::npos;
            size_t start = this->_get_hash_modulus(item);
            size_t nextOdd = 1;
            //if (this->_elems.at(start)._data == item) return start;
            while(this->_elems.at(start)._data != item && 
                this->_elems.at(start)._state != Hash_Table_LP<T>::Entry::VACANT) {
                    start += nextOdd;
                    nextOdd += 2;
                    if (start >= this->_elems.size()) start -= this->_elems.size();
                }
                
            return start;
        }
        virtual void _grow_capacity() {
            this->_elems.resize(Hash_Table_QP<T>::_next_prime(2 * this->_elems.size()));
        }

        static size_t _next_prime(size_t n) {
            if (n <= 1) return 2;
            if (n <= 2) return 3;
            if (n <= 4) return 5;
            if (n <= 5) return 7;
            //cout << "lol" << endl;
            n++;
            for (long num = n%2 == 0 ? n+1 : n; true; num += 2) {
                if (num % 3 == 0 || num % 5 == 0)  continue;

                //bool is_prime = false;
                long k;
                long lim = ceil((sqrt((float)num))/6);
                for (k = 1; k <= lim; k++ ) {
                    if (num % (6*k-1) == 0 && num != 6*k - 1) break;
                    if (num % (6*k +1) == 0  && num != (6*k + 1)) break;
                }
                //cout << to_string(k) + " " << to_string(lim) << endl;
                if (k>lim) return (size_t)num;
            }
            return n;
        }

        friend class Tests;
};

#endif /* Hash_Table_QP_h */