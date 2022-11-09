#pragma once
#ifndef HEAP_SORT_HPP
#define HEAP_SORT_HPP

#include "heap.hpp" /* heap::make_heap heap::heapify*/
#include <utility> /* std::swap */

namespace algo {
    namespace sort {
        template <typename T>
        void heap_sort(T *first, T *last) {
            auto end = last;

            auto compare = [](const T &a, const T &b) {
                return a < b;
            };

            heap::make_heap(first, last, compare);
            for (auto it = last - 1; it > first; --it) {
                std::swap(*first, *it);
                --end;
                heap::heapify(first, end, 0, compare);
            }
        }

        template <typename T, typename Compare>
        void heap_sort(T *first, T *last, Compare compare) {
            auto end = last;

            heap::make_heap(first, last, compare);
            for (auto it = last - 1; it > first; --it) {
                std::swap(*first, *it);
                --end;
                heap::heapify(first, end, 0, compare);
            }
        }
    }
}



#endif