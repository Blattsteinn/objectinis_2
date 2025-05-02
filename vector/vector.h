// Vector.h
#pragma once

template<typename T>
class Vector {
    private:
        T*      array     = nullptr;
        size_t  size_     = 0;
        size_t  capacity_ = 0;


    public:

    // Default Constructor
    Vector() : array(nullptr), size_(0), capacity_(0)
        {}

    // Parameterized constructor: deep copy from external buffer
    Vector(const T* src, size_t size, size_t capacity)
      : array(new T[capacity]), size_(size), capacity_(capacity)
    {
        for (size_t i = 0; i < size_; ++i)
            array[i] = src[i];
    }

    // Destructor
    ~Vector() {
        delete[] array;
        }    

    // (implement Rule of Five)
    // Vector(const Vector&) = delete;
    // Vector& operator=(const Vector&) = delete;
    // Vector(Vector&&) noexcept = delete;
    // Vector& operator=(Vector&&) noexcept = delete;
    
    void double_the_capacity(){
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

    void reserve(size_t n);

    void push_back(T element);

    // Accessors
    size_t size() const noexcept      { return size_; }
    size_t capacity() const noexcept  { return capacity_; }
    T& operator[](size_t idx)         { return array[idx]; }
    const T& operator[](size_t idx) const { return array[idx]; }
};

#include "Vector_impl.h"