#pragma once
#ifndef COMPLETE_GRAPH_HPP
#define COMPLETE_GRAPH_HPP

#include "array_list.hpp"

#include <utility>

class complete_graph {
private:
    typedef ds::array_list<ds::array_list<int>> matrix;
    matrix cost_matrix;
    int node_count;
public:
    complete_graph(matrix cm) : cost_matrix(cm), node_count(cost_matrix.size()) {};
 
    std::pair<int, ds::array_list<int>> tsp_brute_force(int);
    int calculate_path_cost(ds::array_list<int>);
    ds::array_list<int> tsp_branch_and_bound();
    ds::array_list<int> calculate_reachable_nodes(ds::array_list<int>);

    void print_tsp_solution();
};




#endif