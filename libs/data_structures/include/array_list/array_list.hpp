/* 
 * Implentation of a dynamic array in C++ 
 * This implementation uses the default allocator new 
 */

#pragma once
#ifndef ARRAY_LIST_HPP
#define ARRAY_LIST_HPP

#include <cstddef>
#include <initializer_list> 
#include <algorithm>
#include <limits>
#include <stdexcept>
#include <memory>

namespace ds {
    template <typename T, class Allocator = std::allocator<T>>
    class array_list {
    
    public:
        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;
        typedef T value_type;
        typedef T& reference;
        typedef T* iterator;
        typedef const T* const_iterator;
        typedef Allocator allocater_type;

        /* Iterators */
        iterator begin() {
            return data_;
        }

        const_iterator cbegin() const {
            return data_;
        }

        iterator end() {
            return &data_[size_];
        }

        const_iterator cend() const {
            return &data_[size_];
        }

        /* Capacity */
        
        /* Return the current size of the array */
        size_type size() const noexcept {
            return size_; 
        }

        /* Return the current capacity of the array */
        size_type capacity() const noexcept {
            return capacity_;
        }

        /* Check if the array contains any element */
        bool empty() const noexcept {
            return size_ == 0;
        }

        /* Return maximum possible container size*/
        size_type max_size() const noexcept {
            return std::numeric_limits<size_type>::max();
        }

        /* Constructors */

        /* Initialize empty array */
        array_list() : size_(0), capacity_(0) {
            data_ = nullptr;
        }

        /* Initialize array with space allocated for n items */
        array_list(size_type n) : size_(0), capacity_(n) {
            data_ = allocator_.allocate(capacity_);
        }

        /* Initialize array with n items of value v*/
        array_list(size_type n, value_type v) : size_(n), capacity_(n) {
            data_ = allocator_.allocate(capacity_);
            std::fill_n(data_, n, v);
        }

        /* Initialize array with initializer_list {} */
        array_list(std::initializer_list<value_type> init_list) {
            size_ = init_list.size();
            capacity_ = init_list.size();
            data_ = allocator_.allocate(capacity_);

            std::copy(init_list.begin(), init_list.end(), data_);
        }


        /* Copy Constructor initialize array from a different array  */
        
        array_list(const array_list& a) {
            size_ = a.size();
            capacity_ = a.capacity();
            data_ = allocator_.allocate(capacity_);

            std::copy(a.cbegin(), a.cend(), data_);
        }
        
        

        /* Initialize from first iterator to last iterator */
        array_list(iterator first, iterator last) {
            size_ = last - first;
            capacity_ = size_;
            data_ = allocator_.allocate(capacity_);

            std::copy(first, last, data_);
        }


        /* Operators */

        /* 
         * Assignment operators
         * This assignment operators will copy the array, it does not make another reference 
         */
        
        array_list& operator=(const array_list& a) {
            if (data_ != nullptr) {
                for (size_type i = 0; i < size_; ++i) {
                    allocator_.destroy(data_ + i);
                }
                allocator_.deallocate(data_, capacity_);
                data_ = nullptr;
            }
            
            size_ = a.size();
            capacity_ = a.capacity();
            data_ = allocator_.allocate(capacity_);
            
            
            for (size_type i = 0; i < size_; ++i) {
                data_[i] = a.data_[i];
            }


            return *this;
        }
        

        /* Destructor */
        ~array_list() {
            if (data_ != nullptr) {
                for (size_type i = 0; i < size_; ++i) {
                    allocator_.destroy(data_ + i);
                }
                allocator_.deallocate(data_, capacity_);
                data_ = nullptr;
            }
        }

        

        /* Allocate memory for new_cap elements*/
        void reserve(size_type new_cap) {
            if (new_cap > max_size()) {
                throw std::length_error("Capacity can not exceed maximum size");
            }

            realloc(new_cap);
        }
        
        /* Shrink the empty memories to only the size*/
        void shrink_to_fit() {
            realloc(size_);
        }

        /* Element access */
        
        /* Access element with boundary checking */
        reference at(size_type pos) {
            if (pos < 0 || pos > size_) {
                throw std::out_of_range("Can not access index at" + pos);
            }    

            return data_[pos];
        }

        /* Return reference to the first element */
        reference front() {
            return data_[0];
        }

        /* Return reference to the last element */
        reference back() {
            return data_[size_ - 1];
        }

        /* Return the underlying pointer */
        iterator data() {
            return data_;
        }

        /* Access element without boundary checking */
        reference operator[](size_type pos) {
            return data_[pos];
        }

        /* Modifiers */

        /* 
         * Push an element to the end of the array  
         * Allocate memory twice the current capacity if full 
         */
        void push_back(const value_type& value) {
            if (size_ + 1 > capacity_) {
                capacity_ == 0 ? realloc(1) : realloc(capacity_ * 2);
            }

            allocator_.construct(data_ + size_, value);
            ++size_;
        }

        /* Clear the content of all elements in the array making */
        void clear() noexcept {
            for (size_type i = 0; i < size(); ++i) {
                allocator_.destroy(data_ + i);
            }

            size_ = 0;
        }

        /* Pop the last element of the array */
        void pop_back() {
            if (size_ == 0) {
                throw std::out_of_range("Can not pop_back() an empty array list");
            }
            allocator_.destroy(end() - 1);
            --size_;
        }

        /* Resize the array fill them with default values if count is larger than current size */
        void resize(size_type count) {
            resize(count, value_type());
        }

        /* Resize the array fill them with the value specifed if count is larger than current size */
        void resize(size_type count, const value_type& value) {
            if (count > capacity_) {
                realloc(count);
                for (size_type i = size_; i < count; ++i) {
                    allocator_.construct(data_ + i, value);
                }
            } else if (count < size_) {
                for (size_type i = count; i < size_; ++i) {
                    allocator_.destroy(data_ + i);
                }
            }

            size_ = count;
        }

        /* Insert an element to the position specified by the iterator pos */
        iterator insert(const_iterator pos, const value_type& value) {
            const difference_type index = pos - begin();

            if (index < 0 || index > size()) {
                throw new std::out_of_range("Insert index is out of range");
            }

            if (size() + 1 > capacity()) {
                capacity() == 0 ? realloc(1) : realloc(capacity() * 2);
            }

            for (iterator it = end(); it != &data_[index]; --it) {
                *it = *(it - 1);
                allocator_.destroy(it - 1);
            }
            allocator_.construct(&data_[index], value);
            size_++;
            
            return &data_[index];
        } 
        
        /* Erase an element at the position specified by the iterator pos */
        iterator erase(const_iterator pos) {
            const difference_type index = pos - data_;

            if (index < 0 || index > size_) {
                throw std::out_of_range("Iterator is out of range");
            }
            
            allocator_.destroy(data_ + index);
            for (iterator it = &data_[index]; it != end() - 1; ++it) {
                *it = *(it + 1);
                allocator_.destroy(it + 1);
            }
            
            --size_;

            return data_ + index;
        }        

    private:
        size_type size_;
        size_type capacity_;
        iterator data_; 
        allocater_type allocator_;


        /**********************************************
         * Internal use to reallocate array 
         * if new_cap < size_ values will be truncated 
         **********************************************/
        void realloc(size_type new_cap) {
            T* new_data = allocator_.allocate(new_cap);

            for (size_type i = 0; i < size_; ++i) {
                allocator_.construct(new_data + i, std::move(data_[i]));
                allocator_.destroy(data_ + i);
            }

            allocator_.deallocate(data_, capacity_);

            data_ = new_data;
            capacity_ = new_cap;
        }
    };    
}


#endif