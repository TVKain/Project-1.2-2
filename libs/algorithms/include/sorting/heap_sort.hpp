#pragma once
#ifndef HEAP_SORT_HPP
#define HEAP_SORT_HPP

#include "heap.hpp" /* heap::make_heap heap::heapify*/
#include <utility> /* std::swap */
#include <functional> /* std::less */

namespace algo {
    namespace sort {
        template <typename T, typename Compare = std::less<T>>
        void heap_sort(T *first, T *last, Compare compare = Compare()) {
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