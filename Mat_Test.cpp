#include <iostream>
#include <vector>
#include "Matrix.h"
#include "Sparse_Matrix.h"
#include "Matrix_Algorithms.h"
#include <list>

using namespace std;

int main() {
    //Matrix<int> m(5,5);
    //Sparce_Matrix<int> m(5,5);
    //string str = m.to_string();
    // list<int> m;
    // auto it = m.begin();
    // m.insert(it, 1);
    Matrix<int> m (4,4);
    Matrix<int> n (4,4);
    int counter = 0;
    for (int i = 0; i < m.get_num_rows(); ++i) {
        for (int j = 0; j < m.get_num_cols(); ++j) {
            m.at(i,j) = counter;
            counter++;
        }
    }
    for (int i = 0; i < n.get_num_rows(); ++i) {
        for (int j = 0; j < n.get_num_cols(); ++j) {
            n.at(i,j) = counter;
            counter++;
            counter %= 5;
        }
    }
    cout << m << endl << n << endl;
    Matrix<int> k;
    Mx::multiply(m,n,k);
    cout << k << endl;
    //m.resize(4);
    //for (int i : m) cout << i;
}