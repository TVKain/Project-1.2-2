#include "heap.hpp"
#include "array_list.hpp"

#include <algorithm>

int main() {
    ds::array_list<int> a = {10, -1, 2, 3, 9, 2, 5};
    ds::array_list<int> b = {10, 9, 5, 3, -1, 2, 2};

    ds::array_list<int> c(a);
    ds::array_list<int> d = {-1, 3, 2, 10, 9, 2, 5};

    algo::heap::make_heap(a.begin(), a.end());

    if (!std::equal(a.begin(), a.begin() + a.size(), b.begin())) {
        return 1;
    }

    algo::heap::make_heap(c.begin(), c.end(), std::greater<int>());

    if (!std::equal(c.begin(), c.begin() + c.size(), d.begin())) {
        return 1;
    }


    algo::heap::pop_heap(a.begin(), a.end());
    a.pop_back();

    ds::array_list<int> e = {9, 3, 5, 2, -1, 2};


    if (!std::equal(a.begin(), a.begin() + a.size(), e.begin())) {
        return 1;
    }
    
    a.push_back(10);

    ds::array_list<int> f = {10, 3, 9, 2, -1, 2, 5};

    algo::heap::push_heap(a.begin(), a.end());

    if (!std::equal(a.begin(), a.begin() + a.size(), f.begin())) {
        return 1;
    }


    return 0;
}