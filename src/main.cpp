#include <iostream>
#include <chrono>
#include <functional>
#include <vector>

#include "array_list.hpp"
#include "complete_graph.hpp"
#include "util.hpp"

int main() {
    std::vector<std::vector<int>> v = { {1,2,3,4},{5,6,7,8} };

    v.insert(v.begin(), {9,8,2,1});

    for (int i = 0; i < v.size(); ++i) {
        for (int j = 0; j < v[0].size(); ++j) {
            std::cout << v[i][j] << " ";
        }
        std::cout << std::endl;
    }    


    return 0;
}