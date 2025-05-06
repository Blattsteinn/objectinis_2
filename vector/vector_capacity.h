// vector_capacity.h
#pragma once

#include "vector_library.h"

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
void Vector<T>::reserve(size_type n) {
    if (n <= capacity_) 
        return;
    T* new_array = static_cast<T*>(
        ::operator new[](n * sizeof(T))
    );

    for (size_type i = 0; i < size_; ++i) {
        new (&new_array[i]) T(std::move(array[i]));
        array[i].~T();
    }

    ::operator delete[](array);
    array     = new_array;
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
// reduces memory usage by freeing unused memory
// (public member function)
template<typename T>
void Vector<T>::shrink_to_fit(){
        if (capacity_ == size_) 
        return;   // nothing to shrink

        T* new_array = static_cast<T*>(
            ::operator new[](size_ * sizeof(T))
        );

    
    try {
        for (size_type i = 0; i < size_; ++i) {
            new (&new_array[i]) T(std::move(array[i]));
            array[i].~T();
        }
    } catch (...) {
        for (size_type j = 0; j < size_; ++j) {
            new_array[j].~T();
        }
        ::operator delete[](new_array);
        throw;
    }

    ::operator delete[](array);

    array     = new_array;
    capacity_ = size_;
}