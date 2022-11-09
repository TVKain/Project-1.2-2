#include "merge_sort.hpp"
#include "array_list.hpp"
#include <algorithm>
#include <iostream>

int main() 
{
    ds::array_list<int> a = {3, 2, 1, 8, 6, 7, 0, -10, 20, 30, 100, -44};

    algo::sort::merge_sort_iterative(a.begin(), a.end());

    ds::array_list<int> b = {8, 9, 3, -100, 20, 15, 22, 23, 24, 25, 9};

    algo::sort::merge_sort_iterative(b.begin(), b.end());
    
    if (!std::is_sorted(a.begin(), a.end()) || !std::is_sorted(b.begin(), b.end())) {
        return 1;
    }

    return 0;
}