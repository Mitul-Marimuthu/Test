//student id: 20538991

#include <vector>
#include <iostream>
#include <sstream>
#include <list>
#include "Matrix.h"

#ifndef Sparse_Matrix_h
#define Sparse_Matrix_h

using namespace std;

template <typename T>
class Sparse_Matrix {
    private:
        static double constexpr FLOOR = 1e-10;
        
        struct Node {
            size_t _col;
            T _val;

            Node(size_t c = 0, const T &v = T()) : _col(c), _val(v) {}
            size_t get_col() const { return _col; }
            const T get_val() const { return _val; }
            void set_val(const T &val) { _val = val; }
            virtual const T &operator=(const T &val) { return _val = val; }

            friend ostream& operator<<(ostream& os, const Node &node) {
                return os << "{ C: " << node._col << ", V: " << node._val << " }";
            }
        };

        vector<list<Node>> _rows;
        size_t _num_rows, _num_cols;
        T _default_val;

    public:
        Sparse_Matrix(size_t nr = 0, size_t nc = 0, const T &default_val = T()) :
             _num_rows(nr), _num_cols(nc), _default_val(default_val) {
             _rows.resize(_num_rows);
            //for (list<Node> &l : _rows) l.resize(_num_cols);
        }

        size_t get_num_rows() const { return _num_rows; };
        size_t get_num_cols() const { return _num_cols; };

        bool is_valid (size_t r, size_t c) const {
            if (r >= _num_rows || c >= _num_cols) return false;
            if ( r < 0 || c < 0) return false;
            return true;
        } 
        void clear() {
            for (list<Node> &l : _rows) {
                 l.clear();
            //     l.resize(_num_cols);
            }
            //for (list<Node> &l : _rows) l.resize(_num_cols);
        }
        const T get(size_t r, size_t c) const {
            if (!is_valid(r,c) ) return _default_val;
            list<Node> l = _rows.at(r);
            auto it = l.begin();
            for (it = l.begin(); it != l.end(); ++it) {
                if (it->get_col() == c) return it->get_val();
                if (it->get_col() > c) break;
            }
            return _default_val;
        }
        bool set(size_t row, size_t col, const T &val) {
            if (!is_valid(row,col)) return false;
            //if (row >= _rows.size()) _rows.resize(row+1);
            list<Node> *l = &_rows.at(row);
            auto it = l->begin();
            for (it = l->begin(); it != l->end(); ++it) {
                size_t c = it->get_col();
                if (c < col) continue;
                else if (c > col) break;
                else {
                    if (val == _default_val) {
                        l->erase(it);
                        return true;
                    }
                    it->set_val(val);
                    return true;
                }
            }
            if (val == _default_val) return false;
            Node n (col, val);
            it--;
            l->insert(it, n);
            return true;
        }
        Matrix<T> get_slice(size_t r1, size_t c1, size_t r2, size_t c2) const {
            size_t tl = r1 > r2 ? r2 : r1;
            size_t tc = c1 > c2 ? c2 : c1;
            size_t rows = r2 > r1 ? r2-r1 : r1-r2;
            size_t cols = c2 > c1 ? c2-c1 : c1-c2;
            Matrix<T> m(rows+1,cols+1);
            for (size_t r = 0; r <= rows; r++) {
                for (size_t c = 0; c <= cols; c++) {
                    m.at(r,c) = this->get(tl + r, tc + c);
                }
            }
            return m;
        }

        bool is_default(const double &val) {
            return abs(val - _default_val) < FLOOR;
        }

        friend class Tests;
        friend class Mx;
};

//A code more cormorant

/*template <typename T> bool Sparse_Matrix<T>::is_valid (size_t r, size_t c) const {
    if (r >= _num_rows || c >= _num_cols) return false;
    return true;
}

template <typename T> void Sparse_Matrix<T>::clear() {
    for (list<Sparse_Matrix::Node> l : _rows) {
        l.clear();
    }
    for (list<Sparse_Matrix::Node> l : _rows) l.resize(_num_cols);
}

template <typename T> const T Sparse_Matrix<T>::get(size_t r, size_t c) const {
    if (!is_valid(r,c)) return _default_val;
    list<Sparse_Matrix::Node> l = _rows.at(r);
    auto it = l.begin();
    for (it = l.begin(); it != l.end(); ++it) {
        if (it->get_col() == c) return it->get_val();
        if (it->get_col() > c) break;
    }
    return _default_val;
}

template <typename T> bool Sparse_Matrix<T>::set(size_t row, size_t col, const T &val) {
    if (!is_valid(row,col)) return false;
    list<Sparse_Matrix::Node> l = _rows.at(row);
    auto it = l.begin();
    for (it = l.begin(); it != l.end(); ++it) {
        size_t c = it->get_col();
        if (c < col) continue;
        else if (c > col) break;
        else {
            if (val == _default_val) {
                l.erase(it);
            }
            it->set_val(val);
            return true;
        }
    }
    if (val == _default_val) return true;
    Sparse_Matrix::Node n (col, val);
    l.insert(it, n);
    return true;
}

template <typename T> Matrix<T> Sparse_Matrix<T>::get_slice(size_t r1, size_t c1, size_t r2, size_t c2) const {
    size_t rows = r2-r1, cols = c2-c1;
    Matrix<T> m(rows+1,cols+1);
    for (size_t r = 0; r < rows; r++) {
        for (size_t c = 0; c < cols; c++) {
            m.at(r,c) = get(r1 + r, c1 + c);
        }
    }
    return m;
}*/

#endif /* Sparse_Matrix_h */