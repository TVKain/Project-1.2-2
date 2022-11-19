#pragma once
#ifndef ARRAY_LIST_HPP
#define ARRAY_LIST_HPP

#include <memory>
#include <stdexcept>


namespace ds {
    template <typename T, class Allocator = std::allocator<T>>
    class array_list {
    public:
        template <typename U>
        class array_list_iterator {
        public:
            typedef U value_type;
            typedef value_type& reference;
            typedef const value_type& const_reference;
            typedef value_type* pointer;
            typedef const pointer const_pointer;
            typedef std::ptrdiff_t difference_type;
            typedef std::size_t size_type;   

            array_list_iterator(const pointer &t_curr) : m_curr(t_curr) {}

            pointer operator()() {
                return m_curr;
            }

            const_pointer operator()() const {
                return m_curr;
            }

            array_list_iterator& operator+(const difference_type &diff) {
                return array_list_iterator(m_curr + diff);
            }

            array_list_iterator& operator-(const difference_type &diff) {
                return array_list_iterator(m_curr - diff);
            }
            
            array_list_iterator& operator++() {
                ++m_curr;
                return *this;
            }

            array_list_iterator& operator--() {
                --m_curr;
                return *this;
            }

            bool operator==(const array_list_iterator &other) const {
                return m_curr == other.m_curr;
            }

            bool operator!=(const array_list_iterator &other) const {
                return m_curr != other.m_curr;
            }

            const_reference operator*() const {
                return *m_curr;
            }

            reference operator*() {
                return *m_curr;
            }

        private:
            pointer m_curr;
        };

        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;

        typedef T value_type;
        typedef value_type& reference;
        typedef const reference const_reference;
        typedef value_type* pointer;
        typedef value_type* iterator;
        typedef const iterator const_iterator;

        typedef Allocator allocator_type;


        array_list() : m_size(0), m_capacity(0), m_data(nullptr) {}

        array_list(const size_type &t_capacity) : m_size(0), m_capacity(t_capacity) {
            m_data = m_allocator.allocate(m_capacity);
        }

        array_list(const array_list &other) : m_size(other.m_size), m_capacity(other.m_capacity) {
            m_data = m_allocator.allocate(m_capacity);
            for (size_type i = 0; i < m_size; ++i) {
                m_allocator.construct(m_data + i, other[i]);
            }
        }

        array_list(size_type n, value_type v) : m_size(n), m_capacity(n) {
            m_data = m_allocator.allocate(m_capacity);
            for (size_type i = 0; i < m_size; ++i) {
                m_allocator.construct(m_data + i, v);
            }
        }

        array_list(const std::initializer_list<value_type> &init_list) 
            : m_size(init_list.size()), m_capacity(init_list.size()) {
            m_data = m_allocator.allocate(m_capacity);

            auto start = init_list.begin();
            auto dest = begin();
            while (start != init_list.end()) {
                m_allocator.construct(dest, *start);
                ++start;
                ++dest;
            }
        }

        array_list& operator=(const array_list &other) {
            if (this == &other) {
                return *this;
            }
            
            this->~array_list();
            new (this) array_list(other);

            return *this;
        }

        ~array_list() {
            for (size_type i = 0; i < m_size; ++i) {
                m_allocator.destroy(m_data + i);
            }
            m_allocator.deallocate(m_data, m_capacity);
            m_data = nullptr;
            m_size = 0;
            m_capacity = 0;
        }

        iterator begin() noexcept {
            return m_data;
        }

        iterator end() noexcept {
            return m_data + m_size;
        }

        const_iterator cbegin() const noexcept {
            return m_data;
        }

        const_iterator cend() const noexcept {
            return m_data + m_size;
        }

        size_type size() const noexcept {
            return m_size;
        }

        size_type capacity() const noexcept {
            return m_capacity;
        }

        reference front() noexcept {
            return m_data[0];
        }

        const_reference front() const noexcept {
            return m_data[0];
        }

        reference back() {
            return m_data[m_size - 1];
        }

        const_reference back() const noexcept {
            return m_data[m_size - 1];
        }

        const_reference operator[](const size_type &pos) const {
            return m_data[pos];
        }
        reference operator[](const size_type &pos) {
            return m_data[pos];
        }

        bool empty() const noexcept {
            return m_size == 0;
        }

        void push_back(const value_type &value) {
            if (m_size + 1 > m_capacity) {
                m_capacity == 0 ? realloc(1) : realloc(m_capacity * GROWTH);
            }

            m_allocator.construct(m_data + m_size, value);
            ++m_size;
        }

        void pop_back() {
            if (m_size == 0) {
                throw std::out_of_range("Can not pop_back() an empty array list");
            }
            m_allocator.destroy(m_data + m_size - 1);
            --m_size;
        }

    private:
        size_type m_size;
        size_type m_capacity;
        pointer m_data;
        allocator_type m_allocator;
        const size_type GROWTH = 2;

        void realloc(size_type t_capacity) {
            pointer t_data = m_allocator.allocate(t_capacity);
            
            for (size_type i = 0; i < m_size; ++i) {
                m_allocator.construct(t_data + i, m_data[i]);
                m_allocator.destroy(m_data + i);
            }

            m_allocator.deallocate(m_data, m_capacity);

            m_capacity = t_capacity;
            m_data = t_data;
        }
    };
}







#endif