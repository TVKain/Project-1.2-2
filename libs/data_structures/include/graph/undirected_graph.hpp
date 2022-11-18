#pragma once
#ifndef UNDIRECTED_GRAPH_HPP
#define UNDIRECTED_GRAPH_HPP

#include "array_list.hpp"
#include "sort.hpp"

#include <cmath>
#include <utility>
#include <ostream>
#include <iostream>
#include <unordered_map>
#include <limits>
#include <algorithm>
#include <iomanip>

/* Implementation of graph using adjacency matrix */

namespace ds {
    class undirected_graph {
    public:
        /* typedef for size type*/
        typedef std::size_t size_type;

        /* typedef for weight type of edges */
        typedef int weight_type;

        /* typedef for matrix type */
        typedef ds::array_list<ds::array_list<weight_type>> matrix;
        
        /* typedef for vertex type*/
        typedef int vertex_type;

        /* typedef for the return type of tsp procedure */
        typedef std::pair<weight_type, ds::array_list<vertex_type>> tsp_return_type;

        /* typedef for the return type of mst procedure*/
        typedef std::pair<bool, undirected_graph> mst_return_type;

        /* typedef for the return type of one tree procedure */
        typedef std::pair<bool, undirected_graph> one_tree_return_type;

        /* definition of edge_type */
        typedef std::pair<vertex_type, vertex_type> edge_type;
        

        /***************************************
         * @brief:
         *          construct an empty graph
         *          can't do much with it really
         ***************************************/
         undirected_graph() : cost_matrix(matrix()), vertices(ds::array_list<vertex_type>()) {}

        /**********************************************************************
         * @brief: 
         *          construct graph object from a cost matrix (adjacency matrix)
         *          build an array of vertices from cost matrix as well  
         * @param: cm - matrix
         **********************************************************************/
        undirected_graph(matrix &cm) : cost_matrix(cm) {
            for (int i = 0; i < cm.size(); ++i) {
                vertices.push_back(i);
            }
        }

        /**********************************
         * @brief: Copy constructor
         * @param: other - undirected_graph 
         **********************************/
        undirected_graph(const undirected_graph &other) : cost_matrix(other.cost_matrix), vertices(other.vertices) {}

        void set_cost_matrix(matrix new_matrix) {
            cost_matrix = new_matrix;
        }

        /*************************************
         * @brief: Overload = operator to copy
         *************************************/
        undirected_graph& operator=(const undirected_graph &other) {
            cost_matrix = other.cost_matrix;
            return *this;
        }

        /********************************************
         * @brief: Get number of edges in the graph
         * @return: 
         *        size_type - denotes number of edges 
         ********************************************/
        size_type edges_size() const {
            size_type count = 0;
            auto copy = cost_matrix;

            for (int i = 0; i < vertices_size(); ++i) {
                for (int j = i + 1; j < vertices_size(); ++j) {
                    if (copy[i][j] != UNREACHABLE_VALUE) {
                        count++;
                    }
                }
            }
            return count;
        }

        /*********************************************************
         * @brief: Get the weight of the minimum edge in the graph 
         * @return: 
         *      weight_type - the minimum weight
         *********************************************************/
        weight_type min_edge_weight() {
            weight_type min = std::numeric_limits<weight_type>::max();

            for (vertex_type i = 0; i < vertices_size(); ++i) {
                for (vertex_type j = i + 1; j < vertices_size(); ++j) {
                    weight_type curr = edge_weight({i, j});
                    if (curr < min) {
                        min = curr;
                    }
                }
            }

            return min;
        }

        /*************************************************************
         * @brief: Get the degree of a vertex in the graph
         * @param: vertex_type v 
         * @return: size_type - denotes the degree of the input vertex
         *************************************************************/
        size_type vertex_degree(const vertex_type &v) {
            size_type count = 0;
            for (const auto &c : cost_matrix[v]) {
                if (c != 0) {
                    count++;
                }
            }
            return count;
        }

