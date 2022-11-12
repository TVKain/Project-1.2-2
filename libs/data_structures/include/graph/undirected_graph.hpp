#pragma once
#ifndef UNDIRECTED_GRAPH_HPP
#define UNDIRECTED_GRAPH_HPP

#include "array_list.hpp"
#include "priority_queue.hpp"

#include <utility>
#include <ostream>
#include <iostream>
#include <unordered_map>
#include <limits>
#include <algorithm>

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

        /* definition of edge_type */
        struct edge_type {
            vertex_type from;
            vertex_type to;
        };

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

        /***************************************************************
         * @brief: Get the vertex with the largest degree
         * @return:
         *        size_type - denotes the vertex with the largest degree
         ***************************************************************/
        vertex_type largest_degree_vertex() {
            vertex_type largest = 0;

            for (vertex_type i = 1; i < vertices_size(); ++i) {
                if (vertex_degree(i) > vertex_degree(largest)) {
                    largest = i;
                }
            }
            
            return largest;
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
            return cost_matrix[e.from][e.to];
        }


        /**********************************************************
         * @brief: Get number of vertices
         * @return:
         *      size-type - denotes number of vertices in the graph
         **********************************************************/
        size_type vertices_size() const {
            return cost_matrix.size();
        }
        

        /******************************************************
         * @brief: Get total weight of the graph
         * @return:
         *      weight-type - denotes total weight of the graph
         ******************************************************/
        weight_type total_weight() {
            weight_type total = 0;
            for (int i = 0; i < vertices_size(); ++i) {
                for (int j = i + 1; j < vertices_size(); ++j) {
                    total += edge_weight({i, j});
                }
            }
            return total;
        }

        /*******************************************
         * @brief: Overload << operator for printing
         *******************************************/
        friend std::ostream& operator<<(std::ostream &os, const undirected_graph &ug) {
            auto size = ug.vertices_size();
            auto matrix = ug.cost_matrix;
            
            for (int i = 0; i < size; ++i) {
                for (int j = 0; j < size; ++j) {
                    os << matrix[i][j] << " ";
                }
                os << std::endl;
            }
            return os;
        }

        /************************************************************
         * @brief: Return a one tree of the graph 
         * @params: 
         *      vertex_type: the vertex to be removed (default = 0)
         * @return:
         *      undirected_graph: a new graph represents the one tree
         ************************************************************/
        undirected_graph one_tree(const vertex_type &);

        /*******************************************************
         * @brief: Return a minimum spanning tree of the graph
         * @return:
         *      undirected_graph: a new graph represents the mst
         *******************************************************/
        undirected_graph mst_prim();

        /**********************************************************************
         * @brief: Return a subgraph of the current graph with a vertex removed
         * @params: 
         *      vertex_type: vertex to be removed
         * @return: 
         *      undirected_graph: the subgraph with the vertex removed
         **********************************************************************/
        undirected_graph remove_vertex(const vertex_type &);

        undirected_graph remove_vertices(const ds::array_list<vertex_type> &);
        
        /********************************************************************
        * @brief: Return a subgraph of the current graph with an edge removed
        * @params: 
        *      edge_type: edge to be removed
        * @return: 
        *      undirected_graph: the subgraph with the input edge removed
        *********************************************************************/
        undirected_graph remove_edge(const edge_type &);

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


        weight_type tsp_bnb_lower_bound_v1(const ds::array_list<vertex_type> &);
        tsp_return_type tsp_bnb_v1(const vertex_type &);

    private:
        /*************************************************************************
         * @brief: helper for tsp, get all visitable vertices from current vertex
         * @params: 
         *      ds::array_list<vertex_type> - denotes the current visited vertices
         * @return:
         *      dsLLarray_list<vertex_type> - denotes visitable vertices
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
        
        /* list of vertces */
        ds::array_list<vertex_type> vertices;
        
        /* Underlying cost matrix (adjacency matrix) */
        matrix cost_matrix;

        /* Define unreachable value for edge(a, b) = null */
        const int UNREACHABLE_VALUE = 0;
    
    };

    

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

    /*
     * subgraph g' = g\{visited vertices}
     * LB = current path cost + g'.V * g'.min_edge
     */

     /*
     undirected_graph::weight_type tsp_bnb_lower_bound_v1(const ds::array_list<undirected_graph::vertex_type> &current_vertices) {
        ds::array_list<vertex_type> cp(current_vertices);
        cp.pop_back();

        weight_type lower_bound;


        return lower_bound;
    }
     */
    
    /*
    undirected_graph::tsp_return_type undirected_graph::tsp_bnb_v1(const undirected_graph::vertex_type &init_vertex) {
        weight_type min_cost = std::numeric_limits<weight_type>::max();
        ds::array_list<vertex_type> min_tour;

        // Stack store the current lower bound and an array of vertices that was explored in order 
        ds::array_list<weight_type, ds::array_list<vertex_type>> stack;
        
        weight_type current_lower_bound;

        //stack.push_back(ds::array_list<vertex_type>{init_vertex});

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
    */
    
    undirected_graph undirected_graph::remove_edge(const undirected_graph::edge_type &e) {
        undirected_graph ret(cost_matrix);
        ret.cost_matrix[e.from][e.to] = 0;
        ret.cost_matrix[e.to][e.from] = 0;
        return ret;
    }

    undirected_graph undirected_graph::one_tree(const undirected_graph::vertex_type &to_remove = 0) {
        undirected_graph removed = remove_vertex(to_remove);
        undirected_graph mst = removed.mst_prim();

        matrix ret = mst.cost_matrix;

        ds::array_list<int> row = cost_matrix[to_remove];

        std::replace(row.begin(), row.end(), 0, std::numeric_limits<int>::max());

        int min = 0;
        int second_min = 1;
        if (row[second_min] < row[min]) {
            std::swap(min, second_min);
        }

        for (int i = 0; i < row.size(); ++i) {
            if (row[i] < row[min]) {
                second_min = min;
                min = i;
            } else {
                if (row[i] < row[second_min]) {
                    second_min = i;
                }
            }
        }
        
        ds::array_list<int> row_to_add(row.size(), 0);
        row_to_add[min] = row[min];
        row_to_add[second_min] = row[second_min];

        for (int i = 0; i < ret.size(); ++i) {
            ret[i].insert(ret[i].begin() + to_remove, row_to_add[i + 1]);
        }
        ret.insert(ret.begin(), row_to_add);

        return ret;
    }

    undirected_graph undirected_graph::remove_vertex(const undirected_graph::vertex_type &v) {
        return remove_vertices({v});
    }

    undirected_graph undirected_graph::remove_vertices(const ds::array_list<undirected_graph::vertex_type> &vs) {
        auto copy_matrix = cost_matrix;
        auto copy_vs(vs);
        const int REMOVED = -1;

        matrix ret;

        for (int i = 0; i < copy_matrix.size(); ++i) {
            ds::array_list<int> row;
            for (int j = 0; j < copy_matrix.size(); ++j) {
                bool pred = std::find(copy_vs.begin(), copy_vs.end(), i) != copy_vs.end();
                bool s_pred = std::find(copy_vs.begin(), copy_vs.end(), j) != copy_vs.end();

                if (!pred && !s_pred) {
                    row.push_back(copy_matrix[i][j]);
                }
            }
            if (!row.empty()) {
                ret.push_back(row);
            }
            row.clear();
        }

        return undirected_graph(ret);
    }   

    undirected_graph undirected_graph::mst_prim() {
        struct prim_vertex_type {
            vertex_type parent;
            vertex_type self;
            weight_type min_weight;

            prim_vertex_type(vertex_type p, vertex_type s, weight_type m) : parent(p), self(s), min_weight(m) {} 
            prim_vertex_type(const prim_vertex_type &other) : parent(other.parent), self(other.self), min_weight(other.min_weight) {}
        };

        const vertex_type NULL_PARENT = -1;
        const weight_type MAX_WEIGHT = std::numeric_limits<int>::max();

        auto prim_vertex_cmp = [](const prim_vertex_type &a, const prim_vertex_type &b) {
            return a.min_weight > b.min_weight;
        };

        typedef ds::priority_queue<prim_vertex_type, ds::array_list<prim_vertex_type>, decltype(prim_vertex_cmp)> prim_min_pq_type;

        matrix ret(vertices_size(), ds::array_list<int>(vertices_size(), 0));

        ds::array_list<prim_vertex_type> init_min_pq;

        std::unordered_map<vertex_type, bool> visited;

        /* Initialize the min heap */
        for (vertex_type v : vertices) {
            prim_vertex_type pv(NULL_PARENT, v, MAX_WEIGHT);
            init_min_pq.push_back(pv);
            visited[v] = false;
        }

        init_min_pq.front().min_weight = 0;

        ds::array_list<prim_vertex_type> result;
        
        prim_min_pq_type min_pq(prim_vertex_cmp, init_min_pq);

        while (!min_pq.empty()) {
            prim_vertex_type min_vertex = min_pq.top();
            min_pq.pop();   
            
            if (visited[min_vertex.self]) {
                continue;
            } 

            visited[min_vertex.self] = true;

            result.push_back(min_vertex);

            auto adj_vertices = adjacent_vertices(min_vertex.self);

            for (const vertex_type &v : adj_vertices) {
                if (!visited[v]) {
                    min_pq.push(prim_vertex_type(min_vertex.self, v, edge_weight({min_vertex.self, v})));
                }
            }
        }

        for (int i = 1; i < result.size(); ++i) {
            auto from = result[i].parent;
            auto to = result[i].self;
            auto weight = result[i].min_weight;
            ret[from][to] = weight;
            ret[to][from] = weight;
        }

        return undirected_graph(ret);
    }

}



#endif