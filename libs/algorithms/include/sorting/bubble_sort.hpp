#pragma once
#ifndef BUBBLE_SORT_HPP
#define BUBBLE_SORT_HPP

#include <utility> /* std::swap */
#include <functional> /* std::less */

namespace algo {
    namespace sort {
        /* Bubble sort implementation
         * Sorts based on the compare function
         */
        template <typename T, typename Compare = std::less<T>>
        void bubble_sort(T *first, T *last, Compare compare = Compare()) {
            for (auto i = first; i < last - 1; ++i) {
                for (auto j = last - 1; j >= i + 1; --j) {
                    if (compare(*j, *(j - 1))) {
                        std::swap(*j, *(j - 1));
                    }
                }
            }
        }
    }
}
#endif