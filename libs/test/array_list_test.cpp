#include "array_list.hpp"
#include <iostream>

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

    ds::array_list<ds::array_list<int>> v = { {1,2,3,4},{5,6,7,8} };

    v.insert(v.begin(), {9,8,2,1});

    for (int i = 0; i < v.size(); ++i) {
        for (int j = 0; j < v[0].size(); ++j) {
            std::cout << v[i][j] << " ";
        }
        std::cout << std::endl;
    }    

    ds::array_list<ds::array_list<int>> v1 = { 
        {9,8,2,1}, {1,2,3,4},{5,6,7,8} };

    auto z = v1[1];

    v1.erase(v1.begin());




    return 0;
}