// Vector.h
#pragma once

template<typename T>
class Vector {
    private:
        T*      array     = nullptr;
        size_t  size_     = 0;
        size_t  capacity_ = 0;

    public:
    using size_type = std::size_t;

    using reference       = T&;
    using const_reference = const T&;

    // iterator types
    using iterator       = T*;
    using const_iterator = const T*;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;


    void double_the_capacity();

// ----- rule-of-five
    // ---- Copy constructor
    Vector(const Vector& other)
      : array(other.size_ ? new T[other.size_] : nullptr),
        size_(other.size_),
        capacity_(other.capacity_)
    {
        for (size_t i = 0; i < size_; ++i) {
            array[i] = other.array[i];
        }
    }

    // ---- Move constructor
    Vector(Vector&& other)  noexcept
      : array(other.array),
        size_(other.size_),
        capacity_(other.capacity_)
    {
        other.array    = nullptr;
        other.size_    = 0;
        other.capacity_= 0;
    }

    // ---- Copy assignment operator
    Vector& operator=(const Vector& other) {
        if (this != &other) {

            T* new_array = other.capacity_ ? new T[other.capacity_] : nullptr;
            for (size_t i = 0; i < other.size_; ++i) {
                new_array[i] = other.array[i];
            }
            delete [] array;

            array     = new_array;
            size_     = other.size_;
            capacity_ = other.capacity_;
        }
        return *this;
    }

     // ---- Move assignment operator
     Vector& operator=(Vector&& other) noexcept {
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

// ----- Element access
    // ----- at()
    constexpr reference at(size_type pos);
    constexpr const_reference at(size_type pos) const;

    // ----- operator[]
    T& operator[](size_type idx) { return array[idx]; }
    const T& operator[](size_type idx) const { return array[idx]; }

    // ----- front()
    constexpr reference front();
    constexpr const_reference front() const;

    // ----- back()
    constexpr reference back();
    constexpr const_reference back() const;

    // ----- data()  <---- ???
    constexpr T* data() noexcept { return array;}
    constexpr const T* data() const noexcept { return array; }

// ----- iterators
    constexpr iterator begin() noexcept { return array; }
    constexpr const_iterator begin() const noexcept { return array; }
    constexpr const_iterator cbegin() const noexcept { return array; }

    constexpr iterator end() noexcept { return array + size_; }
    constexpr const_iterator end() const noexcept { return array + size_; }
    constexpr const_iterator cend() const noexcept { return array + size_; }

    // --- reverse
    constexpr reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
    constexpr const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }
    constexpr const_reverse_iterator crbegin() const noexcept {return const_reverse_iterator(end()); }
    
    constexpr reverse_iterator rend() noexcept { return reverse_iterator(begin()); }
    constexpr const_reverse_iterator rend()   const noexcept { return const_reverse_iterator(begin()); }
    constexpr const_reverse_iterator crend()   const noexcept { return const_reverse_iterator(begin()); }

// ------------------------------------ Capacity ------------------------------
    // in "vector_capacity.h"
    // ---- empty() ----
    constexpr bool empty() const noexcept;

    // ----- size() ----
    constexpr size_type size() const noexcept;

    // ----- max_size() ----
    constexpr size_type max_size() const noexcept;

    // ----- reserve() ----
    constexpr void reserve(size_type new_cap);

    // ----- capacity() ----
    constexpr size_type capacity() const noexcept;

    // ----- shrink_to_fit() ----
    constexpr void shrink_to_fit();

// ------------------------------------ Modifiers ------------------------------
    // in "vector_modifiers.h"

    // ---- clear() ----
    constexpr void clear() noexcept;

    // ---- insert() ----
    constexpr iterator insert(const_iterator pos, const T& value);
    constexpr iterator insert(const_iterator pos, T&& value);  
    constexpr iterator insert(const_iterator pos, size_type count, const T& value);
    template<class InputIt>
    constexpr iterator insert(const_iterator pos, InputIt first, InputIt last);
    constexpr iterator insert(const_iterator pos, std::initializer_list<T> ilist); // <---- raketu mokslas

    // ---- insert_range() ---- c++ 23
    // ---- emplace() ----
    template< class... Args >
    iterator emplace(const_iterator pos, Args&&... args);

    // ---- erase() ----
    iterator erase(iterator pos);
    iterator erase(const_iterator pos);
    iterator erase(iterator first, iterator last);
    iterator erase(const_iterator first, const_iterator last);

    // ---- push_back() ----
    void push_back(const T& value);
    void push_back( T&& value );

    // ---- emplace_back() ----
    template< class... Args >
    reference emplace_back( Args&&... args );

    // ---- append_range() ----  c++ 23
    // ---- pop_back() ----
    void pop_back();
    
    // ---- resize() ----
    void resize(size_type count);
    void resize(size_type count, const T& value );

    // ---- swap() ----
    void swap( Vector& other ) noexcept;
// ----------------------------------------------------------------------------

    // Default Constructor
    Vector() : array(nullptr), size_(0), capacity_(0)
        {}

    // Vector<int> v2(5, 42);    // size() == 5, capacity() == 5
    // prints: 42 42 42 42 42 
    Vector(size_type count, const T& value = T())
    : array(new T[count]), size_(count), capacity_(count)
    {
        for (size_type i = 0; i < count; ++i)
        array[i] = value;
    }


    template<
    typename InputIt,
    typename = std::enable_if_t<!std::is_integral<InputIt>::value>
    >
    Vector(InputIt first, InputIt last)
        : array(nullptr), size_(0), capacity_(0)
    {
        size_type count = static_cast<size_type>(last - first);
        reserve(count);
        for (size_type i = 0; i < count; ++i)
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
    
};

#include "Vector_impl.h"
#include "vector_modifiers.h"
#include "vector_capacity.h"
#include "vector_elementAccess.h"