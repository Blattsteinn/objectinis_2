// vector_modifiers.h
#pragma once

#include "vector_library.h"

// --------------------  MODIFIERS  --------------------
// clear
//   Clears all elements from the vector.
//   (public member function)
template <typename T>
void Vector<T>::clear() noexcept
{
    for (size_type i = 0; i < size_; ++i)
    {
        array[i].~T();
    }
    size_ = 0;
}

// insert
//   Inserts one or more elements at a given position.
//   (public member function)

// 1) Inserts a copy of value before pos.
template <typename T>
typename Vector<T>::iterator Vector<T>::insert(const_iterator pos, const T &value){

    size_type idx = pos - begin();

    // Make a copy incase it throws
    Vector tmp(*this);

    while (tmp.size_ + 1 > tmp.capacity_) {
        tmp.double_the_capacity();
    }
    
    for (size_type i = tmp.size_; i > idx; --i) {
        new (&tmp.array[i]) T(std::move(tmp.array[i-1]));
        tmp.array[i-1].~T();
    }

    new (&tmp.array[idx]) T(value);
    ++tmp.size_;

    // if everything is OK
    swap(tmp);

    return array + idx;
}

// 2) Inserts value before pos, using move
template <typename T>
typename Vector<T>::iterator Vector<T>::insert(const_iterator pos, T &&value){
    size_type idx = pos - begin();

    // Make a copy incase it throws
    Vector tmp(*this);

    while (tmp.size_ + 1 > tmp.capacity_) {
        tmp.double_the_capacity();
    }

    for (size_type i = tmp.size_; i > idx; --i) {
        new (&tmp.array[i]) T(std::move(tmp.array[i - 1]));
        tmp.array[i - 1].~T();
    }

    new (&tmp.array[idx]) T(value);
    ++tmp.size_;

    // if everything is OK
    swap(tmp);

    return array + idx;
}

// 3) Inserts count copies of the value before pos.
template <typename T>
typename Vector<T>::iterator Vector<T>::insert(const_iterator pos, size_type count, const T &value){
    
    size_type idx = pos - begin();
    Vector tmp;                 // start fresh, not a copy
    tmp.reserve(size_ + count);
    
    // 1) copy elements [0, idx)
    for (size_type i = 0; i < idx; ++i) {
        tmp.push_back(std::move_if_noexcept(array[i]));
    }
        
    for (size_type i = 0; i < count; ++i){
        tmp.push_back(value);
    }
        
    for (size_type i = idx; i < size_; ++i){
        tmp.push_back(std::move_if_noexcept(array[i]));
    }

    // if everything is OK
    swap(tmp);

    return begin() + idx;
}

// 4) Inserts elements from range [first, last) before pos.
template<typename T>
template<class InputIt, typename> 
typename Vector<T>::iterator Vector<T>::insert(const_iterator pos, InputIt first, InputIt last){
    size_type idx   = pos - begin();
    size_type count = static_cast<size_type>(std::distance(first, last));

    if (count == 0)
        return const_cast<iterator>(pos);

    Vector tmp;
    tmp.reserve(size_ + count);

    for (size_type i = 0; i < idx; ++i)
        tmp.push_back(std::move_if_noexcept(array[i]));

    for (; first != last; ++first)
        tmp.push_back(*first);

    for (size_type i = idx; i < size_; ++i)
        tmp.push_back(std::move_if_noexcept(array[i]));

    swap(tmp);
    return begin() + idx;
}

// 5) Inserts elements from initializer list ilist before pos.
// Equivalent to insert(pos, ilist.begin(), ilist.end()).
template <typename T>
typename Vector<T>::iterator Vector<T>::insert(const_iterator pos, std::initializer_list<T> ilist){
   
    size_type idx = pos - begin();
    Vector tmp;
    tmp.reserve(size_ + ilist.size());

    for (size_type i = 0; i < idx; ++i)
        tmp.push_back(std::move_if_noexcept(array[i]));
    for (auto &x : ilist)
        tmp.push_back(x);
    for (size_type i = idx; i < size_; ++i)
        tmp.push_back(std::move_if_noexcept(array[i]));

    swap(tmp);
    return begin() + idx;
}

// emplace (C++11)
//   Constructs an element in-place at a given position.
//   (public member function)

template<typename T>
template< class... Args >
typename Vector<T>::iterator Vector<T>::emplace(const_iterator pos, Args&&... args){

    size_type idx = pos - begin();

    if (size_ + 1 > capacity_){
    double_the_capacity();
    }

    for (size_type i = size_; i > idx; --i){
        array[i] = std::move(array[i - 1]);
    }

    // 4) construct the new T in-place
    new (&array[idx]) T(std::forward<Args>(args)...);

    ++size_;
    return array + idx;
}

