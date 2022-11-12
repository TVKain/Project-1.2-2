#include "priority_queue.hpp"
#include <iostream>
#include <functional>
#include <algorithm>

int main() {
    ds::array_list<int> v = {10, 2, 3, -10, 100};
    ds::priority_queue<int> a(std::less<int>(), v);

    ds::priority_queue<int> b(a);

    ds::priority_queue<int> c = a;

    if (a.top() != 100) {
        return 1;
    }
    
    a.pop();

    if (a.top() != 10) {
        return 1;
    }

    a.push(200);

    if (a.top() != 200) {
        return 1;
    }

    ds::priority_queue<int> d = {100, 200, 300, -100, 1000};

    std::cout << d.top();

    if (d.top() != 1000) {
        return 1;
    }


    ds::priority_queue<int, ds::array_list<int>, std::greater<int>> f(std::greater<int>(), v);

    if (f.top() != -10) {
        return 1;
    }

    return 0;
}