// vector_impl.h
#pragma once

#include "vector.h"

template<typename T>
void Vector<T>::double_the_capacity() {
    // 1) Compute new capacity (at least 1, then ×2)
    size_type newCap = std::max<size_type>(size_type(1), capacity_ * 2);

    // 2) Allocate raw, uninitialized memory
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
        // Rollback: destroy what we did manage to construct, then free
        for (size_type j = 0; j < i; ++j) {
            new_array[j].~T();
        }
        ::operator delete[](new_array);
        throw;
    }

    // 4) All moves succeeded → destroy old objects
    for (size_type j = 0; j < size_; ++j) {
        array[j].~T();
    }

    // 5) Free old buffer and commit the new one
    ::operator delete[](array);
    array     = new_array;
    capacity_ = newCap;
}
