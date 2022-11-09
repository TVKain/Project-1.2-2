#include <iostream>
#include "array_list.hpp"
#include "complete_graph.hpp"

int main() {
    ds::array_list<ds::array_list<int>> cost_matrix = {
                                                        { 0, 10, 15, 20 },
{ 10, 0, 35, 25 },
{ 15, 35, 0, 30 },
{ 20, 25, 30, 0 } };
    complete_graph g(cost_matrix);

    auto [min, a] = g.tsp_brute_force(0);

    for (int i = 0; i < a.size(); ++i) {
        std::cout << a[i]+ 1 << " -> ";
    }
    std::cout << std::endl;
    std::cout << "Min: " << min;

    return 0;
}