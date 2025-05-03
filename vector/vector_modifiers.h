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
// inserts one element
template <typename T>
void Vector<T>::insert(const_iterator pos, const T &value)
{

    size_type idx = pos - begin();

    while (size_ + 1 > capacity_)
    {
        double_the_capacity();
    }

    for (size_type i = size_; i > idx; --i)
    {
        array[i] = std::move(array[i - 1]);
    }
    array[idx] = value;
    ++size_;
}

template <typename T>
void Vector<T>::insert(const_iterator pos, T &&value)
{
    size_type idx = pos - begin();

    while (size_ + 1 > capacity_)
    {
        double_the_capacity();
    }

    for (size_type i = size_; i > idx; --i)
    {
        array[i] = std::move(array[i - 1]);
    }
    array[idx] = std::forward<T>(value);
    ++size_;
}

template <typename T>
void Vector<T>::insert(const_iterator pos, size_type count, const T &value)
{
    size_type idx = pos - begin();

    while (size_ + count > capacity_)
    {
        double_the_capacity();
    }

    for (size_type i = size_; i > idx; --i)
    {
        array[i - 1 + count] = std::move(array[i - 1]);
    }

    for (size_type j = 0; j < count; ++j)
    {
        array[idx + j] = value;
    }

    size_ += count;
}

template <typename T>
void Vector<T>::insert(const_iterator pos, std::initializer_list<T> ilist)
{
    size_type idx = pos - begin();
    size_type count = ilist.end() - ilist.begin();

    while (size_ + count > capacity_)
    {
        double_the_capacity();
    }

    for (size_type i = size_; i > idx; --i)
    {
        array[i - 1 + count] = std::move(array[i - 1]);
    }

    const T *ptr = ilist.begin();
    for (size_type j = 0; j < ilist.size(); ++j)
    {
        array[idx + j] = ptr[j]; // copy the j-th element
    }

    size_ += count;
}

// insert_range (C++23)
//   Inserts a range of elements [first, last) at a given position.
//   (public member function)

// emplace (C++11)
//   Constructs an element in-place at a given position.
//   (public member function)

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
void Vector<T>::push_back(const T &value)
{
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

// append_range (C++23)
//   Appends a range of elements [first, last) to the end of the vector.
//   (public member function)

// pop_back
//   Removes the last element from the vector.
//   (public member function)
template <typename T>
void Vector<T>::pop_back()
{
    array[size_].~T();
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
void Vector<T>::swap(Vector &other) noexcept
{
    std::swap(array, other.array);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
}