        /****************************************************************************************
         * @brief: Get adjacent vertices from the input vertex
         * @param: vertex_type v
         * @return: 
         *      ds::array_list<vertex_type> - the list of adjacent vertices from the input vertex
         ****************************************************************************************/
        ds::array_list<vertex_type> adjacent_vertices(const vertex_type &v) {
            ds::array_list<vertex_type> ret;
            
            for (int i = 0; i < vertices_size(); ++i) {
                if (cost_matrix[v][i] != UNREACHABLE_VALUE) {
                    ret.push_back(i);
                }
            }

            return ret;
        }

        /*************************************************
         * @brief: Get edge weight of an edge
         * @params: edge_type e 
         * @return:
         *      weight-type - the weight of the input edge
         *************************************************/
        weight_type edge_weight(edge_type e) {
            return cost_matrix[e.first][e.second];
        }


        /**********************************************************
         * @brief: Get number of vertices
         * @return:
         *      size-type - denotes number of vertices in the graph
         **********************************************************/
        size_type vertices_size() const {
            return cost_matrix.size();
        }
        
        /*******************************************
         * @brief: Overload << operator for printing
         *******************************************/
        friend std::ostream& operator<<(std::ostream &os, const undirected_graph &ug) {
            auto size = ug.vertices_size();
            auto matrix = ug.cost_matrix;
            
            for (int i = 0; i < size; ++i) {
                for (int j = 0; j < size; ++j) {
                    os << std::setw(4) << matrix[i][j] << " ";
                }
                os << std::endl;
            }
            return os;
        }

        /*******************************************
         * @brief: Solve tsp problem by brute force
         * @params:
         *      vertex_type: vertex to start at
         * @return:
         *      tsp_return_type:
         *          the min cost of the tour
         *          the tour itself
         ******************************************/
        tsp_return_type tsp_brute_force(const vertex_type &);
        weight_type tsp_bnb_lower_bound_v2(ds::array_list<vertex_type> );
        tsp_return_type tsp_bnb_v2(const vertex_type &);

        /*****************************************************************
         * @brief: Get the weight of the minimum edge adj to v
         * @params: vertex_type v 
         *          the input vertex
         * @return: 
         *          the weight of the minimum edge adj to the input vertex
         *****************************************************************/
        weight_type min_adjacent_edge(const vertex_type &);
    private:
        /*************************************************************************
         * @brief: helper for tsp, get all visitable vertices from current vertex
         * @params: 
         *      ds::array_list<vertex_type> - denotes the current visited vertices
         * @return:
         *      ds::array_list<vertex_type> - denotes visitable vertices
         *************************************************************************/
        ds::array_list<vertex_type> visitable_vertices(ds::array_list<vertex_type> &);

        /*************************************************************
         * @brief: helper for tsp, calculate the current path cost
         * @params:
         *      ds::array_list<vertex_type> - denotes the current path
         * @return:
         *      weight_type - denotes the total cost for the path
         **************************************************************/
        weight_type path_cost(ds::array_list<vertex_type> &); 
        
        /* list of vertices */
        ds::array_list<vertex_type> vertices;
        
        /* Underlying cost matrix (adjacency matrix) */
        matrix cost_matrix;

        /* Define unreachable value for edge(a, b) = null */
        const int UNREACHABLE_VALUE = 0;
    
    };


    undirected_graph::weight_type undirected_graph::min_adjacent_edge(const undirected_graph::vertex_type &v) {
        weight_type min_weight = std::numeric_limits<weight_type>::max();
        for (vertex_type i = 0; i < vertices_size(); ++i) {
            if (cost_matrix[v][i] < min_weight && cost_matrix[v][i] != UNREACHABLE_VALUE) {
                min_weight = cost_matrix[v][i];
            }
        }
        return min_weight;
    }

    undirected_graph::weight_type undirected_graph::path_cost(ds::array_list<undirected_graph::vertex_type> &tour) {
        weight_type total_cost = 0;
        for (int i = 0, j = 1; j < tour.size(); ++i, ++j) {
            vertex_type from = tour[i];
            vertex_type to = tour[j];
            total_cost += edge_weight({from, to});
        }
        return total_cost;
    }

