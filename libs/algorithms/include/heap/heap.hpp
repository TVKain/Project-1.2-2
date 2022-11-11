#pragma once
#ifndef HEAP_HPP
#define HEAP_HPP

#include <iostream>
#include <cstddef>
#include <functional>
#include <algorithm>

namespace algo {
    namespace heap {

        namespace {
            constexpr std::size_t left(std::size_t i) {
                return (i << 1) + 1;
            }

            constexpr std::size_t right(std::size_t i) {
                return (i << 1) + 2;
            }

            constexpr std::size_t parent(std::size_t i) {
                return (i - 1) >> 1;
            }
        }

        template <typename T, typename Compare>
        void heapify(T *first, T *last, std::size_t index, Compare compare) {
            decltype(index) elem;
            auto size = last - first;

            while (true) {
                auto l = left(index);
                auto r = right(index);

                if (l < size && compare(*(first + index), *(first + l))) {
                    elem = l;
                } else {
                    elem = index;
                }

                if (r < size && compare(*(first + elem), *(first + r))) {
                    elem = r;
                }

                if (elem != index) {
                    std::swap(*(first + elem), *(first + index));
                    index = elem;
                } else {
                    break;
                }
            }
            
        }

        template <typename T, typename Compare = std::less<T>>
        void make_heap(T *first, T *last, Compare compare = Compare()) {
            auto size = last - first;

            for (auto i = size / 2; i >= 0; --i) {
                heapify(first, last, i, compare);
            }
        }

        template <typename T, typename Compare = std::less<T>>
        void push_heap(T *first, T *last, Compare compare = Compare()) {
            auto current = last - first - 1;
            auto parent_index = parent(current);

            /* While the parent[i] < i  */
            while (compare(*(first + parent_index), *(first + current))) {
                std::swap(*(first + parent_index), *(first + current));
                current = parent_index;
                parent_index = parent(current);

                if (current == 0) {
                    break;
                }
            }
         }

        template <typename T, typename Compare = std::less<T>> 
        void pop_heap(T *first, T *last, Compare compare = Compare()) {
            std::swap(*first, *(last - 1));
            heapify(first, last - 2, 0, compare);
        }

    }
}


#endif