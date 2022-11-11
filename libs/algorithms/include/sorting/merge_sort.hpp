#pragma once
#ifndef MERGE_SORT_HPP
#define MERGE_SORT_HPP

#include "array_list.hpp" /* array_list */
#include <algorithm>
#include <functional>

namespace algo {
    namespace sort {
        namespace {
            template <typename T, typename Compare>
            void merge(T *start, T *mid, T *end, Compare compare) {
                ds::array_list<T> left(start, mid);
                ds::array_list<T> right(mid, end);

                auto i = left.begin();
                auto j = right.begin();
                auto k = start;

                while (i != left.end() && j != right.end()) {
                    if (compare(*i, *j)) {
                        *k = *i;
                        ++i;
                    } else {
                        *k = *j;
                        ++j;
                    }
                    ++k;
                }

                while (i != left.end()) {
                    *k = *i;
                    ++i;
                    ++k;
                }

                while (j != right.end()) {
                    *k = *j;
                    ++j;
                    ++k;
                }
            }
        }

        template<typename T, typename Compare = std::less<T>> 
        void merge_sort_recursive(T *first, T *last, Compare compare = Compare()) {
            if (first >= last - 1) {
                return;
            }

            auto mid = first + (last - first) / 2;

            merge_sort_recursive(first, mid, compare);
            merge_sort_recursive(mid, last, compare);
            merge(first, mid, last, compare);
        }

        template<typename T, typename Compare = std::less<T>>
        void merge_sort_iterative(T *first, T *last, Compare compare = Compare()) {
            auto size = last - first;
            decltype(size) group_size = 1;

            for (; group_size < size; group_size *= 2) {
                
                for (decltype(size) group_size = 1; group_size < size; group_size *= 2) {
                
                    for (auto start = first; start < last; start += 2 * group_size) {
                        auto mid = std::min(last, start + group_size);
                        auto end = std::min(last, start + 2 * group_size);

                        merge(start, mid, end, compare);
                    }
                }
            }   
        }  

    }

}

#endif