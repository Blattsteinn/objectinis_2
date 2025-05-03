// vector_impl.h
#pragma once

#include "vector.h"

   // CAPACITY FUNCTIONS
    template<typename T>    
    void Vector<T>::double_the_capacity(){
        size_type oldCap = capacity_;
        size_type newCap = (oldCap == 0 ? 1 : oldCap * 2);          // 2) 1 if you zero, otherwise 2×
        
        // allocates a new array
        T* newArray = new T[newCap];
        
        // copies everything
        for(size_type i = 0; i < capacity_; i++){
            newArray[i] = array[i];
        }

        delete[] array;
        array = newArray;
        capacity_ = newCap;
    }