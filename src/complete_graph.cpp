#include "complete_graph.hpp"
#include "array_list.hpp"
#include "sort.hpp"

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
        } else if (reachable_nodes.empty()) {
            ds::array_list<int> current_path = current_nodes;
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

std::pair<int, ds::array_list<int>> complete_graph::tsp_branch_and_bound_v1(int init_node) {
    auto cost_matrix_copy = cost_matrix;

    int min_cost = std::numeric_limits<int>::max();
    ds::array_list<int> min_path;

    ds::array_list<int> current_nodes{init_node};
    int current_low_bound = node_count * get_current_smallest_edge(current_nodes);

    /* Stack store the current lower bound and a list of nodes that was taken in order */
    ds::array_list<std::pair<int, ds::array_list<int>>> stack;
    stack.push_back(std::make_pair(current_low_bound, current_nodes));

    while (!stack.empty()) {
        current_low_bound = stack.back().first; 
        current_nodes = stack.back().second;

        stack.pop_back();

        if (min_cost < current_low_bound) {
            continue;
        }

        auto reachable_nodes = calculate_reachable_nodes(current_nodes);

        if (!reachable_nodes.empty()) {
            ds::array_list<std::pair<int, ds::array_list<int>>> tmp;
            for (const auto &reachable_node : reachable_nodes) {
                auto next_current_nodes = current_nodes;
                next_current_nodes.push_back(reachable_node);
                auto next_lower_bound = calculate_current_low_bound(next_current_nodes);

                tmp.push_back(std::make_pair(next_lower_bound, next_current_nodes));
            }
            algo::sort::insertion_sort(tmp.begin(), tmp.end(), [](const auto &a, const auto &b) {
                return a.first > b.first;
            });
            for (const auto &i : tmp) {
                stack.push_back(i);
            }
            tmp.clear();
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

int complete_graph::calculate_current_low_bound(ds::array_list<int> &current_nodes) {
    return calculate_path_cost(current_nodes) + (node_count - current_nodes.size() + 1) * get_current_smallest_edge(current_nodes);
}

int complete_graph::get_current_smallest_edge(ds::array_list<int> &current_nodes) {
    int min_edge = std::numeric_limits<int>::max();

    ds::array_list<std::pair<int, int>> removed_edges;

    for (int i = 0, j = 1; j < current_nodes.size(); ++i, ++j) {
        removed_edges.push_back(std::make_pair(current_nodes[i], current_nodes[j]));
        removed_edges.push_back(std::make_pair(current_nodes[j], current_nodes[i]));
    }

    for (int i = 0; i < cost_matrix.size(); ++i) {
        for (int j = 0; j < cost_matrix.size(); ++j) {
            if (i == j) {
                continue;
            }
            bool first_pred = std::find(removed_edges.begin(), removed_edges.end(), std::make_pair(i, j)) == removed_edges.end();
            bool second_pred = cost_matrix[i][j] < min_edge;

            if (first_pred && second_pred) {
                min_edge = cost_matrix[i][j];
            }
        }
    }

    return min_edge;
}
