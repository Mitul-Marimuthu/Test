#include <vector>
#include <iostream>
#include <sstream>
#include "Set.h"

using namespace std;

int main() {
    vector<int> master {15, 5, 3, 1, 5};
    size_t master_total = 0;
    for (int i : master) master_total += i;

    size_t target = 14;
    //for (int i : master) cout << " " << i;
    Set<int> master_set(&master);
    master_set.add_all_elems();
    Set<int> best_subset = master_set.find_biggest_subset_le(target);

    cout << master_set << endl;
    cout << "Target = " << target << endl;
    cout << "Best sum =" << best_subset.get_sum() << endl;
    cout << best_subset << endl;
}
