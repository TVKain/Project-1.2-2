#pragma once
#ifndef INSERTION_SORT_HPP
#define INSERTION_SORT_HPP

#include <utility> /* std::swap */
#include <functional>

namespace algo {
    namespace sort {
        /* Insertion sort implentation
         * Sorts based on the compare function
         * The default compare function uses the < operator
         */
        template <typename T, typename Compare = std::less<T>>
        void insertion_sort(T *first, T *last, Compare compare = Compare()) {
            for (auto i = first + 1; i < last; ++i) {
                T key = *i;
                auto j = i - 1;
                while (j >= first && compare(key, *j))
                {
                    *(j + 1) = *j;
                    --j;
                }
                *(j + 1) = key;
            }
        }
    }
}

#endif