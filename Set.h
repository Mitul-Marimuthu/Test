//student id: 20538991
//stilted stilt on stilts
#include <vector>
#include <iostream>
#include <sstream>
#ifndef Set_h
#define Set_h

using namespace std;

template <typename T>
class Set {
    private: 
        vector<T> *_master_ptr;
        vector<size_t> _elems;
        size_t _sum;

    public:
        Set(vector<T> *mast_ptr = nullptr): _master_ptr(mast_ptr), _sum(0) {}

        const size_t size() const { return _elems.size(); }
        const vector<T> *get_master_ptr() const { return _master_ptr; }
        const size_t get_sum() const { return _sum; }

        bool add_elem(size_t n); // n is the index in master
        bool add_all_elems(); // add everything in the master

        Set<T> find_biggest_subset_le(size_t target);

        friend ostream &operator<<(ostream& os, const Set<T> &set) {
            const vector<T> *mast_ptr = set.get_master_ptr();
            os << "{\n";
            for (size_t index : set._elems)
                os << " " << mast_ptr->at(index) << "\n";
            return os << "}";
        }

        friend class Tests;
};

template <typename T> bool Set<T>::add_elem(size_t n) { 
    if (_master_ptr == nullptr || n >= _master_ptr->size()) return false;
    _elems.push_back(n); 
    _sum = _sum + _master_ptr->at(n);
    return true;
}
template <typename T> bool Set<T>::add_all_elems() {
    if (_master_ptr == nullptr) return false;
    for (size_t i = 0; i < _master_ptr->size(); ++i) {
        _elems.push_back(i);
    }
    return true;
}

template <typename T> Set<T> Set<T>::find_biggest_subset_le(size_t target) {
    if (target == 0 || _master_ptr == nullptr) return Set<T>(_master_ptr);
    vector<Set<T>> options;
    Set<T> min(_master_ptr);
    size_t min_sum = target;
    for (size_t i = 0; i < _master_ptr->size(); i++) {
        for (size_t j = 0; j < options.size(); j++) {
            Set<T> temp = options.at(j);
            if (temp.size() > 0 && temp._elems.back() == i) break;
            size_t sum = temp.get_sum() + _master_ptr->at(i);
            if (sum > target) continue;
            temp.add_elem(i);
            if (target - temp.get_sum() < min_sum ) {
                min_sum = target - temp.get_sum();
                min = temp;
            }
            options.push_back(temp);
            if(temp.get_sum() == target) { 
                return temp; 
            }

        }
        Set<T> temp2(_master_ptr);
        temp2.add_elem(i);
        options.push_back(temp2);
    }
    return min;
}

#endif /* Set_h */




