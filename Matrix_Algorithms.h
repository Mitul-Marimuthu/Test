// student id: 20538991

#include <vector>
#include <iostream>
#include <list>
#include <cmath>
#include "Sparse_Matrix.h"
#include "Matrix.h"

#ifndef Matrix_Algorithms_h
#define Matrix_Algorithms_h

using namespace std; 

class Mx {
    public:
        template <typename T> static bool can_multiply(const Matrix<T> &a, const Matrix<T> &b) {
            size_t n1 = a.get_num_cols();
            size_t n2 = b.get_num_rows();
            if (n1 == 0 || n2 == 0) return false;
            return n1 == n2;
        }

        template <typename T> static bool multiply(const Matrix<T> &a, const Matrix<T> &b,  Matrix<T> &res) {
            if (!can_multiply(a,b)) return false;
            size_t n = b._rows.size();
            res.resize(a._rows.size(), b._rows.at(0).size());
            for (size_t i = 0; i < a._rows.size(); ++i) {
                for (size_t j = 0; j < b._rows[0].size(); ++j) {
                    for (size_t k = 0; k < n; k++) {
                        cout << i << " " << j << " " << k << " " << endl;
                        res.at(i,j) += a._rows.at(i).at(k) * b._rows.at(k).at(j);
                    }
                }
            }
            return true;
        }

        template <typename T> static bool can_multiply(const Sparse_Matrix<T> &a,
            const Sparse_Matrix<T> &b) {
                size_t n1 = a.get_num_cols();
                size_t n2 = b.get_num_rows();
                return n1 != 0 && n2 != 0 && n1 == n2;
                //return (a.get_num_cols() != 0 && b.get_num_rows() != 0) && ();
                //return true; 
            }
        template <typename T> static bool add_to_cell(Sparse_Matrix<T> &spmat, size_t r,
            size_t c, const T &val) {
                if (!spmat.is_valid(r,c)) return false;
                list<typename Sparse_Matrix<T>::Node> *l = &spmat._rows.at(r);
                auto it = l->begin();
                for (it = l->begin(); it != l->end(); ++it) {
                    size_t col = it->get_col();
                    if (col < c) continue;
                    else if (col > c) break;
                    else {
                        if (spmat.is_default(val+it->get_val())) {
                            l->erase(it);
                            return true;
                        }
                        it->set_val(val + it->get_val());
                        return true;
                    }
                }
                if (spmat.is_default(val)) return false;
                typename Sparse_Matrix<T>::Node n (c, val);
                it--;
                l->insert(it, n);
                return true; 
            }
        template <typename T> static bool multiply(const Sparse_Matrix<T> &a,
            const Sparse_Matrix<T> &b, Sparse_Matrix<T> &res) { 
                if (!can_multiply(a,b)) return false;
                res._rows.resize(a.get_num_rows());
                res._num_rows = res._rows.size();
                res._num_cols = b.get_num_cols();
                for (size_t i = 0; i < a.get_num_rows(); ++i) {
                    for (auto ita = a._rows.at(i).begin(); ita != a._rows.at(i).end(); ++ita) {
                        size_t col = ita->get_col();
                        for (auto itb = b._rows.at(col).begin(); itb != b._rows.at(col).end(); ++itb) {
                            add_to_cell(res,i,itb->get_col(),ita->get_val()*itb->get_val());
                        }
                    }
                }
                // for (size_t i =0; i < a.get_num_rows(); ++i) {
                //     for (size_t j = 0; j < b.get_num_cols(); ++j) {
                //         for (auto it = a._rows.at(i).begin(); it != a._rows.at(i).end(); ++it) {
                //             add_to_cell(res,i,j,it->get_val()*b.get(it->get_col(),j));
                //         }
                //     }
                // }
                return true;
                // size_t nr = ceil(log(a.get_num_cols())/log(2));
                // nr = pow(2,nr);
                // Matrix<T> ta = a.get_slice(0,0,nr,nr);
                // Matrix<T> tb = b.get_slice(0,0,nr,nr);
                // //Sparse_Matrix<T> c(a.get_num_rows(), b.get_num_cols());
                // //res.resize(a._rows.size(), b._rows.at(0).size());
                // res._rows.resize(a.get_num_rows());
                // res._num_rows = res._rows.size();
                // res._num_cols = b.get_num_cols();
                //helper(ta,tb,res,nr,0,0,0,0);
                // for (size_t i = 0; i < a.get_num_rows(); ++i) {
                //     if (a._rows.at(i).size() == 0) continue;
                //     for (size_t j = 0; j < b.get_num_cols(); ++j) {
                //         for (size_t k = 0; k < n; k++) {
                //             //cout << i << " " << j << " " << k << " " << endl;
                //             add_to_cell(res,i,j,a.get(i,k) * b.get(k,j));
                //         }
                //     }
                // }
                //res = c; 
                return true;
            }
        //    
        //     //cout << "A" << nr << endl;
        //     res.resize(nr,nr);
            
        //     //cout << a._rows.size() << " " << b._rows.at(0).size();
        //     //a.resize(nr,nr);
        //     //b._rows.resize(nr,T());
        //     // Matrix<T> t1 = a;
        //     // Matrix<T> t2 = b;
        //     // t1.resize(nr,nr);
        //     // //a._rows.resize(nr);
        //     // //for (int i = 0; i < a._rows.size(); ++i) a._rows[i].resize(nr);
        //     // t2.resize(nr,nr);
        //     res = helper(a,b,res,nr, 0,0,0,0);
        //     res.resize(a._rows.size(), b._rows.at(0).size());
        //     return true;
        // }

