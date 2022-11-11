#include "bubble_sort.hpp"
#include "array_list.hpp"

#include <algorithm>

int main() {
    ds::array_list<int> a = {5, 4, 3, 2, 1};

    algo::sort::bubble_sort(a.begin(), a.end());

    if (!std::is_sorted(a.begin(), a.end())) {
        return 1;
    }

    ds::array_list<int> b = {1,2,3,4,5};

    algo::sort::bubble_sort(b.begin(), b.end(), std::greater<int>());

    if (!std::is_sorted(b.begin(), b.end(), std::greater<int>())) {
        return 1;
    }

    return 0;
}