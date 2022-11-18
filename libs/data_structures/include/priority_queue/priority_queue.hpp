#pragma once 
#ifndef PRIORITY_QUEUE_HPP
#define PRIORITY_QUEUE_HPP

#include "heap.hpp"
#include "array_list.hpp"

#include <functional>
#include <initializer_list> 

namespace ds {
    template <typename T, class Container = ds::array_list<T>, class Compare = std::less<T>>
    class priority_queue {  
    public:
        typedef T value_type;
        typedef Container container_type;
        typedef typename container_type::reference reference;
        typedef typename container_type::size_type size_type;
        typedef Compare value_compare;

        /* Default constructor */
        priority_queue() : comp_(Compare()), c_(Container()) {}

        /* Initialize comp_ with compare c_ is default initialized */
        priority_queue(const Compare &compare) : comp_(compare), c_(Container()) {}

        /* Initialize comp_ with compare, c_ with cont, 
           then calls make_heap(c_.begin(), c_.end(), comp_) to make it a max heap */
        priority_queue(const Compare &compare, const Container &cont) : comp_(compare), c_(cont) {
            algo::heap::make_heap(c_.begin(), c_.end(), comp_);
        }

        /* Initialize comp_ with default, 
           c_ with init_list, then calls make_heap */
        priority_queue(std::initializer_list<value_type> init_list) : comp_(Compare()), c_(init_list) {
            algo::heap::make_heap(c_.begin(), c_.end(), comp_);
        }
    
        /* Initialize comp_ with compare, c_ with first and last, 
           then calls make_heap(c_.begin(), c_.end(), comp_) to make it a max heap */
        template <class InputIt>      
        priority_queue(InputIt first, InputIt last, const Compare &compare) : comp_(compare), c_(first, last) {
            algo::heap::make_heap(c_.begin(), c_.end(), comp_);
        }

        /* Copy constructor */
        priority_queue(const priority_queue& other) : comp_(other.comp_), c_(other.c_) {}


        /*
        // Overload equals operator to be copy 
        priority_queue& operator=(const priority_queue& other) {
            comp_ = other.comp_;
            c_ = other.c_;
            return *this;
        }
        */
        

        /* Return reference to the first element (the largest - default) of the priority queue */
        reference top() {
            return c_.front();
        }

        /* Check if priority queue is empty */
        bool empty() {
            return c_.empty();
        }

        /* Return the size of the priority queue */
        size_type size() {
            return c_.size();
        }

        /* Add an element to the priority queue */
        void push(const value_type& value) {
            c_.push_back(value);
            algo::heap::push_heap(c_.begin(), c_.end(), comp_);
        }

        /* Pop the first element out of the priority queue */
        void pop() {
            algo::heap::pop_heap(c_.begin(), c_.end(), comp_);
            c_.pop_back();
        }

        /* Return the underlying container */
        container_type get_container() {
            return c_;
        }

    private:
        container_type c_;
        value_compare comp_;
    };

}







#endif