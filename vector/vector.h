// Vector.h
#pragma once

template<typename T>
class Vector {
    private:
        T*      array     = nullptr;
        size_t  size_     = 0;
        size_t  capacity_ = 0;

    public:

    // iterator types
    using iterator       = T*;
    using const_iterator = const T*;

    // iterator access
    iterator       begin()       noexcept { return array; }
    iterator       end()         noexcept { return array + size_; }
    const_iterator begin() const noexcept { return array; }
    const_iterator end()   const noexcept { return array + size_; }

    void double_the_capacity();
    void reserve(size_t n);

    // Modifiers
    void push_back(T element);
    void clear();
    void pop_back();

    void resize(size_t count);
    void resize(size_t count, const T& value );

    void insert(const_iterator pos, const T& value);
    void insert(const_iterator pos, T&& value);  // <---- raketu mokslas



    // Default Constructor
    Vector() : array(nullptr), size_(0), capacity_(0)
        {}

    // Vector<int> v2(5, 42);    // size() == 5, capacity() == 5
    // prints: 42 42 42 42 42 
    Vector(size_t count, const T& value = T())
    : array(new T[count]), size_(count), capacity_(count)
    {
        for (size_t i = 0; i < count; ++i)
        array[i] = value;
    }

    // int data[] = { 10, 20, 30, 40};
    // Vector<int> v3(std::begin(data), std::end(data));
    // prints: 10 20 30 40 
    template<
    typename InputIt,
    typename = std::enable_if_t<!std::is_integral<InputIt>::value>
    >
    Vector(InputIt first, InputIt last)
        : array(nullptr), size_(0), capacity_(0)
    {
        size_t count = static_cast<size_t>(last - first);
        reserve(count);
        for (size_t i = 0; i < count; ++i)
        array[i] = first[i];
        size_ = count;
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
    
    // Accessors
    size_t size() const noexcept      { return size_; }
    size_t capacity() const noexcept  { return capacity_; }
    T& operator[](size_t idx)         { return array[idx]; }
    const T& operator[](size_t idx) const { return array[idx]; }
};

#include "Vector_impl.h"