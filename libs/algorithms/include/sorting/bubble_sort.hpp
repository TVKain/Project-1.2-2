#pragma once
#ifndef BUBBLE_SORT_HPP
#define BUBBLE_SORT_HPP

#include <utility> /* std::swap */

namespace algo {
    namespace sort {
        /* Bubble sort implementation
         * Default sorting from min to max
         * Uses the < operator
         */
        template <typename T>
        void bubble_sort(T *first, T *last) {
            for (auto i = first; i < last - 1; ++i) {
                for (auto j = last - 1; j >= i + 1; --j) {
                    if (*(j) < *(j - 1)) {
                        std::swap(*(j), *(j - 1));
                    }
                }
            }
        }

        /* Bubble sort implementation
         * Sorts based on the compare function
         */
        template <typename T, typename Compare>
        void bubble_sort(T *first, T *last, Compare compare) {
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