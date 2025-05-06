// vector_memberFunctions.h
#pragma once

#include "vector_library.h"

template<typename T>
void Vector<T>::assign(size_type count, const T& value){

    T* new_array = static_cast<T*>(
        ::operator new[](count * sizeof(T))
    );

    size_type constructed = 0;
    try {
        for (; constructed < count; ++constructed) {
            new (&new_array[constructed]) T(value);
        }
    } catch (...) {
        // If fails destroys what we did, then frees the memory
        for (size_type j = 0; j < constructed; ++j)
            new_array[j].~T();
        ::operator delete[](new_array);
        throw;
    }

    for (size_type j = 0; j < size_; ++j) {
        array[j].~T();
    }
    ::operator delete[](array);

    array     = new_array;
    size_     = count;
    capacity_ = count;
}

template<typename T>
template<typename InputIt, typename>
void Vector<T>::assign(InputIt first, InputIt last){
    for (size_type i = 0; i < size_; ++i)
    array[i].~T();

    size_ = 0;
    for (; first != last; ++first)
        push_back(*first);
}

template<typename T>
void Vector<T>::assign(std::initializer_list<T> ilist){
    assign(ilist.begin(), ilist.end());
}

// ---- Copy constructor
template<typename T>
Vector<T>::Vector(const Vector<T>& other)
    : array(other.capacity_ 
            ? static_cast<T*>(::operator new[](other.capacity_ * sizeof(T)))
            : nullptr),
      size_(other.size_),
      capacity_(other.capacity_)
{
    size_type i = 0;
    try {
        for (; i < other.size_; ++i) {
            new (&array[i]) T(other.array[i]);
        }
    } catch (...) {
        // If fails destroys what we did, then frees the memory
        for (size_type j = 0; j < i; ++j) {
            array[j].~T();
        }
        ::operator delete[](array);
        throw;
    }
}


// --- initializer_list
template<typename T>
Vector<T>::Vector(std::initializer_list<T> ilist)
  : array(ilist.size()
            ? static_cast<T*>(::operator new[](ilist.size() * sizeof(T)))
            : nullptr),
    size_(0),
    capacity_(ilist.size())
{
    for (auto const &elem : ilist) {
        push_back(elem);}
}
    
template<typename T>
Vector<T>& Vector<T>::operator=(std::initializer_list<T> ilist){
    assign(ilist);
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
        Vector tmp(other);
        swap(tmp);
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