        template <typename T> static void helper( Matrix<T> &a,  Matrix<T> &b, Sparse_Matrix<T> &res, size_t size ,
            size_t r1, size_t r2, size_t r3, size_t r4) {
            if (size <= 2) {
                //Matrix<T> x(2,2);
                //if (a.at(r1,r2))
                T p1 = a.at(r1,r2) * (b.at(r3, r4+1) - b.at(r3+1,r4+1));
                T p2 = (a.at(r1,r2) + a.at(r1,r2+1)) * b.at(r3+1,r4+1);
                T p3 = (a.at(r1+1,r2) + a.at(r1+1,r2+1)) * b.at(r3,r4);
                T p4 = a.at(r1+1,r2+1) * (b.at(r3+1,r4) - b.at(r3,r4));
                T p5 = (a.at(r1,r2) + a.at(r1+1,r2+1)) * (b.at(r3,r4) + b.at(r3+1,r4+1));
                T p6 = (a.at(r1,r2+1) - a.at(r1+1,r2+1)) * (b.at(r3+1,r4) + b.at(r3+1,r4+1));
                T p7 = (a.at(r1,r2) - a.at(r1+1,r2)) * (b.at(r3,r4) + b.at(r3,r4+1));
                // add_to_cell(res,r1,r4,a.get(r1,r2)*b.get(r3,r4)+a.get(r1,r2+1)*b.get(r3+1,r4));
                // add_to_cell(res,r1,r4+1,a.get(r1,r2)*b.get(r3,r4+1)+a.get(r1,r2+1)*b.get(r3+1,r4+1));
                // add_to_cell(res,r1+1,r4,a.get(r1+1,r2)*b.get(r3,r4)+a.get(r1+1,r2+1)*b.get(r3+1,r4));
                // add_to_cell(res,r1+1,r4+1,a.get(r1+1,r2)*b.get(r3,r4+1)+a.get(r1+1,r2+1)*b.get(r3+1,r4+1));
                // x.at(0,0) = p5+p4-p2+p6;
                // x.at(0,1) = p1+p2;
                // x.at(1,0) = p3+p4;
                // x.at(1,1) = p5+p1-p3-p7;
                add_to_cell(res,r1,r4,p5+p4-p2+p6);
                add_to_cell(res,r1,r4+1,p1+p2);
                add_to_cell(res,r1+1,r4,p3+p4);
                add_to_cell(res,r1+1,r4+1,p5+p1-p3-p7);
                // size_t mid = (size)/2;
                // for (size_t i = r1; i < r1 + mid; ++i) {
                //     for (size_t j = r4; j < r2 + mid; ++j) {
                //         add_to_cell(res,i,j,x.at(i-r1,j-r2));
                //     } 
                // }
                //return x;
            }
            else {
                size_t mid = (size)/2;
                helper(a,b,res,size/2, r1, r2,r3,r4);
                helper(a,b,res,size/2, r1,r2+mid, r3+mid,r4);
                helper(a,b,res,size/2, r1,r2,r3,r4+mid);
                helper(a,b,res,size/2, r1,r2+mid,r3+mid,r4+mid);
                helper(a,b,res,size/2,r1+mid,r2,r3,r4);
                helper(a,b,res,size/2,r1+mid,r2+mid,r3+mid,r4);
                helper(a,b,res,size/2,r1+mid,r2,r3,r4+mid);
                helper(a,b,res,size/2,r1+mid,r2+mid,r3+mid,r4+mid);
                // Matrix<T> x = helper(a,b,res,size/2, r1, r2,r3,r4) + helper(a,b,res,size/2, r1,r2+mid, r3+mid,r4);
                // //cout << x;
                // Matrix<T> y = helper(a,b,res,size/2, r1,r2,r3,r4+mid) + helper(a,b,res,size/2, r1,r2+mid,r3+mid,r4+mid);
                // Matrix<T> c = helper(a,b,res,size/2,r1+mid,r2,r3,r4) + helper(a,b,res,size/2,r1+mid,r2+mid,r3+mid,r4);
                // Matrix<T> d = helper(a,b,res,size/2,r1+mid,r2,r3,r4+mid) + helper(a,b,res,size/2,r1+mid,r2+mid,r3+mid,r4+mid);
                //cout << "1" << endl;
                
                //cout << "2" << endl;
            //     for (size_t i = r1+mid; i < r1 + size; ++i) {
            //         for (size_t j = r2; j < r2 + mid; ++j) {
            //             //cout << "(" << i << "," << j << ")" << endl;
            //             add_to_cell(res,i,j,c.at(i-mid,j));
            //         } 
            //     }
            //     ///cout << "3" << endl;
            //     for (size_t i = r1; i < r1 + mid; ++i) {
            //         for (size_t j = r2+mid; j < r2 +size; ++j) {
            //             add_to_cell(res,i,j,y.at(i,j-mid));
            //         } 
            //     }
            //     //cout << "4" << endl;
            //     for (size_t i = r1+mid; i < r1 + size; ++i) {
            //         for (size_t j = r2+mid; j < r2 + size; ++j) {
            //             add_to_cell(res,i,j, d.at(i-mid,j-mid));
            //         } 
            //     }
            // }
            // Matrix<T> m;
            // return m;
            }
        }

        
};

// the mockingbird on netflix
#endif /* Matrix_Algorithms_h */