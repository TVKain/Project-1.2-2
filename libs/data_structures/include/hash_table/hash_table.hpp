/**********************************************
 * Hash Map implementation in C++
 * Deals with collision using seperate chaining 
 **********************************************/

#pragma once
#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include <utility>
#include <string>
#include <functional>
#include <iostream>
#include <initializer_list>

#include "array_list.hpp"
#include "linked_list.hpp"


namespace ds {
    typedef std::size_t hash_value;

    template <class Key>
    struct hash;

    template <> 
    struct hash<std::string> {
        hash_value operator()(const std::string &key) const {
            hash_value ret = 0;
            for (const auto &c : key) {
                ret += static_cast<hash_value>(c);
            }
            return ret;
        }
    };

    template <> 
    struct hash<char> {
        hash_value operator()(const char &key) const {
            return static_cast<hash_value>(key * 26 / 7 * 2);
        }
    };


    template <> 
    struct hash<int> {
        hash_value operator()(const int &key) const {
            return static_cast<hash_value>(key * 26 / 7 * 2);
        }
    };

    template <> 
    struct hash<float> {
        hash_value operator()(const float &key) const {
            return static_cast<hash_value>(key * 26 / 7 * 2);
        }
    };


    template <> 
    struct hash<double> {
        hash_value operator()(const double &key) {
            return static_cast<hash_value>(key * 26 / 7 * 2);
        }
    };
    
    template <class T>
    struct hash<T*> {
        hash_value operator()(const T* key) {
            return reinterpret_cast<hash_value>(key);
        }
    };

    template <class Key, class T, class Hash = ds::hash<Key>, class KeyEqual = std::equal_to<Key>>
    class hash_table {
    public:
        template <class U>
        class hash_table_iterator {
        public:
            typedef typename ds::linked_list_iterator<U> iterator_type;
            typedef U value_type;
            typedef value_type& reference;
            typedef const value_type& const_reference;
            typedef value_type* pointer;
            typedef const value_type* const_pointer;
            typedef std::size_t size_type;

            hash_table_iterator(hash_table &t_parent, const iterator_type &t_curr) 
                : m_curr(t_curr), m_bucket(0), m_parent(t_parent) {}
            hash_table_iterator(hash_table &t_parent, const iterator_type &t_curr, const size_type &t_bucket) 
                : m_curr(t_curr), m_bucket(t_bucket), m_parent(t_parent) {}

            hash_table_iterator& operator++() {
                ++m_curr;

                while (m_curr == nullptr) {
                    ++m_bucket;
                    
                    if (m_bucket == m_parent.m_bucket_count) {
                        return *this;
                    }

                    m_curr = iterator_type(m_parent.m_data[m_bucket].begin());
                }

                return *this;
            }

            iterator_type operator()() {
                return m_curr;
            }

            const iterator_type operator()() const {
                return m_curr;
            }

            bool operator==(const hash_table_iterator& other) const {
                return m_curr == other.m_curr;
            }

            bool operator!=(const hash_table_iterator& other) const {
                return m_curr != other.m_curr;
            }

            const_reference operator*() const {
                return *m_curr;
            }

            reference operator*() {
                return *m_curr;
            }

            pointer operator->() {
                return &(*m_curr);
            }

            const_pointer operator->() const {
                return &(*m_curr);
            }
        private:
            hash_table& m_parent;
            iterator_type m_curr;
            size_type m_bucket;            
        };

        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;

        typedef Key key_type;
        typedef T mapped_type;
        typedef std::pair<const Key, T> value_type;
        typedef value_type& reference;
        typedef const value_type& const_reference;

        typedef hash_table_iterator<value_type> iterator;

        typedef Hash hasher;
        typedef KeyEqual key_equal;    

        hash_table() : m_size(0) {
            for (size_type i = 0; i < m_bucket_count; ++i) {
                m_data.push_back(ds::linked_list<value_type>());
            }
        }

        hash_table(const std::initializer_list<value_type> &init_list) : m_size(init_list.size()) {
            for (size_type i = 0; i < m_bucket_count; ++i) {
                m_data.push_back(ds::linked_list<value_type>());
            }
            
            for (const auto &it : init_list) {
                insert(it);
            }
        }

        hash_table(const hash_table &other) : m_size(other.m_size), m_data(other.m_data), m_bucket_count(other.m_bucket_count) { }

        hash_table& operator=(const hash_table &other) {
            if (this == &other) {
                return *this;
            }

            this->~hash_table();
            new (this) hash_table(other);
            return *this;
        }

        ~hash_table() = default; 

        mapped_type& operator[](const key_type& key) {
            auto find_in_bucket = find(key); 

            if (find_in_bucket == end()) {
                auto iter = insert(std::make_pair(key, mapped_type())).first;
                ++m_size;
                return (*iter).second;
            }

            return (*find_in_bucket).second;
        }

        std::pair<iterator, bool> insert_or_assign(const key_type &key, const mapped_type &mapped) {
            auto find_in_bucket = find(key);

            if (find_in_bucket == end()) {
                ++m_size;
                return insert(std::make_pair(key, mapped));
            }

            (*find_in_bucket).second = mapped;

            return std::make_pair(find_in_bucket, false);
        }
                
        iterator begin() noexcept {
            if (empty()) {
                return iterator(*this, nullptr, m_bucket_count);
            }

            size_type first;
            for (size_type i = 0; i < m_bucket_count; ++i) {
                if (!m_data[i].empty()) {
                    first = i;
                    break;
                }
            }
            return iterator(*this, m_data[first].begin(), first);
        }

        iterator end() noexcept {
            return iterator(*this, nullptr, m_bucket_count);
        }

        std::pair<iterator, bool> insert(const value_type& value) {
            size_type bucket_index = m_hash_function(value.first) % m_bucket_count;

            auto &current_bucket = m_data[bucket_index];
            
            for (auto it = current_bucket.begin(); it != current_bucket.end(); ++it) {
                if (m_key_compare((*it).first, value.first)) {
                    return std::make_pair(iterator(*this, it, bucket_index), false);
                }
            }

            ++m_size;
            auto it = current_bucket.insert(current_bucket.end(), value);
            return std::make_pair(iterator(*this, it, bucket_index), true);
        }

        bool contains(const key_type &key) {
            return find(key) != end();
        }

        iterator find(const key_type &key) {
            size_type bucket_index = m_hash_function(key) % m_bucket_count;

            auto &current_bucket = m_data[bucket_index];

            auto to_find = current_bucket.begin();
            
            while (to_find != current_bucket.end()) {
                if (m_key_compare((*to_find).first, key)) {
                    return iterator(*this, to_find, bucket_index);
                }
                ++to_find;
            }

            return iterator(*this, to_find, m_bucket_count);
        }

        size_type erase(const key_type &key) {
            size_type bucket_index = m_hash_function(key) % m_bucket_count;

            auto &current_bucket = m_data[bucket_index];

            auto to_delete = find(key)();

            if (to_delete != current_bucket.end()) {
                current_bucket.erase(to_delete);
                --m_size;
                return 1;
            }

            return 0;
        }

        size_type size() const noexcept {
            return m_size;
        }

        bool empty() const noexcept {
            return m_size == 0;
        }

        size_type bucket_size(const size_type &n) const {
            return m_data[n].size();
        }

        void clear() noexcept {
            for (size_type i = 0; i < m_bucket_count; ++i) {
                m_data[i].clear();
            }
            m_size = 0;
        }

    private:
        hasher m_hash_function;
        key_equal m_key_compare;
        size_type m_size;
        const size_type m_bucket_count = 256;
        array_list<linked_list<value_type>> m_data;
    };
}









#endif