// student id: 20538991

#include <iostream>
#include <vector>
#include <algorithm>
#include "Pivoting.h"
#include <functional>

#include <string_view>

using namespace std;

void my_questing_sort_in_place(vector<int> &elems);
// void merge_sort(vector<int> &elems, size_t start, size_t end);
//void swap(vector<int> &elems, size_t start, size_t end);

// int main() {
//     vector<int> v {-5,9,3,30,-4,10,98,-6,11,44,-9,77,50,12,67, 13};
//     //{1,2,3,4,5,6,7};
//     //{-5,9,3,30,-4,10,98,-5,10,44,-9,77,50,10,67};
//     //{6,4,6,3,5,7,8,5,3,9};
//     //{-5,9,3,30,-4,10,98,-5,10,44,-9,77,50,10,67}
//     for (int i : v) cout << to_string(i) << " ";
//     cout << endl;
//     // size_t x = Pivoting<int>::_partition(v, 0, v.size() - 1);
//     Pivoting<int>::do_qsort(v);
//     //cout << to_string(x) << endl;
//     for (int i : v) cout << to_string(i) << " ";
//     cout << endl;
//     vector<int> k {-5,9,3,30,-4,10,98,-6,11,44,-9,77,50,12,67, 13};
//     int i = Pivoting<int>::find_median(k);
//     //cout << i << endl;
//     cout << "function returns: " << i << " actual : " << v.at(v.size()/2) << endl;
// }

void my_questing_sort_in_place(vector<int> &a) {
    std::sort(a.begin(), a.end());
//     int k, pos, arraySize;
//     int tmp;
    
//    arraySize = a.size();
//    for( pos = 1; pos < arraySize; pos++ )
//    {
//       tmp = a[pos];
//       for( k = pos; k > 0 && tmp < a[k-1]; k-- )
//          a[k] = a[k-1];
//       a[k] = tmp;
//    }
}

// void merge_sort(vector<int> &elems, size_t start, size_t end) {
//     //out << end-start << endl;
//     // if (end - start < 1) {
//     //     // if (end - start == 1) {
//     //     //     if (elems.at(end) < elems.at(start)) swap(elems, start, end);
//     //     // }
//     //     return;
//     // }
//     if (start < end) {
//         size_t mid = start + (end-1)/2;
//         merge_sort(elems,0,mid);
//         merge_sort(elems, mid+1, end);
//         //cout << "merge " << start << " " << end << " done" << endl;
//         //for (int i : elems) cout << i << " ";
//         //cout << endl;
//         // size_t second = mid + 1;
//         // while (start <= mid && second <= end) {
//         //     if (elems.at(start) <= elems.at(second)) start++;
//         //     else {
//         //         int value = elems.at(second);
//         //         size_t index = second;
//         //         while (index != start) {
//         //             elems.at(index) = elems.at(index - 1);
//         //             index--;
//         //         }
//         //         elems.at(start) = value;
//         //         start++;
//         //         mid++;
//         //         second++;
//         //     }
//         // }
//     }
// }

void swap(vector<int> &elems, size_t start, size_t end) {
    int temp = elems.at(start);
    elems.at(start) = elems.at(end);
    elems.at(end) = temp;
}


