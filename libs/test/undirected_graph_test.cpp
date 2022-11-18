#include "undirected_graph.hpp"
#include "array_list.hpp"

#include <iostream>


int main() {
    ds::array_list<ds::array_list<int>> b = {
        {0, 4, 8, 2, 3},
        {4, 0, 1, 6, 5},
        {8, 1, 0, 2, 1},
        {2, 6, 2, 0, 6},
        {3, 5, 1, 6, 0}
    };

    ds::undirected_graph g(b);

    auto mins = g.two_min_edge_weight(0);

    if (mins.first != 2 || mins.second != 3) {
        return 1;
    }

    auto mins1 = g.two_min_edge_weight(1);

    if (mins1.first != 1 || mins1.second != 4) {
        return 1;
    }

    auto mins2 = g.two_min_edge_weight(2);

    if (mins2.first != 1 || mins2.second != 1) {
        return 1;
    }

    mins = g.two_min_edge_weight(3);

    if (mins.first != 2 || mins.second != 2) {
        return 1;
    }    

    mins = g.two_min_edge_weight(4);

    if (mins.first != 1 || mins.second != 3) {
        return 1;
    }

    ds::array_list<int> a = {0, 1};

    std::cout << "First: " << g.tsp_bnb_lower_bound_v1(a) << std::endl;
    std::cout << "Second: " << g.tsp_bnb_lower_bound_v2(a) << std::endl;

    auto c = a;
    c.push_back(3);

    std::cout << "First: " << g.tsp_bnb_lower_bound_v1(c) << std::endl; 
    std::cout << "Second: " << g.tsp_bnb_lower_bound_v2(c)<< std::endl;
    
    return 0;
}