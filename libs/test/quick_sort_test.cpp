#include "quick_sort.hpp"
#include "array_list.hpp"
#include <algorithm>
#include <functional>

int main() 
{
    ds::array_list<int> a = {3, 2, 1, 8, 6, 7, 0, -10, 20, 30, 100, -44};

    algo::sort::quick_sort_iterative(a.begin(), a.end());

    ds::array_list<int> b = {8, 9, 3, -100, 20, 15, 22, 23, 24, 25, 9};

    ds::array_list<int> c(b);
    ds::array_list<int> d(b);

    algo::sort::quick_sort_iterative(b.begin(), b.end(), std::greater<int>());
    
    if (!std::is_sorted(a.begin(), a.end()) || !std::is_sorted(b.begin(), b.end(), std::greater<int>())) {
        return 1;
    }

    algo::sort::quick_sort_recursive(c.begin(), c.end());
    algo::sort::quick_sort_recursive(d.begin(), d.end(), std::greater<int>());

    if (!std::is_sorted(c.begin(), c.end()) || !std::is_sorted(d.begin(), d.end(), std::greater<int>())) {
        return 1;
    }

    return 0;
}