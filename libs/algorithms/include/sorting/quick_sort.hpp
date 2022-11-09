#pragma once
#ifndef QUICK_SORT_HPP
#define QUICK_SORT_HPP

#include <utility> /* std::swap std::pair */
#include "array_list.hpp" /* ds::array_list */

namespace algo {
    namespace sort {
        namespace {
            /* Partition subroutine for quick sort */
            template <typename T, typename Compare>
            T* quick_sort_partition(T *first, T *last, Compare compare) {
                auto pivot = *(last - 1);

                auto index = first - 1;

                for (auto it = first; it != last - 1; ++it) {
                    if (compare(*it, pivot)) {
                        index++;
                        std::swap(*it, *index);
                    }
                }

                std::swap(*(index + 1), *(last - 1));

                return index + 1;
            }
        }
        

        template <typename T>
        void quick_sort_recursive(T *first, T *last) {
            if (first + 1 >= last) {
                return;
            }

            auto pivot = quick_sort_partition(first, last, [](const T &a, const T &b) {
                return a < b;
            });
            quick_sort_recursive(first, pivot);
            quick_sort_recursive(pivot + 1, last);
        }

        template <typename T>
        void quick_sort_iterative(T *first, T *last) {
            ds::array_list<std::pair<T*, T*>> stack = {{first, last}};

            while (!stack.empty()) {
                auto start = stack.back().first;
                auto end = stack.back().second; 
                stack.pop_back();

                auto pivot = quick_sort_partition(start, end, [](const T &a, const T &b) {
                    return a < b;
                });

                if (pivot - 1 > start) {
                    stack.push_back(std::make_pair(start, pivot));
                }

                if (pivot + 1 < end - 1) {
                    stack.push_back(std::make_pair(pivot + 1, end));
                }

            }
            
        }

        template <typename T, typename Compare>
        void quick_sort_recursive(T *first, T *last, Compare compare) {
            if (first + 1 >= last) {
                return;
            }

            auto pivot = quick_sort_partition(first, last, compare);
            quick_sort_recursive(first, pivot, compare);
            quick_sort_recursive(pivot + 1, last, compare);
        }

        template <typename T, typename Compare>
        void quick_sort_iterative(T *first, T *last, Compare compare) {
            ds::array_list<std::pair<T*, T*>> stack = {{first, last}};

            while (!stack.empty()) {
                auto start = stack.back().first;
                auto end = stack.back().second; 
                stack.pop_back();

                auto pivot = quick_sort_partition(start, end, compare);

                if (pivot - 1 > start) {
                    stack.push_back(std::make_pair(start, pivot));
                }

                if (pivot + 1 < end - 1) {
                    stack.push_back(std::make_pair(pivot + 1, end));
                }

            }
            
        }
    }
}





#endif