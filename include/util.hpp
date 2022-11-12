#pragma once
#ifndef UTIL_HPP
#define UTIL_HPP

#include <string>
#include <chrono>
#include <iostream>

#include "array_list.hpp"

namespace util {
    void read_matrix_from_file(std::string, ds::array_list<ds::array_list<int>> &);
    void print_matrix(ds::array_list<ds::array_list<int>> &);
    void print_array(ds::array_list<int> &);

    ds::array_list<ds::array_list<int>> generate_cost_matrix(int, int, int);
    int generate_random_num(const int &, const int &);

    template<typename Duration = std::chrono::nanoseconds, typename F, typename ... Args>
    Duration bench_time(F&& fun,  Args&&... args) {
        const auto beg = std::chrono::high_resolution_clock::now();
        std::forward<F>(fun)(std::forward<Args>(args)...);
        const auto end = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<Duration>(end - beg);
    }
}




#endif