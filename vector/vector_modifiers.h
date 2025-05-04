// vector_modifiers.h
#pragma once

#include "vector.h"

// --------------------  MODIFIERS  --------------------
// clear
//   Clears all elements from the vector.
//   (public member function)
template <typename T>
constexpr void Vector<T>::clear() noexcept
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
        tmp.array[i] = std::move(tmp.array[i - 1]);
    }

    tmp.array[idx] = value;
    ++tmp.size_;

    // if everything is OK
    swap(tmp);

    return array + idx;
}

// 2) Inserts value before pos, possibly using move semantics.
template <typename T>
typename Vector<T>::iterator Vector<T>::insert(const_iterator pos, T &&value){
    size_type idx = pos - begin();

    // Make a copy incase it throws
    Vector tmp(*this);

    while (tmp.size_ + 1 > tmp.capacity_) {
        tmp.double_the_capacity();
    }

    for (size_type i = tmp.size_; i > idx; --i) {
        tmp.array[i] = std::move(tmp.array[i - 1]);
    }

    tmp.array[idx] = std::move(value);
    ++tmp.size_;

    // if everything is OK
    swap(tmp);

    return array + idx;
}

// 3) Inserts count copies of the value before pos.
template <typename T>
typename Vector<T>::iterator Vector<T>::insert(const_iterator pos, size_type count, const T &value){
    size_type idx = pos - begin();

    // Make a copy incase it throws
    Vector tmp(*this);
    
    while (tmp.size_ + count > tmp.capacity_) {
        tmp.double_the_capacity();
    }

    // Move forward 'count' times
    for (size_type i = tmp.size_; i > idx; --i) {
        tmp.array[i - 1 + count] = std::move(tmp.array[i - 1]);
    }

    for (size_type j = 0; j < count; ++j){
        tmp.array[idx + j] = value;
    }

    tmp.size_ += count;

    // if everything is OK
    swap(tmp);

    return array + idx;
}

// 4) Inserts elements from range [first, last) before pos.
template<typename T>
template<class InputIt, typename> 
typename Vector<T>::iterator Vector<T>::insert(const_iterator pos, InputIt first, InputIt last){
    size_type idx = pos - begin();
    size_type count = last - first;

    if (count == 0)
    return const_cast<iterator>(pos);

    // Make a copy incase it throws
    Vector tmp(*this);

    while (tmp.size_ + count > tmp.capacity_) {
        tmp.double_the_capacity();
    }

    // Move forward 'count' times
    for (size_type i = tmp.size_; i > idx; --i){
        tmp.array[i - 1 + count] = std::move(tmp.array[i - 1]);
    }
    // Add new elements
    size_type j = 0;
    for (auto i = first; i != last; ++i, ++j){
        tmp.array[idx + j] = *i;
    }

    tmp.size_ += count;
    // if everything is OK
    swap(tmp);

    return array + idx;
}

// 5) Inserts elements from initializer list ilist before pos.
// Equivalent to insert(pos, ilist.begin(), ilist.end()).
template <typename T>
typename Vector<T>::iterator Vector<T>::insert(const_iterator pos, std::initializer_list<T> ilist){
    size_type idx = pos - begin();
    size_type count = ilist.size();

    if (count == 0)
    return const_cast<iterator>(pos);

    // Make a copy incase it throws
    Vector tmp(*this);

    while (tmp.size_ + count > tmp.capacity_){
        tmp.double_the_capacity();
    }

    for (size_type i = tmp.size_; i > idx; --i){
        tmp.array[i - 1 + count] = std::move(tmp.array[i - 1]);
    }

    const T *ptr = ilist.begin();
    for (size_type j = 0; j < ilist.size(); ++j){
        tmp.array[idx + j] = ptr[j]; // copy the j-th element
    }

    tmp.size_ += count;

    // if everything is OK
    swap(tmp);

    return array + idx;
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
    if (size_ == capacity_)
    {
        Vector::double_the_capacity();
    }
    array[size_] = value;
    ++size_;
}

template <typename T>
void Vector<T>::push_back(T &&value)
{
    if (size_ == capacity_)
    {
        Vector::double_the_capacity();
    }
    array[size_] = std::move(value);
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