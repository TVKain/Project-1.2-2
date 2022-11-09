#include "array_list.hpp"

int main() {
    ds::array_list<int> a = {1,2,3,4};

    if (a.size() != 4) {
        return 1;
    }

    if (a.at(0) != 1) {
        return 1;
    }

    a.clear();

    if (a.size() != 0) {
        return 1;
    }

    a.push_back(4);
    a.push_back(2);
    a.push_back(69);

    if (a.size() != 3) {
        return 1;
    }

    if (a[1] != 2) {
        return 1;
    }


    return 0;
}