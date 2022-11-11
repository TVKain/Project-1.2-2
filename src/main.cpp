#include <iostream>
#include <chrono>
#include <functional>

#include "array_list.hpp"
#include "complete_graph.hpp"
#include "util.hpp"

int main() {
    ds::array_list<ds::array_list<int>> cost_matrix;

    util::read_matrix_from_file("graph5.txt", cost_matrix);

    util::print_matrix(cost_matrix);
    std::cout << std::endl;
    
    complete_graph g(cost_matrix);

    /*
    auto bf = util::bench_time<std::chrono::seconds>([&g]() -> void {
        auto [min, path] = g.tsp_brute_force(0);
        std::cout << "BF: " << min << std::endl;
    });
    std::cout << "Time: " << bf.count() << std::endl;
    */
    

    auto bnb = util::bench_time<std::chrono::milliseconds>([&g]() -> void {
        auto [min, path] = g.tsp_branch_and_bound_v1(0);
        std::cout << "BNB: " << min << std::endl;
        for (int i = 0; i < path.size(); ++i) {
            std::cout << path[i] + 1 << "->";
        }
        std::cout << std::endl;
    });
    std::cout << "Time: " << bnb.count() << std::endl;



    return 0;
}