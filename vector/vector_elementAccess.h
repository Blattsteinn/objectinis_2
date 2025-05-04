// vector_elementAccess.h
#pragma once

#include "vector.h"

// ----- at()
template<typename T>
constexpr typename Vector<T>::reference Vector<T>::at(size_type pos){
    if (pos >= size_) {
        throw std::out_of_range("Vector::at: index out of range");
    }
    return array[pos];
}

template<typename T>
constexpr typename Vector<T>::const_reference Vector<T>::at(size_type pos) const{
    if (pos >= size_) {
        throw std::out_of_range("Vector::at: index out of range");
    }
    return array[pos];
}

// ----- front()
template<typename T>
constexpr typename Vector<T>::reference Vector<T>::front(){
    if (empty()) {
        throw std::out_of_range("Vector::front(): empty vector");
    }
    return *begin();
}

template<typename T>
constexpr typename Vector<T>::const_reference Vector<T>::front() const{
    if (empty()) {
        throw std::out_of_range("Vector::front(): empty vector");
    }
    return *begin();
}

// ----- back()
template<typename T>
constexpr typename Vector<T>::reference Vector<T>::back(){
    if (empty()) {
        throw std::out_of_range("Vector::back(): empty vector");
    }
    return *(end()-1);
}

template<typename T>
constexpr typename Vector<T>::const_reference Vector<T>::back() const{
    if (empty()) {
        throw std::out_of_range("Vector::front(): empty vector");
    }
    return *(end()-1);
}
