#include <iostream>
#include <vector>
#include <algorithm>
#include <vector>
#include "Heap.h"
#include "Special_Heap.h"

using namespace std;
using namespace std::chrono;
//template <> int get_sentinal<int>() { return -500; }
int main() {
    vector<int> v(1000000);
    //for (int &i : v) i = rand()%10;
    auto f = []() -> int { return rand() % 100000; };
    generate(v.begin(), v.end(), f);
    Special_Heap<int> h(v);
    //for (int i : h._elems) cout << i << " ";
    auto start = high_resolution_clock::now();
    h.get_least_k(100000);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "Time taken by function: " << duration.count() << " milliseconds" << endl;
    //cout << endl;
    //cout << h._size << endl;
}