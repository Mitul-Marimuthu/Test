// student id: 20538991
// chump - the shark
#include <iostream>
#include <vector>

#ifndef Hash_Table_LP_h
#define Hash_Table_LP_h

using namespace std;

template <typename T> size_t Hash(const T &item);
template <typename T> class Hash_Table_LP {
    protected:
        struct Entry {
            T _data;
            enum STATE { ACTIVE, VACANT, DELETED } _state;
            Entry(const T &d = T(), STATE st = VACANT) : _data(d), _state(st) {}
        };

        static const size_t DEFAULT_INIT_CAPACITY = 3;
        vector<Entry> _elems;
        size_t _size;
        size_t _num_non_vacant_cells;
        float _max_load_factor;

        virtual size_t _get_hash_modulus(const T &item) const {
            return Hash<T>(item) % this->_elems.size();
        }
        
        virtual void _rehash() {
            vector<Entry> old = _elems;
            size_t old_size = _elems.size();
            _grow_capacity();
            for (size_t i = 0; i < old_size; ++i) {
                _elems.at(i)._state = Entry::VACANT;
            }
            _size = _num_non_vacant_cells = 0;
            for (size_t i = 0; i < old.size(); i++){
                if (old.at(i)._state == Entry::ACTIVE)
                    this->insert(old.at(i)._data);
            }
        }

        virtual bool set_max_load_factor(float x) {
            if (x <= 0 || x > this->_get_biggest_allowed_max_load_factor()) return false;
            _max_load_factor = x;
            return true;
        }
        virtual float _get_biggest_allowed_max_load_factor() const {
            return 0.75;
        }
        virtual size_t _find_pos(const T &item) const {
            if (_size >= _elems.size()) return string::npos;
            size_t start = this->_get_hash_modulus(item);
            size_t index = start;
            // if (_elems.at(index)._data == item) return index;
            // index++;
            while(_elems.at(index)._data != item && 
                _elems.at(index)._state != Entry::VACANT) {
                index++; 
                if (index >= _elems.size()) index -= _elems.size();
            }
            return index;
        }
        virtual void _grow_capacity() {
            _elems.resize(_elems.size() * 2);
        }
        

    public:
        
        Hash_Table_LP(size_t n = DEFAULT_INIT_CAPACITY) {
            _elems.resize(n);
            _size = 0;
            _num_non_vacant_cells = 0;
            _max_load_factor = this->_get_biggest_allowed_max_load_factor();
        }
        size_t get_size() const { return _size; }
        bool is_empty() const { return _size == 0; }
        bool contains(const T &item) const {
            size_t index = _find_pos(item);
            if (_elems.at(index)._state == Entry::VACANT) return false;
            //if (_elems.at(index)._state == Entry::DELETED) return false;
            return true;
        }
        T &find(const T &item) {
            size_t index = this->_find_pos(item);
            if (_elems.at(index)._state == Entry::VACANT) throw Not_found_exception();
            return _elems.at(index)._data;
        }
        bool clear() {
            if (_size == 0) return false;
            for (Entry e : _elems) {
                e._state = Entry::VACANT;
                e._data = T();
            }
            _size = _num_non_vacant_cells = 0;
            return true;
        }
        bool insert(const T &item) {
            if (_size >= _elems.size()) throw Table_full_exception();
            size_t index = this->_find_pos(item);
            if (_elems.at(index)._state == Entry::ACTIVE) return false;
            if (_elems.at(index)._state == Entry::DELETED) {
                _num_non_vacant_cells--;
            }
            _elems.at(index)._state = Entry::ACTIVE;
            _elems.at(index)._data = item;
            _size++;
            _num_non_vacant_cells++;

            if (_num_non_vacant_cells > _elems.size() *_max_load_factor)
                this->_rehash();
            return true;
        }
        bool remove(const T &item) {
            size_t index = this->_find_pos(item);
            if (_elems.at(index)._state == Entry::VACANT) return false;
            if (_elems.at(index)._state == Entry::DELETED) return false;
            _elems.at(index)._state = Entry::DELETED;
            _size--;
            return true;
        }

        class Table_full_exception : public exception {
            public : const string to_string() const throw() { return string("Table full exception"); }
        };
        class Not_found_exception : public exception {
            public : const string to_string() const throw() { return string("Not found exception"); }
        };
        
        friend class Tests;
};




#endif /* Hash_Table_h */
