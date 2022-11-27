/*********************************************************
 * Doubly-linked list data structure implementation in C++ 
 *********************************************************/
#pragma once
#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <memory>
#include <initializer_list>
#include <iostream>

namespace ds {
    
    template <typename T>
    class linked_list_node {
    public:
        typedef T value_type;
        typedef value_type& reference;
        typedef const value_type& const_reference; 

        typedef linked_list_node* self_pointer;
        
        linked_list_node(const_reference t_value) : m_value(t_value), m_next(nullptr), m_prev(nullptr) {}
        linked_list_node(const_reference t_value, const self_pointer &t_next, const self_pointer &t_prev) : 
            m_value(t_value), m_next(t_next), m_prev(t_prev) {}

        linked_list_node(const linked_list_node& other) : 
            m_value(other.m_value), m_next(other.m_next), m_prev(other.m_prev) {}

        value_type& value() {
            return m_value;
        }

        self_pointer& next() {
            return m_next;
        }

        self_pointer& prev() {
            return m_prev;
        }
        
        const value_type& value() const {
            return m_value;
        }

        const self_pointer& next() const {
            return m_next;
        }

        const self_pointer& prev() const {
            return m_prev;
        }
    private:
        value_type m_value;
        self_pointer m_next;
        self_pointer m_prev;
    };
    

    template <typename U>
    class linked_list_iterator {
    public:
        typedef U value_type;
        typedef value_type& reference;
        typedef const value_type& const_reference;
        typedef value_type* pointer;
        typedef const value_type* const_pointer;
        typedef linked_list_node<value_type>* pointer_type;

        linked_list_iterator(const pointer_type &t_curr) : m_curr(t_curr) {}

        pointer_type operator()() {
            return m_curr;
        }

        const pointer_type operator()() const {
            return m_curr;
        }

        linked_list_iterator& operator++() {
            m_curr = m_curr->next();
            return *this;
        }

        linked_list_iterator& operator--() {
            m_curr = m_curr->prev();
            return *this;
        }

        bool operator==(const linked_list_iterator &other) const {
            return m_curr == other.m_curr;
        }

        bool operator!=(const linked_list_iterator &other) const {
            return m_curr != other.m_curr;
        }

        const_reference operator*() const {
            return m_curr->value();
        }

        reference operator*() {
            return m_curr->value();
        }

        pointer operator->() {
            return &(m_curr->value());
        }

        const pointer operator->() const {
            return &(m_curr->value());
        }

    private:
        pointer_type m_curr;
    };


    template <typename T, class Allocator = std::allocator<linked_list_node<T>>>
    class linked_list {
    public: 
        typedef T value_type;
        typedef value_type& reference;
        typedef const value_type& const_reference;
        typedef value_type* pointer;

        typedef Allocator allocator_type;
        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;
        
        typedef linked_list_node<value_type> node_type;
        typedef linked_list_node<value_type>* p_node_type;
        typedef linked_list_node<value_type>& r_node_type;

        typedef linked_list_iterator<value_type> iterator;
        typedef const iterator const_iterator;

        linked_list() : m_size(0), m_head(nullptr), m_tail(nullptr) {}

        linked_list(const linked_list &other) : m_size(0), m_head(nullptr), m_tail(nullptr) {
            for (auto it = other.begin(); it != other.end(); ++it) {
                push_back(*it);
            }
        }

        linked_list(std::initializer_list<value_type> init_list) : m_size(0), m_head(nullptr), m_tail(nullptr) {
            for (auto it = init_list.begin(); it != init_list.end(); ++it) {
                push_back(*it);
            }
        }

        ~linked_list() {
            auto start = m_head;

            while (start != nullptr) {
                auto to_delete = start;
                start = start->next();
                m_allocator.destroy(to_delete);
                m_allocator.deallocate(to_delete , 1);
            }
            m_head = nullptr;
            m_tail = nullptr;
            m_size = 0;
        }

        void clear() noexcept {
            this->~linked_list();
        }

        linked_list& operator=(const linked_list& other) {
            if (this == &other) {
                return *this;
            }

            this->~linked_list();
            new (this) linked_list(other);

            return *this;
        }

        iterator begin() noexcept {
            return iterator(m_head);
        }

        const_iterator begin() const noexcept {
            return const_iterator(m_head);
        }

        iterator end() noexcept {
            return iterator(nullptr);
        }

        const_iterator end() const noexcept {
            return const_iterator(nullptr);
        }

        size_type size() const noexcept {
            return m_size;
        }

        bool empty() const noexcept {
            return m_size == 0;
        }

