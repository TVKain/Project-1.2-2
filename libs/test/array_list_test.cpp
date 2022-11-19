#include "array_list_fix.hpp"
#include <iostream>

int main() {
    array_list<array_list<int>> a;

    array_list<int> b;
    b.push_back(4);
    b.push_back(5);

    array_list<int> c;
    c.push_back(10);

    a.push_back(b);
    a.push_back(c);

    a.pop_back();

    return 0;
}