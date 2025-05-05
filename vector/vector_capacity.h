// vector_capacity.h
#pragma once

#include "vector_Library.h"

// empty
// checks whether the container is empty
// (public member function)
template<typename T>
constexpr bool Vector<T>::empty() const noexcept {
    return size_ == 0;
}

// size
// returns the number of elements
// (public member function)
template<typename T>
constexpr typename Vector<T>::size_type Vector<T>::size() const noexcept {
    return size_;
}

// max_size
// returns the maximum possible number of elements
// (public member function)
template<typename T>
constexpr typename Vector<T>::size_type Vector<T>::max_size() const noexcept {
    return std::numeric_limits<size_type>::max() / sizeof(T);
}

// reserve
// reserves storage
// (public member function)
template<typename T>
constexpr void Vector<T>::reserve(size_type n) {
    //if (n > max_size()){
   //     throw std::length_error; }

    if (n <= capacity_)
        return;
    
    T* new_array = new T[n];
    for (size_type i = 0; i < size_; ++i)
        new_array[i] = array[i];
    
    delete[] array;
    array = new_array;
    capacity_ = n;
}

// capacity
// returns the number of elements that can be held in currently allocated storage
// (public member function)
template<typename T>
constexpr typename Vector<T>::size_type Vector<T>::capacity() const noexcept { 
    return capacity_; 
}

// shrink_to_fit
// (DR*)
// reduces memory usage by freeing unused memory
// (public member function)
template<typename T>
void Vector<T>::shrink_to_fit(){
        if (capacity_ == size_) 
        return;   // nothing to shrink

    T* newArray = new T[size_];

    
    try {
        for (size_type i = 0; i < size_; ++i) {
            newArray[i] = std::move(array[i]);
        }
    } catch (...) {
        delete[] newArray;
        throw;
    }

    delete[] array;
    array     = newArray;
    capacity_ = size_;
}