// erase
//   Removes the element at a given position (or a range of elements).
//   (public member function)

// singles --->
template <typename T>
typename Vector<T>::iterator
Vector<T>::erase(iterator pos)
{
    size_type idx = pos - begin();

    if (idx == size_ - 1)
    {
        pop_back();
        return end();
    }

    // Move everything backwards
    for (size_type i = idx; i + 1 < size_; ++i)
    {
        array[i] = std::move(array[i + 1]);
    }

    pop_back();

    return begin() + idx;
}

template <typename T>
typename Vector<T>::iterator
Vector<T>::erase(const_iterator pos)
{
    size_type idx = pos - begin();

    if (idx == size_ - 1)
    {
        pop_back();
        return end();
    }

    // Move everything backwards
    for (size_type i = idx; i + 1 < size_; ++i)
    {
        array[i] = std::move(array[i + 1]);
    }

    pop_back();

    return begin() + idx;
}

// ranges --->
template <typename T>
typename Vector<T>::iterator
Vector<T>::erase(iterator first, iterator last)
{
    size_type count = last - first;
    size_type idx = first - begin();

    // Do nothing
    if (count == 0)
    {
        return end();
    }

    // Shifting elements to the left
    for (size_type i = idx; i + count < size_; ++i)
    {
        array[i] = std::move(array[i + count]);
    }

    // Destroying elements
    for (size_type d = 0; d < count; ++d)
    {
        array[--size_].~T();
    }

    return begin() + idx;
}

template <typename T>
typename Vector<T>::iterator
Vector<T>::erase(const_iterator first, const_iterator last)
{
    size_type count = last - first;
    size_type idx = first - begin();

    // Do nothing
    if (count == 0)
    {
        return end();
    }

    // Shifting elements to the left
    for (size_type i = idx; i + count < size_; ++i)
    {
        array[i] = std::move(array[i + count]);
    }

    // Destroying elements
    for (size_type d = 0; d < count; ++d)
    {
        array[--size_].~T();
    }

    return begin() + idx;
}

// push_back
//   Appends a copy of the given element to the end of the vector.
//   (public member function)
template <typename T>
void Vector<T>::push_back(const T &value){
    if (size_ == capacity_){
        Vector::double_the_capacity();
    }
    new (&array[size_]) T(value);           // construct from const T&
    ++size_;
}

template <typename T>
void Vector<T>::push_back(T &&value)
{
    if (size_ == capacity_){
        Vector::double_the_capacity();
    }
    new (&array[size_]) T(std::move(value)); // construct from T&&
    ++size_;
}

// emplace_back (C++11)
//   Constructs an element in-place at the end of the vector.
//   (public member function)
template<typename T>
template< class... Args >
typename Vector<T>::reference Vector<T>::emplace_back(Args&&... args){
    auto it = emplace(end(), std::forward<Args>(args)...);
    return *it;
}

// pop_back
//   Removes the last element from the vector.
//   (public member function)
template <typename T>
void Vector<T>::pop_back(){
    array[size_ - 1].~T();
    --size_;
}

// resize
//   Changes the number of elements stored in the vector.
//   If new size > old size, value-initializes new elements.
//   If new size < old size, erases excess elements.
//   (public member function)
template <typename T>
void Vector<T>::resize(size_type count)
{
    if (count == size_)
    {
        return;
    }

    else if (size_ > count)
    {
        for (size_type i = count; i < size_; ++i)
        {
            array[i].~T();
        }
        size_ = count;
        return;
    }

    else
    {
        reserve(count);
        for (size_type i = size_; i < count; ++i)
        {
            new (&array[i]) T();
        }
        size_ = count;
        return;
    }
};

template <typename T>
void Vector<T>::resize(size_type count, const T &value)
{
    if (count == size_)
    {
        return;
    }

    else if (size_ > count)
    {
        for (size_type i = count; i < size_; ++i)
        {
            array[i].~T();
        }
        size_ = count;
        return;
    }

    else
    {
        reserve(count);
        for (size_type i = size_; i < count; ++i)
        {
            new (&array[i]) T(value);
        }
        size_ = count;
        return;
    }
};

// swap
//   Exchanges the contents of this vector with another.
//   (public member function)
template <typename T>
void Vector<T>::swap(Vector &other) noexcept{
    std::swap(array, other.array);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
}