#pragma once
#ifndef BINARY_SEARCH_TREE
#define BINARY_SEARCH_TREE

#include <functional>
#include <memory>
#include <utility>
#include <initializer_list>

#include "array_list.hpp"

namespace ds {
    
    template <typename T> 
    class binary_search_tree_node {
    public:
        typedef T value_type;
        typedef value_type& reference;
   
        typedef const reference const_reference;
        typedef binary_search_tree_node* self_pointer;
        
        binary_search_tree_node() 
            : m_parent(nullptr), m_left(nullptr), m_right(nullptr), m_value(value_type()) {}

        binary_search_tree_node(const value_type &t_value) 
            : m_parent(nullptr), m_left(nullptr), m_right(nullptr), m_value(t_value) {}

        binary_search_tree_node(
            const self_pointer &t_parent, const self_pointer &t_left, 
            const self_pointer &t_right, const value_type &t_value) : 
            m_parent(t_parent), m_left(t_left), m_right(t_right), m_value(t_value) {}
    
        reference value() {
            return m_value;
        }

        const_reference value() const {
            return m_value;
        }

        self_pointer& parent() {
            return m_parent;
        }

        const self_pointer& parent() const {
            return m_parent;
        }

        self_pointer& left() {
            return m_left;
        }

        self_pointer& right() {
            return m_right;
        }

        const self_pointer& left() const {
            return m_left;
        }

        const self_pointer& right() const {
            return m_right;
        }

    private:
        self_pointer m_right;
        self_pointer m_left;
        self_pointer m_parent;
        value_type m_value;
    };

    


    template <class Key, class T, class KeyCompare = std::less<Key>,
        class Allocator = std::allocator<binary_search_tree_node<std::pair<const Key, T>>> >
    class binary_search_tree {
    public:
        template <typename U>
        class binary_search_tree_iterator {
        public:
            typedef U value_type;
            typedef value_type& reference;
            typedef const value_type& const_reference;
            typedef value_type* pointer;
            typedef const value_type* const_pointer;
            typedef binary_search_tree_node<value_type>* pointer_type;

            binary_search_tree_iterator(const pointer_type &t_curr) 
                : m_curr(t_curr) {}

            pointer_type operator()() {
                return m_curr;
            }

            const pointer_type operator()() const {
                return m_curr;
            }

            binary_search_tree_iterator& operator++() {
                // If the current node has a right child 
                // Find the minimum of the subtree(right-child)
                if (m_curr->right() != nullptr) {
                    m_curr = m_curr->right();
                    while (m_curr->left() != nullptr) {
                        m_curr = m_curr->left();
                    }
                    return *this;
                }
                // If the current node does not have a right child
                // The successor is the ancestor whose 
                // left child is also an ancestor of the current node
                
                auto p_curr = m_curr->parent();
                auto tmp_curr = m_curr;

                while (p_curr != nullptr && tmp_curr == p_curr->right()) {
                    tmp_curr = p_curr;
                    p_curr = p_curr->parent();
                }

                m_curr = p_curr;
                return *this;
            }

            binary_search_tree_iterator& operator--() {
                // If the current node has a right child 
                // Find the minimum of the subtree(right-child)
                if (m_curr->left() != nullptr) {
                    m_curr = m_curr->left();
                    while (m_curr->right() != nullptr) {
                        m_curr = m_curr->right();
                    }
                    return *this;
                }
                // If the current node does not have a left child
                // The successor is the ancestor whose right child 
                // is also an ancestor of the current node
                
                auto p_curr = m_curr->parent();
                auto tmp_curr = m_curr;

                while (p_curr != nullptr && tmp_curr == p_curr->left()) {
                    tmp_curr = p_curr;
                    p_curr = p_curr->parent();
                }

                m_curr = p_curr;
                return *this;
            }

            bool operator==(const binary_search_tree_iterator &other) const {
                return m_curr == other.m_curr;
            }

            bool operator!=(const binary_search_tree_iterator &other) const {
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

            const_pointer operator->() const {
                return &(m_curr->value());
            }
        private:
            pointer_type m_curr;
        };

        typedef std::size_t size_type;
        
        typedef Key key_type;
        typedef T mapped_type;
        typedef std::pair<const Key, T> value_type;
        typedef value_type& reference;
        typedef const value_type& const_reference;

        typedef binary_search_tree_node<value_type> node_type;
        typedef node_type* node_pointer;
        typedef node_type& node_reference;

        typedef binary_search_tree_iterator<value_type> iterator;
        typedef const iterator const_iterator;

        typedef KeyCompare compare_type;
        typedef Allocator allocator_type;

