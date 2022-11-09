#pragma once
#ifndef INSERTION_SORT_HPP
#define INSERTION_SORT_HPP

#include <utility> /* std::swap */

namespace algo {
    namespace sort {
        /* Insertion sort implentation
         * Default sorting from min to max
         * Uses the < operator
         */
        template <typename T>
        void insertion_sort(T *first, T *last) {
            for (auto i = first + 1; i < last; ++i) {
                T key = *i;
                auto j = i - 1;
                while (j >= first && key < *j) {
                    *(j + 1) = *j;
                    --j;
                }
                *(j + 1) = key;
            }
        }

        /* Insertion sort implentation
         * Sorts based on the compare function
         */
        template <typename T, typename Compare>
        void insertion_sort(T *first, T *last, Compare compare) {
            for (auto i = first + 1; i < last; ++i) {
                T key = *i;
                auto j = i - 1;
                while (j >= first && compare(key, j))
                {
                    *(j + 1) = *j;
                    --j;
                }
                *(j + 1) = key;
            }
        };

    }
}

#endif