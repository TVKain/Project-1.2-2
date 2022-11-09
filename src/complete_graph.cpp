#include "complete_graph.hpp"
#include "array_list.hpp"

#include <utility>
#include <limits>
#include <algorithm>
#include <iostream>

std::pair<int, ds::array_list<int>> complete_graph::tsp_brute_force(int init_node) {
    int min_cost = std::numeric_limits<int>::max();
    ds::array_list<int> min_path;

    /* Stack store the array of nodes that was taken in order */
    ds::array_list<ds::array_list<int>> stack;
    stack.push_back(ds::array_list<int>{init_node});

    while (!stack.empty()) {
        auto current_nodes = stack.back();

        stack.pop_back();

        auto reachable_nodes = calculate_reachable_nodes(current_nodes);
    
        if (reachable_nodes.size() != 0) {
            for (const auto &reachable_node : reachable_nodes) {
                auto next_current_nodes = current_nodes;
                next_current_nodes.push_back(reachable_node);
                stack.push_back(next_current_nodes);
            }
        } else if (reachable_nodes.size() == 0) {
            ds::array_list<int> current_path(current_nodes);
            current_path.push_back(init_node);

            int total_cost = calculate_path_cost(current_path);

            if (total_cost < min_cost) {
                min_cost = total_cost;
                min_path = current_path;
            }
        }
        
    }
    return std::make_pair(min_cost, min_path);
}

int complete_graph::calculate_path_cost(ds::array_list<int> path) {
    int total_cost = 0; 
    for (int i = 0, j = 1; j < path.size(); ++i, ++j) {
        int from = path[i];
        int to = path[j];
        total_cost += cost_matrix[from][to];
    }
    return total_cost;
}

ds::array_list<int> complete_graph::calculate_reachable_nodes(ds::array_list<int> current_nodes) {
    ds::array_list<int> reachable_nodes;

    for (int i = 0; i < node_count; ++i) {
        if (std::find(current_nodes.begin(), current_nodes.end(), i) == current_nodes.end()) {
            reachable_nodes.push_back(i);
        }
    }

    return reachable_nodes;
}

