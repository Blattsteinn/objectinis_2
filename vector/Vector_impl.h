// Vector_impl.h
#pragma once

#include "vector.h"

   // CAPACITY FUNCTIONS
    template<typename T>    
    void Vector<T>::double_the_capacity(){
        size_t oldCap = capacity_;
        size_t newCap = (oldCap == 0 ? 1 : oldCap * 2);          // 2) 1 if you zero, otherwise 2×
        
        // allocates a new array
        T* newArray = new T[newCap];
        
        // copies everything
        for(size_t i = 0; i < capacity_; i++){
            newArray[i] = array[i];
        }

        delete[] array;
        array = newArray;
        capacity_ = newCap;
    }

    // RESERVE
    template<typename T>
    void Vector<T>::reserve(size_t n) {
        if (n <= capacity_)
            return;
        
        T* new_array = new T[n];
        for (size_t i = 0; i < size_; ++i)
            new_array[i] = array[i];
        
        delete[] array;
        array = new_array;
        capacity_ = n;
    }
    
    // --------------------  MODIFIERS  -------------------- 
// clear
//   Clears all elements from the vector.
//   (public member function)
    template<typename T>
    void Vector<T>::clear(){
        for (size_t i = 0; i < size_; ++i) {
            array[i].~T();
        }
        size_ = 0;
    }

// insert
//   Inserts one or more elements at a given position.
//   (public member function)
    // inserts one element
    template<typename T>
    void Vector<T>::insert(const_iterator pos, const T& value ){
        
        size_t idx = static_cast<size_t>(pos - begin());

        if(size_ == capacity_){
            double_the_capacity(); }

        if(idx == size_){
            push_back(value);
            return;
        }

        T* newArray = new T[capacity_];

        size_t i = 0;
        for(size_t oldIdx = 0; oldIdx < size_; ++i, ++oldIdx){
            if(oldIdx == idx){
                newArray[i++] = value;
            } 
            newArray[i] = array[oldIdx];
            
        }
        ++size_;
        delete[] array;
        array = newArray;
    }

    template<typename T>
    void Vector<T>::insert(const_iterator pos, T&& value){
        size_t idx = static_cast<size_t>(pos - begin());
        if (size_ >= capacity_) double_the_capacity();
    
        if (idx == size_) {
            // at end: either copy or move via push_back
            push_back(std::forward<T>(value));
            return;
        }
    
        // allocate new buffer
        T* newArray = new T[capacity_];
        size_t i = 0;
    
        // splice in the new element at index idx
        for (size_t old = 0; old < size_; ++old) {
            if (old == idx) {
            newArray[i++] = std::forward<T>(value);
            }
            newArray[i++] = array[old];
        }
    
        ++size_;
        delete[] array;
        array = newArray;
    }

// insert_range (C++23)
//   Inserts a range of elements [first, last) at a given position.
//   (public member function)

// emplace (C++11)
//   Constructs an element in-place at a given position.
//   (public member function)

// erase
//   Removes the element at a given position (or a range of elements).
//   (public member function)

// push_back
//   Appends a copy of the given element to the end of the vector.
//   (public member function)
    template<typename T>
    void Vector<T>::push_back(T element){
        if(size_ == capacity_){
            Vector::double_the_capacity();
        }
        array[size_] = element;
        ++size_;

    }

// emplace_back (C++11)
//   Constructs an element in-place at the end of the vector.
//   (public member function)

// append_range (C++23)
//   Appends a range of elements [first, last) to the end of the vector.
//   (public member function)

// pop_back
//   Removes the last element from the vector.
//   (public member function)
    template<typename T>
    void Vector<T>::pop_back(){
        array[size_].~T();
        --size_;
    }
// resize
//   Changes the number of elements stored in the vector.
//   If new size > old size, value-initializes new elements.
//   If new size < old size, erases excess elements.
//   (public member function)
    template<typename T>
    void Vector<T>::resize(size_t count){
        if(count == size_){ return; }

        else if(size_ > count ) {
            for(size_t i = count; i < size_; ++i){
                array[i].~T();
            }
            size_ = count;
            return;
        }

        else {
            reserve(count);
            for (size_t i = size_; i < count; ++i) {
                new (&array[i]) T();
            }
            size_ = count;
            return;
        }
    };

    template<typename T>
    void Vector<T>::resize(size_t count, const T& value ){
        if(count == size_){ return; }

        else if(size_ > count ) {
            for(size_t i = count; i < size_; ++i){
                array[i].~T();
            }
            size_ = count;
            return;
        }
        
        else {
            reserve(count);
            for (size_t i = size_; i < count; ++i) {
                new (&array[i]) T(value);
            }
            size_ = count;
            return;
        }
    };

// swap
//   Exchanges the contents of this vector with another.
//   (public member function)