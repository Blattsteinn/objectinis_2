// vector_impl.h
#pragma once

#include "vector_library.h"

template<typename T>
void Vector<T>::double_the_capacity() {
    // Compute new capacity
    size_type newCap = std::max<size_type>(size_type(1), capacity_ * 2);

    // Allocate uninitialized memory
    T* new_array = static_cast<T*>(
        ::operator new[](newCap * sizeof(T))
    );

    // 3) Move-construct existing elements into new_array
    size_type i = 0;
    try {
        for (; i < size_; ++i) {
            new (&new_array[i]) T(std::move(array[i]));
        }
    } catch (...) {
        // Destroys what we did, then frees
        for (size_type j = 0; j < i; ++j) {
            new_array[j].~T();
        }
        ::operator delete[](new_array);
        throw;
    }

    // If succeess --> destroy old objects & free  old memory and commit the new one
    for (size_type j = 0; j < size_; ++j) {
        array[j].~T();
    }
    ::operator delete[](array);

    array     = new_array;
    capacity_ = newCap;
}
