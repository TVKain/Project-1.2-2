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
        typedef std::size_t size_type;
        typedef int weight_type;
        typedef ds::array_list<ds::array_list<weight_type>> matrix;
        typedef int label_type;
        typedef int vertex_type;

        struct edge_type {
            vertex_type from;
            vertex_type to;
        };

        undirected_graph(matrix &cm) : cost_matrix(cm) {
            for (int i = 0; i < cm.size(); ++i) {
                vertices.push_back(i);
            }
        }
        undirected_graph(const undirected_graph &other) : cost_matrix(other.cost_matrix), vertices(other.vertices) {}

        undirected_graph& operator=(const undirected_graph &other) {
            cost_matrix = other.cost_matrix;
            return *this;
        }

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

        vertex_type largest_degree_vertex() {
            vertex_type largest = 0;

            for (vertex_type i = 1; i < vertices_size(); ++i) {
                if (vertex_degree(i) > vertex_degree(largest)) {
                    largest = i;
                }
            }
            
            return largest;
        }

        size_type vertex_degree(const vertex_type &v) {
            size_type count = 0;
            for (const auto &c : cost_matrix[v]) {
                if (c != 0) {
                    count++;
                }
            }
            return count;
        }

        ds::array_list<vertex_type> adjacent_vertices(const vertex_type &v) {
            ds::array_list<vertex_type> ret;
            
            for (int i = 0; i < vertices_size(); ++i) {
                if (cost_matrix[v][i] != UNREACHABLE_VALUE) {
                    ret.push_back(i);
                }
            }

            return ret;
        }

        weight_type edge_weight(edge_type e) {
            return cost_matrix[e.from][e.to];
        }

        size_type vertices_size() const {
            return cost_matrix.size();
        }
        
        weight_type total_weight() {
            weight_type total = 0;
            for (int i = 0; i < vertices_size(); ++i) {
                for (int j = i + 1; j < vertices_size(); ++j) {
                    total += edge_weight({i, j});
                }
            }
            return total;
        }

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

        undirected_graph one_tree(const vertex_type &);
        undirected_graph mst_prim();
        undirected_graph remove_vertex(const vertex_type &);
        undirected_graph remove_edge(const edge_type &);

        

        private:
            ds::array_list<vertex_type> vertices;
            matrix cost_matrix;
            const int UNREACHABLE_VALUE = 0;
    
    };

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
        auto copy_matrix = cost_matrix;

        copy_matrix.erase(copy_matrix.begin() + v);
        
        for (auto &row : copy_matrix) {
            row.erase(row.begin() + v);
        }

        return undirected_graph(copy_matrix);
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