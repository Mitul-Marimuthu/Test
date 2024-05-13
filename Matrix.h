// student id: 20538991

#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>
#include <ios>

#ifndef Matrix_h
#define Matrix_h

using namespace std;

template <typename T>
class Matrix {
    protected:
        vector<vector<T>> _rows;

    public:
        Matrix(size_t nr = 0, size_t nc = 0);

        size_t get_num_rows() const { return _rows.size(); };
        size_t get_num_cols() const { return (_rows.size()>0? _rows[0].size() : 0); };
        void clear() {_rows.clear(); }

        void resize(size_t nr, size_t nc);
        T &at(size_t r, size_t c);
        string to_string() const;

        class OOB_exception : public exception {
            public: string what() { return "Out of bounds access"; }
        };

        friend ostream& operator<<(ostream& os, const Matrix<T> &mat) {
            return os << mat.to_string();
        }

        friend bool operator==(const Matrix<T> &m1, const Matrix<T> &m2) {
            if (m1.get_num_rows() != m2.get_num_rows()) return false;
            if (m1.get_num_cols() != m2.get_num_cols()) return false;
            for (size_t i = 0; i < m1.get_num_rows(); ++i) {
                for (size_t j = 0; j < m1.get_num_cols(); j++) {
                    if (m1._rows.at(i).at(j) != m2._rows.at(i).at(j)) return false;
                }
            }
            return true;
        }

        friend bool operator!=(const Matrix<T> &m1, const Matrix<T> &m2) {
            return !(m1 == m2);
        }

        friend Matrix<T> operator+(const Matrix<T> &m1, const Matrix<T> &m2) {
            Matrix<T> ret(m1.get_num_rows(), m1.get_num_cols());
            for (size_t i = 0; i < ret.get_num_rows(); ++i) {
                for (size_t j = 0; j < ret.get_num_cols(); ++j) {
                    ret.at(i,j) = m1._rows.at(i).at(j) + m2._rows.at(i).at(j);
                }
            }
            return ret;
        }

        friend class Tests;
        friend class Mx;
};

template <typename T> Matrix<T>::Matrix(size_t nr, size_t nc) {
    resize(nr, nc);
}

template <typename T> void Matrix<T>::resize(size_t nr, size_t nc) {
    _rows.resize(nr);
    for (vector<T> &v : _rows) { v.resize(nc); }
}

template <typename T> T &Matrix<T>::at(size_t r, size_t c) {
    if (r >= _rows.size() || c >= _rows[0].size())
        throw OOB_exception();
    return _rows.at(r).at(c); 
}

template <typename T> string Matrix<T>::to_string() const {
    stringstream str;
    //str.right;
    // << right;
    str << "# Matrix\n";
    for (vector<T> v : _rows) {
        for (size_t i = 0; i < v.size(); ++i) {
            str << setw(6) << v.at(i);
            if (i == v.size() -1 ) continue;
            str << " ";
        }
        str << "\n";
    }
    return str.str(); 
}

#endif /* Matrix_h */