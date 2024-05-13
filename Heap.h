//student id: 20538991
// Universal mouse
#include <iostream>
#include <vector>
#include <sstream>

#ifndef Heap_h
#define Heap_h

using namespace std;
template <typename T> T get_sentinel() {}

template <> 
int get_sentinel<int>() { return -500; }

template <typename T>
class Heap {
    public:
        vector<T> _elems;
        size_t _size;
        static const int INIT_HEAP_CAPACITY = 128;

        bool _percolate_down(size_t pos) {
            if (pos < 1 || pos > _size) return false;
            size_t hole = pos;
            size_t child;
            T temp;
            for (temp = _elems.at(hole); hole *2 <= _size; hole = child) {
                child = 2*hole;
                if (child < _size && _elems.at(child + 1) < _elems.at(child))
                    child++;
                if (_elems.at(child) < temp) {
                    _elems.at(hole) = _elems.at(child);
                }
                else 
                    break;
            }
            _elems.at(hole) = temp;
            return true;
        }
        bool _heapify() {
            if (_size == 0) return false;
            size_t i;
            for (i = _size/2; i > 0; i--)
                _percolate_down(i);
            return true;
        }

    public:
        Heap() {
            _elems.resize(INIT_HEAP_CAPACITY);
            _size = 0;
            _elems.at(0) = get_sentinel<T>();
        }
        Heap(const vector<T>& vec) {
            size_t n = vec.size();
            _size = n;
            //size_t i;
            // for (i = INIT_HEAP_CAPACITY; i <= n; i = i*2) {
            //     if (i < 0) i = n+1;
            // }
            _elems.resize(n+1);
            //cout << _elems.size() << endl;
            _elems.at(0) = get_sentinel<T>();
            for (size_t i = 0; i < n; ++i) _elems.at(i+1) = vec.at(i);
            _heapify();
        }

        virtual bool is_empty() const { return _size == 0; }
        virtual bool insert(const T &elem) {
            if (_size >= _elems.size()-1) _elems.resize(_elems.size() * 2);
            //_elems.push_back(elem);
            _size++;
            size_t hole = _size;
            size_t parent;
            T temp;
            for (temp = elem; hole/2 > 0; hole = parent) {
                parent = hole/2;
                if (temp < _elems.at(parent))
                    _elems.at(hole) = _elems.at(parent);
                else 
                    break;
            }
            _elems.at(hole) = temp;
            return true;
        }
        virtual bool delete_min() {
            if (_size == 0) return false;
            _elems.at(1) = _elems.at(_size);
            //_size--;
            _percolate_down(1);
            _size--;
            return true;
        }
        virtual const T &peek_min() const {
            if (_size == 0) return _elems.at(0);
            return _elems.at(1);
        }

        virtual string to_string() const {
            stringstream ret;
            ret << "# Heap with min = " << _elems.at(1) << "\n";
            ret << "# Size = " << _size << "\n";
            for (size_t i = 1; i <= _size/2; ++i) {
                ret << _elems.at(i) << " : ";
                if (i*2 <= _size) ret << _elems.at(i*2) << " ";
                else ret << "-" << " ";
                if (i*2 + 1 <= _size) ret << _elems.at(i * 2 + 1);
                else ret << "-";
                ret << "\n";
            }
            ret << "# End of heap" << "\n";
            return ret.str();
        }

        friend class Tests;
};

#endif /* Heap_h */