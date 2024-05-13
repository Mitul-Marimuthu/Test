#include <iostream>
#include <vector>
#include "Hash_Table_LP.h"
#include "Hash_Table_QP.h"
using namespace std;

int main() {
    size_t i = 1;

    cout << to_string(i) << endl;
    while( i < 1000) {
        i = Hash_Table_QP<int>::_next_prime(i);
        cout << to_string(i) << endl;
    }
}