        /***************************
         * @brief: empty constructor
         ***************************/
        binary_search_tree() : m_size(0), m_root(nullptr) {}

        /**************************
         * @brief: Copy constructor
         **************************/
        binary_search_tree(const binary_search_tree &other) : m_size(0), m_root(nullptr) {
            for (const auto &it : other) {
                insert(it);
            }
        }

        /*****************************************
         * @brief: Construct from initializer list
         *****************************************/
        binary_search_tree(const std::initializer_list<value_type> &init_list) : m_size(0), m_root(nullptr) {
            for (const auto &it : init_list) {
                insert(it);
            }
        }

        /*********************************
         * @brief: Overload equal operator
         *********************************/
        binary_search_tree& operator=(const binary_search_tree &other) {
            if (this == &other) {
                return *this;
            }
            this.~binary_search_tree();
            new (this) binary_search_tree(other);
            return *this;
        }
        
        /********************
         * @brief: destructor
         ********************/
        ~binary_search_tree() {
            ds::array_list<key_type> keys;

            for (iterator it = begin(); it != end(); ++it) {
                keys.push_back((*it).first);
            }

            for (auto it = keys.begin(); it != keys.end(); ++it) {
                erase(*it);
            }
        }

        /************************
         * @brief: Begin iterator
         ************************/
        iterator begin() noexcept {
            if (empty()) {
                return iterator(nullptr);
            }

            node_pointer c_root = m_root;

            return iterator(minimum(c_root));
        }

        const_iterator begin() const noexcept {
            if (empty()) {
                return iterator(nullptr);
            }

            node_pointer c_root = m_root;

            return iterator(minimum(c_root));
        }
        
        iterator rbegin() noexcept {
            if (empty()) {
                return iterator(nullptr);
            }

            node_pointer c_root = m_root;
            return iterator(maximum(c_root));
        }

        /**********************
         * @brief: End iterator
         **********************/
        iterator end() noexcept {
            return iterator(nullptr);
        }

        const_iterator end() const noexcept {
            return iterator(nullptr);
        }
        
        iterator rend() noexcept {
            return iterator(nullptr);
        }

        /********************************
         * @brief: Check if tree is empty
         * @return: bool
         *      true if tree is empty
         *      false otherwise
         ********************************/
        bool empty() const noexcept {
            return m_size == 0;
        }

        /***************************************
         * @brief: Get the size of the container
         ***************************************/
        size_type size() const noexcept {
            return m_size;
        }


        /********************************************************************************************
         * @brief: Insert a key-value pair into the tree - no dupes key are allowed
         * @params: value_type
         *      The key-value pair to be inserted
         * @return: std::pair<iterator, bool>
         *      iterator - the iterator to the newly inserted element or the element prevented insert
         *      bool - true if insert success false otherwise
         ********************************************************************************************/
        std::pair<iterator, bool> insert(const value_type& value) {
            auto f = find(value.first);

            if (f != end()) {
                return std::make_pair(f, false);
            }

            node_pointer c_root = m_root;
            node_pointer p_node = nullptr;

            auto new_node = m_allocator.allocate(1);
            m_allocator.construct(new_node, binary_search_tree_node(value));

            // find the parent of the newly inserted node
            while (c_root != nullptr) {
                p_node = c_root;
                if (m_key_compare(value.first, (c_root->value()).first)) {
                    c_root = c_root->left();
                } else {
                    c_root = c_root->right();
                }
            }

            new_node->parent() = p_node;

            if (p_node == nullptr) {
                m_root = new_node;
            } else if (m_key_compare(new_node->value().first, p_node->value().first)) {
                p_node->left() = new_node;
            } else {
                p_node->right() = new_node;
            } 

            ++m_size;
            return std::make_pair(iterator(new_node), true);
        }

        /******************************************************
         * @brief: Find the node with the input key
         * @params: key-type  
         *          the input key
         * @return: iterator
         *          the iterator to the node with the input key
         *          end() if no node was found
         ******************************************************/
        iterator find(const key_type &key) {
            auto c_root = m_root;

            while (c_root != nullptr && (
                m_key_compare(c_root->value().first, key) || 
                m_key_compare(key, c_root->value().first))
            ) {
                if (m_key_compare(key, c_root->value().first)) {
                    c_root = c_root->left();
                } else {
                    c_root = c_root->right();
                }
            }

            return iterator(c_root);
        }

        const_iterator find(const key_type &key) const {
            auto c_root = m_root;

            while (c_root != nullptr && (
                m_key_compare(c_root->value().first, key) || 
                m_key_compare(key, c_root->value().first))
            ) {
                if (m_key_compare(key, c_root->value().first)) {
                    c_root = c_root->left();
                } else {
                    c_root = c_root->right();
                }
            }

            return iterator(c_root);
        }

