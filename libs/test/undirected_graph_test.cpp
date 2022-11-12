#include "undirected_graph.hpp"
#include "array_list.hpp"

#include <iostream>


int main() {
    ds::array_list<ds::array_list<int>> a = {
                                                {0, 4, 8, 2, 3},
                                                {4, 0, 1, 6, 5},
                                                {8, 1, 0, 2, 1},
                                                {2, 6, 2, 0, 6},
                                                {3, 5, 1, 6, 0} 
                                            };
    ds::undirected_graph g(a);


    if (g.vertices_size() != 5) {
        return 1;
    }

    if (g.edges_size() != 10) {
        return 1;
    }

    if (g.edge_weight({0, 1}) != 4) {
        return 1;
    }

    if (g.adjacent_vertices(0).size() != 4) {
        return 1;
    }

    auto ret = g.mst_prim();
    
    if (ret.total_weight() != 6) {
        return 1;
    }
   
    auto ret1 = g.remove_vertex(0).mst_prim();

    if (ret1.total_weight() != 4) {
        return 1;
    }

    auto ret2 = g.one_tree();

    if (ret2.total_weight() != 9) {
        return 1;
    }

    if (ret2.vertex_degree(0) != 2) {
        return 1;
    }

    if (ret2.largest_degree_vertex() != 2) {
        return 1;
    }

    auto ret3 = g.remove_edge({1,2});

    if (g.total_weight() - ret3.total_weight() != 1) {
        return 1;
    }

    if (ret3.mst_prim().total_weight() != 9) {
        return 1;
    }

    return 0;
}