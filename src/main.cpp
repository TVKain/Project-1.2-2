#include <iostream>
#include <chrono>
#include <functional>
#include <vector>

#include "array_list.hpp"
#include "undirected_graph.hpp"
#include "util.hpp"

int main() {
    auto a = util::generate_cost_matrix(10, 500, 2500);

    ds::undirected_graph g(a);

    std::cout << g << std::endl;

    auto [min, tour] = g.tsp_brute_force(0);

    std::cout <<"Min: " << min << std::endl;
    util::print_array(tour);

    return 0;
}