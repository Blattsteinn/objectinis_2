// vector_memberFunctions.h
#pragma once

#include "vector.h"

template<typename T>
void Vector<T>::assign(size_type count, const T& value){

    T* new_array = count ? new T[count] : nullptr;

    try {
        // if this throws, catch below
        for (size_type i = 0; i < count; ++i) {
            new_array[i] = value;
        }
    } catch (...) {
        delete[] new_array;
        throw;
    }

    delete[] array;
    array     = new_array;
    size_     = count;
    capacity_ = count;
}

template<typename T>
template<typename InputIt, typename>
void Vector<T>::assign(InputIt first, InputIt last){
    auto count = last - first;

    T* new_array = count ? new T[count] : nullptr;

    try {
        for(size_type i = 0; first != last; ++first, ++i){
            new_array[i] = *first;
        }

    } catch (...) {
        delete[] new_array;
        throw;
    }


    delete[] array;
    array     = new_array;
    size_     = count;
    capacity_ = count;
}

template<typename T>
void Vector<T>::assign(std::initializer_list<T> ilist){
    assign(ilist.begin(), ilist.end());
}

// ---- Copy constructor
template<typename T>
Vector<T>::Vector(const Vector<T>& other)
    : array(other.capacity_ ? new T[other.capacity_] : nullptr),
    size_(other.size_),
    capacity_(other.capacity_)
    {
        for (size_t i = 0; i < size_; ++i) {
            array[i] = other.array[i];
        }
    }


// --- initializer_list
template<typename T>
Vector<T>::Vector(std::initializer_list<T> ilist)
        : array(ilist.size() ? new T[ilist.size()] : nullptr),
        size_(ilist.size()),
        capacity_(ilist.size())
    {
        auto pos = ilist.begin();
        for (size_t i = 0; pos < ilist.end(); ++i, ++pos) {
            array[i] = *pos;
        }
    }
    
template<typename T>
Vector<T>& Vector<T>::operator=(std::initializer_list<T> ilist){
    array = ilist.size() ? new T[ilist.size()] : nullptr;
    size_ = ilist.size();
    capacity_ = ilist.size();

    auto pos = ilist.begin();
    for (size_t i = 0; pos < ilist.end(); ++i, ++pos) {
        array[i] = *pos;
    }

    return *this;
}

// ---- Move constructor
template<typename T>
Vector<T>::Vector(Vector<T>&& other) noexcept
    : array(other.array),
    size_(other.size_),
    capacity_(other.capacity_)
    {
        other.array    = nullptr;
        other.size_    = 0;
        other.capacity_= 0;
    }

// ---- Copy assignment operator
template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other) {
    if (this != &other) {

        T* new_array = other.capacity_ ? new T[other.capacity_] : nullptr;

    try {    
        for (size_t i = 0; i < other.size_; ++i) {
            new_array[i] = other.array[i];
            }
    } catch (...) {
        delete[] new_array;
        throw;
    }
    
        delete [] array;
        array     = new_array;
        size_     = other.size_;
        capacity_ = other.capacity_;
    }

        return *this;
}

// ---- Move assignment operator
template<typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& other) noexcept {
    if(&other != this){
        delete[] array;
        array = other.array;
        size_ = other.size_;
        capacity_ = other.capacity_;

        other.array    = nullptr;
        other.size_    = 0;
        other.capacity_= 0;
        }
        return *this;
     }
