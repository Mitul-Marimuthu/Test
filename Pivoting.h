// student id: 20538991
// A butterfly in baltimore
#include <iostream>
#include <vector>

#ifndef Pivoting_h
#define Pivoting_h

using namespace std;
template <typename T>
class Pivoting {
    private :
        static size_t _partition(vector<T> &elems, size_t lo, size_t hi) {
            //if (hi - lo <= 1) return hi;
            size_t index = lo + (hi-lo)/2;
            T pivot = elems.at(index);
            size_t left = lo;
            size_t right = hi;
            //cout << "lo: " << lo << " pivot: " << pivot << " hi: " << hi << endl;
            while (true) {
                while(elems.at(left) < pivot) left++;
                while(elems.at(right) > pivot) right--;
                //cout << "left: " << left << " right: " << right << endl;
                if ( left >= right) break;
                
                T temp = elems.at(left);
                elems.at(left) = elems.at(right);
                elems.at(right) = temp;
                left++; right--;
            }
            return right;
        }
        static void _do_qsort(vector<T> &elems, size_t lo, size_t hi) {
            size_t i;
            if (hi - lo <= 1) {
                if (hi - lo == 1 && elems.at(lo) > elems.at(hi)) {
                    T temp = elems.at(lo);
                    elems.at(lo) = elems.at(hi);
                    elems.at(hi) = temp;
                }
                return;
            }
            for (i = lo; i < hi; i++) {
                if (elems.at(i) > elems.at(i+1))
                    break;
            }
            if (i == hi) return;
            size_t k = _partition(elems, lo, hi);
            _do_qsort(elems, lo, k);
            _do_qsort(elems, k+1, hi);
        }
        static T _find_kth_least_elem(vector<T> &elems, size_t lo, size_t hi, size_t k) {
            //return T();
            // if (k > hi) k = hi;
            // if (k < lo) k = lo;
            //if (lo > hi) return elems.at(hi);
            //if (hi-lo <= 1) return k == hi ? elems.at(hi) : elems.at(lo);
            size_t index = _partition(elems, lo, hi);
            for (T t : elems) cout << t << " ";
            //cout << endl;
            //cout << "partitioned at: " << index << " lo: " << lo << " hi : " << hi << endl;
            if (hi-lo <= 1) return k == hi ? elems.at(hi) : elems.at(lo);
            
            if ( hi - lo <= 1 && k == index) {
                //cout << "equals" << " size: " << hi-lo + 1 << endl;
                return elems.at(index);
            }
            else if (k <= index) {
                //cout << "less than" << endl;
                return _find_kth_least_elem(elems, lo, index, k);
            } 
            //cout << "greater than" << endl;
            return _find_kth_least_elem(elems, index+1, hi, k); 
        }

    public :
        static T find_median(vector<T> &elems) {
            //cout << "median: " << elems.size()/2 << endl;
            T temp = find_kth_least_elem(elems, elems.size()/2);
            return temp;
        }
        static T find_kth_least_elem(vector<T> &elems, size_t k) {
            if ( k <  0 || k >= elems.size()) return T();
            //cout << k << endl;
            T temp = _find_kth_least_elem(elems, 0, elems.size() -1, k);
            //cout << "returned" << endl;
            return temp;
        }
        static void do_qsort(vector<T> &elems) {
            _do_qsort(elems, 0, elems.size() -1);
        }
        friend class Tests;
};

#endif /* Pivoting_h */