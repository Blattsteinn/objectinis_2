// Vector_impl.h
#pragma once

#include "vector.h"

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

    template<typename T>
    void Vector<T>::push_back(T element){
        if(size_ >= capacity_){
            Vector::double_the_capacity();
        }
        array[size_] = element;
        ++size_;

    }