    ds::array_list<undirected_graph::vertex_type> undirected_graph::visitable_vertices(ds::array_list<undirected_graph::vertex_type> &current_vertices) {
        ds::array_list<vertex_type> ret;

        for (vertex_type i = 0; i < vertices_size(); ++i) {
            if (std::find(current_vertices.begin(), current_vertices.end(), i) == current_vertices.end()) {
                ret.push_back(i);
            }
        }

        return ret;
    }

    undirected_graph::tsp_return_type undirected_graph::tsp_brute_force(const undirected_graph::vertex_type &init_vertex) {
        weight_type min_cost = std::numeric_limits<weight_type>::max();
        ds::array_list<vertex_type> min_tour;

        /* Stack store the array of vertices that was explored in order */
        ds::array_list<ds::array_list<vertex_type>> stack;
        stack.push_back(ds::array_list<vertex_type>{init_vertex});

        while (!stack.empty()) {
            auto current_vertices = stack.back();

            stack.pop_back();

            auto vvs = visitable_vertices(current_vertices);

            if (!vvs.empty()) {
                for (const auto &vv : vvs) {
                    auto next_current_vertices = current_vertices;
                    next_current_vertices.push_back(vv);
                    stack.push_back(next_current_vertices);
                }
            } else {
                ds::array_list<vertex_type> current_tour = current_vertices;
                current_tour.push_back(init_vertex);

                weight_type tc = path_cost(current_tour);

                if (tc < min_cost) {
                    min_cost = tc;
                    min_tour = current_tour;
                }

            }

        } 

        return std::make_pair(min_cost, min_tour);
    }

    undirected_graph::weight_type undirected_graph::tsp_bnb_lower_bound_v2(ds::array_list<undirected_graph::vertex_type> current_vertices) {
        weight_type lower_bound = 0;

        for (int i = 0, j = 1; j < current_vertices.size(); ++i, ++j) {
            auto from = current_vertices[i];
            auto to = current_vertices[j];
            lower_bound += edge_weight({from, to});
        }

        ds::array_list<vertex_type> unvisited;
        for (const auto &i : vertices) {
            if (std::find(current_vertices.begin(), current_vertices.end() - 1, i) == current_vertices.end() - 1) {
                unvisited.push_back(i);
            }
        }

        for (const auto &v : unvisited) {
            lower_bound += min_adjacent_edge(v);
        }
    
        return lower_bound;
    }    

    undirected_graph::tsp_return_type undirected_graph::tsp_bnb_v2(const undirected_graph::vertex_type &init_vertex) {
        weight_type min_cost = std::numeric_limits<weight_type>::max();
        ds::array_list<vertex_type> min_tour;
        ds::array_list<vertex_type> current_vertices = {init_vertex};

        weight_type current_lower_bound = tsp_bnb_lower_bound_v2(current_vertices);
        // Stack store the current lower bound and the current path 
        ds::array_list<std::pair<weight_type, ds::array_list<vertex_type>>> stack;

        stack.push_back(std::make_pair(current_lower_bound, current_vertices));

        while (!stack.empty()) {
            current_lower_bound = stack.back().first;
            current_vertices = stack.back().second;

            stack.pop_back();

            if (current_lower_bound >= min_cost) {
                continue;
            }

            auto vvs = visitable_vertices(current_vertices);

            if (!vvs.empty()) {
                ds::array_list<std::pair<weight_type, ds::array_list<vertex_type>>> tmp;
                for (const auto &vv : vvs) {
                    auto next_current_vertices = current_vertices;
                    next_current_vertices.push_back(vv);
                    auto next_lower_bound = tsp_bnb_lower_bound_v2(next_current_vertices);
                    tmp.push_back(std::make_pair(next_lower_bound, next_current_vertices));
                }
                algo::sort::insertion_sort(tmp.begin(), tmp.end(), [](const auto &a, const auto &b) {
                    return a.first > b.first;
                });
                for (const auto &t : tmp) {
                    stack.push_back(t);
                }
            } else {
                ds::array_list<vertex_type> current_tour = current_vertices;
                current_tour.push_back(init_vertex);

                weight_type tc = path_cost(current_tour);

                if (tc < min_cost) {
                    min_cost = tc;
                    min_tour = current_tour;
                }
            }
        }

        return std::make_pair(min_cost, min_tour);
    }

}



#endif