        mapped_type& operator[](const key_type &key) {
            auto f = find(key);

            if (f == end()) {
                auto iter = insert(std::make_pair(key, mapped_type())).first;
                ++m_size;
                return (*iter).second;
            }

            return (*f).second;
        }

       /*****************************************
         * @brief: Erase a node with the input key
         * @params: key_type
         *      The key of the node to be deleted
         * @return: size_type
         *      0 if no deletion took place
         *      1 if deletetion took place
         *****************************************/
        size_type erase(const key_type& key) {
            iterator to_delete = find(key);

            if (to_delete == end()) {
                return 0;
            }

            node_pointer ptr_to_delete = to_delete();

            // No left child => replace with righht child
            if (ptr_to_delete->left() == nullptr) {
                transplant(ptr_to_delete, ptr_to_delete->right());
            } else if (ptr_to_delete->right() == nullptr) {
                // No right child but left child exists          
                transplant(ptr_to_delete, ptr_to_delete->left());
            } else {
                // Both children are present
                auto s = minimum(ptr_to_delete->right());
                // If the successor is further down the tree 
                if (s != ptr_to_delete->right()) {
                    transplant(s, s->right());
                    s->right() = ptr_to_delete->right();
                    s->right()->parent() = s;
                }
                transplant(ptr_to_delete, s);
                s->left() = ptr_to_delete->left();
                s->left()->parent() = s;
            }

            m_allocator.destroy(ptr_to_delete);
            m_allocator.deallocate(ptr_to_delete, 1);

            --m_size;
            return 1;
        }

        /*************************
         * @brief: clear container
         *************************/
        void clear() {
            this->~binary_search_tree();
            m_size = 0;
            m_root = nullptr;
        }


    private:
        /******************************************************************
         * @brief: Replace the node pointed by u with the node pointed by v
         * @params:
         *      node_pointer u - to be replaced
         *      node_pointer v - the one to replace with
         ******************************************************************/
        void transplant(node_pointer u, node_pointer v) {
            if (u->parent() == nullptr) {
                m_root = v;
            } else if (u == u->parent()->left()) {
                u->parent()->left() = v;
            } else {
                u->parent()->right() = v;
            }

            if (v != nullptr) {
                v->parent() = u->parent();
            }
        }

        /******************************************************
         * @brief: Find the successor of the node pointed by u
         * @params: node_pointer 
         *      The pointer to the node to find the successor
         * @return: node_pointer
         *      The pointer to the node which is a successor of
         *      the input node
         ******************************************************/
        node_pointer successor(node_pointer u) const {
            // If the current node has a right child
            // Find the minimum of the subtree(right-child)
            if (u->right() != nullptr) {
                return minimum(u->right());
            }

            // If the current node does not have a left child
            // The successor is the ancestor whose left child 
            // is also an ancestor of the current node
            auto p = u->parent();

            while (p != nullptr && u == p->right()) {
                u = p;
                p = p->parent();
            }
            
            return u;
        }

        /********************************************************
         * @brief: Find the predecessor of the node pointed by u
         * @params: node_pointer 
         *      The pointer to the node to find the predecessor
         * @return: node_pointer
         *      The pointer to the node which is a predecessor of
         *      the input node
         ********************************************************/
        node_pointer predecessor(node_pointer u) const {
            // If the current node has a left child
            // Find the maximum of the subtree(left-child)
            if (u->left() != nullptr) {
                return maximum(u->left());
            }
            // If the current node does not have a left child
            // The successor is the ancestor whose right child 
            // is also an ancestor of the current node
            auto p = u->parent();
            
            while (p != nullptr && u == p->left()) {
                u = p;
                p = p->parent();
            }

            return u;
        }

        /*****************************************************************
         * @brief: Find the min node in the subtree with root = u
         * @params: node_pointer 
         *          The pointer that points to the root of the subtree
         * @return: node_pointer
         *          The pointer that points to the min node in the subtree
         *****************************************************************/
        node_pointer minimum(node_pointer u) const {
            while (u->left() != nullptr) {
                u = u->left();
            }
            return u;
        }

        /*****************************************************************
         * @brief: Find the max node in the subtree with root = u
         * @params: node_pointer 
         *          The pointer that points to the root of the subtree
         * @return: node_pointer
         *          The pointer that points to the max node in the subtree
         *****************************************************************/
        node_pointer maximum(node_pointer u) const {
            while (u->right() != nullptr) {
                u = u->right();
            }
            return u;
        }


        compare_type m_key_compare;
        size_type m_size;
        node_pointer m_root;
        allocator_type m_allocator;
    };

}


#endif 