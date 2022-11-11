#pragma once 
#ifndef PRIORITY_QUEUE_HPP
#define PRIORITY_QUEUE_HPP

#include "heap.hpp"
#include "array_list.hpp"

#include <functional>

namespace ds {
    template <typename T, class Container = ds::array_list<T>, class Compare = std::less<T>>
    class priority_queue {  
    public:
        typedef T value_type;
        typedef Container container_type;
        typedef typename container_type::reference reference;
        
        typedef typename container_type::size_type size_type;
        typedef Compare value_compare;

        priority_queue() : comp_(Compare()), c_(Container()) {}
        priority_queue(const Compare &compare) : comp_(compare), c_(Container()) {}
        priority_queue(const Compare &compare, const Container &cont) : comp_(compare), c_(cont) {}
        
        priority_queue()

        priority_queue(const priority_queue& other) : comp_(other.comp_), c_(other.c_) {}

        priority_queue& operator=(const priority_queue& other) {
            comp_ = other.comp_;
            c_ = other.c_;
            return *this;
        }



        reference top() {
            return c_.front();
        }

        bool empty() {
            return c_.empty();
        }

        size_type size() {
            return c_.size();
        }

        void push(const value_type& value) {
            c_.push_back(value);
            algo::heap::push_heap(c_.begin(), c_.end(), comp);
        }

    private:
        container_type c_;
        value_compare comp_;
    };

}







#endif