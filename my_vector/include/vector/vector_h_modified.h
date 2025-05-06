// Vector.h
#pragma once

#include "vector_library.h"

template<typename T>
class Vector {
    private:
        T*      array     = nullptr;
        size_t  size_     = 0;
        size_t  capacity_ = 0;

        void double_the_capacity();
        
    public:
    using size_type = std::size_t;

    using reference       = T&;
    using const_reference = const T&;

    // iterator types
    using iterator               = T*;
    using const_iterator = const T*;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

// ----- Constructors
    Vector() : array(nullptr), size_(0), capacity_(0) {}

    Vector(size_type count, const T& value = T()): array(nullptr), size_(0), capacity_(0){
        assign(count, value);
    }

    template<typename InputIt, typename = std::enable_if_t<!std::is_integral<InputIt>::value>>
    Vector(InputIt first, InputIt last) : array(nullptr), size_(0), capacity_(0){  
        for (; first != last; ++first) {
            push_back(*first);
        }
    }

 // ----- Destructor
    ~Vector() { 
        for (size_type i = 0; i < size_; ++i){
            array[i].~T();
        }
    ::operator delete[](array);
}  

// ----- Member functions in "vector_memberFunctions.h"

    // ---- Copy constructor
    Vector(const Vector& other);
    // ---- Move constructor
    Vector(Vector&& other)  noexcept;

    // -- initializer_list
    Vector(std::initializer_list<T> ilist);
    Vector& operator=(std::initializer_list<T> ilist);

    // ---- Copy assignment operator
    Vector& operator=(const Vector& other);

    // ---- Move assignment operator
    Vector& operator=(Vector&& other) noexcept;

     // ---- assign
    void assign(size_type count, const T& value);
    template<class InputIt, typename = std::enable_if_t<!std::is_integral<InputIt>::value>>
    void assign(InputIt first, InputIt last);
    void assign(std::initializer_list<T> ilist);

// ----- Non-member functions 
    bool operator==(const Vector& other) const; //!< Equality.
    bool operator!=(const Vector& other) const; //!< Inequality.
    bool operator< (const Vector& other) const; //!< Lexicographical less‑than.
    bool operator<=(const Vector& other) const; //!< !(@p other < *this).
    bool operator> (const Vector& other) const; //!< @p other < *this.
    bool operator>=(const Vector& other) const; //!< !(*this < @p other).

// ----- Element access in "vector_elementAccess.h"

    // ----- at()
    reference at(size_type pos);
    const_reference at(size_type pos) const;

    // ----- operator[]
    T& operator[](size_type idx) { return array[idx]; }
    const T& operator[](size_type idx) const { return array[idx]; }

    // ----- front()
    reference front();
    const_reference front() const;

    // ----- back()
    reference back();
    const_reference back() const;

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

// ----- Capacity, in "vector_capacity.h"

    // ---- empty() ----
    constexpr bool empty() const noexcept;

    // ----- size() ----
    constexpr size_type size() const noexcept;

    // ----- max_size() ----
    constexpr size_type max_size() const noexcept;

    // ----- reserve() ----
    void reserve(size_type new_cap);

    // ----- capacity() ----
    constexpr size_type capacity() const noexcept;

    // ----- shrink_to_fit() ----
    void shrink_to_fit();

// ----- Modifiers, in "vector_modifiers.h"

    // ---- clear() ----
    void clear() noexcept;

    // ---- insert() ----
    iterator insert(const_iterator pos, const T& value);
    iterator insert(const_iterator pos, T&& value);  
    iterator insert(const_iterator pos, size_type count, const T& value);
    template<class InputIt, typename = std::enable_if_t<!std::is_integral<InputIt>::value>>
    iterator insert(const_iterator pos, InputIt first, InputIt last);
    iterator insert(const_iterator pos, std::initializer_list<T> ilist);

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

    // ---- pop_back() ----
    void pop_back();
    
    // ---- resize() ----
    void resize(size_type count);
    void resize(size_type count, const T& value );

    // ---- swap() ----
    void swap( Vector& other ) noexcept;
// ----------------------------------------------------------------------------
   
};

#include "Vector_impl.h"
#include "vector_modifiers.h"
#include "vector_capacity.h"
#include "vector_elementAccess.h"
#include "vector_memberFunctions.h"

// Missing functions:

// 1) insert_range()  C++ 23
// 2) append_range()  C++ 23