#pragma once
#ifndef HEAP_HPP
#define HEAP_HPP

#include <iostream>
#include <cstddef>

namespace algo {
    namespace heap {

        namespace {
            constexpr std::size_t left(std::size_t i) {
                return (i << 1) + 1;
            }

            constexpr std::size_t right(std::size_t i) {
                return (i << 1) + 2;
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

        template <typename T>
        void make_heap(T *first, T *last) {
            auto size = last - first;

            for (auto i = size / 2; i >= 0; --i) {
                heapify(first, last, i, [](const T &a, const T &b) {
                    return a < b;
                });
            }
        }

        template <typename T, typename Compare>
        void make_heap(T *first, T *last, Compare compare) {
            auto size = last - first;
            for (auto i = size / 2; i >= 0; --i) {
                heapify(first, last, i, compare);
            }
        }

    }
}


#endif