        reference front() {
            return m_head->value();
        } 

        const_reference front() const {
            return m_head->value();
        }

        reference back() {
            return m_tail->value();
        } 

        const_reference back() const {
            return m_tail->value();
        }


        void push_front(const value_type &t_value) {
            auto new_node = m_allocator.allocate(1);
            m_allocator.construct(new_node, linked_list_node(t_value));
            
            if (empty()) {
                m_head = new_node;
                m_tail = new_node;
                ++m_size;
                return;
            }        

            new_node->next() = m_head;
            m_head->prev() = new_node;
            m_head = new_node;
            ++m_size;
        }

        void push_back(const value_type &t_value) {
            auto new_node = m_allocator.allocate(1);
            m_allocator.construct(new_node, linked_list_node(t_value));

            if (empty()) {
                m_head = new_node;
                m_tail = new_node;
                ++m_size;
                return;
            }

            new_node->prev() = m_tail;
            m_tail->next() = new_node;
            m_tail = new_node;
            ++m_size;
        }

        void pop_front() {
            auto to_delete = m_head;
            m_head = m_head->next();
            m_allocator.destroy(to_delete);
            m_allocator.deallocate(to_delete, 1);

            if (m_size == 1) {
                m_tail = nullptr;
            } else {
                m_head->prev() = nullptr;
            }

            --m_size;
        }

        void pop_back() {
            auto to_delete = m_tail;

            m_tail = m_tail->prev();
            m_allocator.destroy(to_delete);
            m_allocator.deallocate(to_delete, 1);

            if (m_size == 1) {
                m_head = nullptr;
            } else {
                m_tail->next() = nullptr;
            }

            --m_size;
        }

        iterator insert(const_iterator position, const value_type& t_value) {
            auto new_node = m_allocator.allocate(1);
            m_allocator.construct(new_node, linked_list_node(t_value));

            if (empty()) {
                m_head = new_node;
                m_tail = new_node;
                ++m_size;
                return iterator(m_head);
            }

            if (position == end()) {
                new_node->prev() = m_tail;
                m_tail->next() = new_node;
                m_tail = new_node;
                ++m_size;
                return iterator(m_tail);
            }

            new_node->next() = position();
            new_node->prev() = position()->prev();
            position()->prev()->next() = new_node;
            ++m_size;

            return iterator(new_node);
        }

        iterator erase(const_iterator position) {
            auto to_delete = position();

            auto prev_node = position()->prev();
            auto next_node = position()->next();
            
            m_allocator.destroy(to_delete);
            m_allocator.deallocate(to_delete, 1);

            if (prev_node == nullptr && next_node == nullptr) {
                m_head = nullptr;
                m_tail = nullptr;
            } else if (prev_node == nullptr) {
                m_head = next_node;
                next_node->prev() = nullptr;
            } else if (next_node == nullptr) {
                m_tail = prev_node;
                prev_node->next() = nullptr;
            } else {
                prev_node->next() = next_node;
                next_node->prev() = prev_node;
            }

            --m_size;
            return next_node;
        }

        /************************************
         * Needs to overload == for this
         ************************************/
        
        iterator find(const value_type &value) {
            auto start = m_head;

            while (start != nullptr) {
                if (start->value() == value) {
                    return iterator(start);
                }
                start = start->next();
            }

            return iterator(nullptr);
        }

        /*****************************************
         * Needs to overload < operator
         * Assumes from low to high
         *****************************************/

        void insert_order(const value_type& t_value) {
            auto new_node = m_allocator.allocate(1);
            m_allocator.construct(new_node, linked_list_node(t_value));

            if (empty()) {
                m_head = new_node;
                m_tail = new_node;
                ++m_size;
                return;
            }

            if (t_value < m_head->value()) {
                m_head->prev() = new_node;
                new_node->next() = m_head;
                m_head = new_node;
                ++m_size;
                return;
            }

            auto start = m_head;

            while (start != nullptr) {
                if (t_value < start->value()) {
                    break;
                }
                start = start->next();
            }
            
            if (start == nullptr) {
                m_tail->next() = new_node;
                new_node->prev() = m_tail;
                m_tail = new_node;
                ++m_size;
            } else {
                start = start->prev();

                start->next()->prev() = new_node;
                new_node->next() = start->next();            
                start->next() = new_node;
                new_node->prev() = start;
                ++m_size;
            }
        }
               
    private:
        allocator_type m_allocator;
        p_node_type m_head;
        p_node_type m_tail;
        size_type m_size;
    };
}












#endif