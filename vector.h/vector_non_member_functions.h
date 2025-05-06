// vector_non_member_functions.h
#pragma once

#include "vector_library.h"

template <typename T>
bool Vector<T>::operator==(const Vector& other) const {
    if (size_ != other.size_) return false;

    return std::equal(begin(), end(), 
              other.begin(), other.end());
 }

template <typename T>
bool Vector<T>::operator!=(const Vector& other) const {
    return !(other == *this);
 }

template <typename T>
bool Vector<T>::operator>(const Vector& other) const {
    // true if the first range is lexicographically less than the second, otherwise false.  
    // Note: always uses < (so it's -  other < this)
   return std::lexicographical_compare(other.begin(), other.end(),   // first range  (other)
                                       begin(), end());              // second range (*this)
 }

template <typename T>
bool Vector<T>::operator>=(const Vector& other) const {
    return !std::lexicographical_compare(begin(),      end(),
                                         other.begin(), other.end()
    );
}

template <typename T>
bool Vector<T>::operator<(const Vector& other) const {
   return std::lexicographical_compare(begin(), end(), 
                                       other.begin(), other.end());
 }

template <typename T>
bool Vector<T>::operator<=(const Vector& other) const {
    return !std::lexicographical_compare(other.begin(), other.end(),
                                         begin(), end());
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& vec) {
    os << '[';
    for (typename Vector<T>::size_type i = 0; i < vec.size(); ++i) {
        os << vec[i];
        if (i + 1 < vec.size())
            os << ", ";
    }
    os << ']';
    return os;
}