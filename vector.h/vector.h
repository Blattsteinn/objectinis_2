// Vector.h
#pragma once

/**
 * @file Vector.h
 * @brief A light‑weight replacement for `std::vector` that allocates with raw
 *        `new`/`delete` instead of an allocator.
 *        overloads.
 *
 * The implementation is distributed across several helper headers included at
 * the bottom of this file:
 *   - @ref Vector_impl.h            — core private helpers (growth, moves)
 *   - @ref vector_memberFunctions.h — constructors/assignments
 *   - @ref vector_elementAccess.h   — element accessors
 *   - @ref vector_capacity.h        — capacity helpers
 *   - @ref vector_modifiers.h       — modifiers
 *
 * @note  This header **does not** depend on allocators; memory is managed with
 *        `::operator new[]` / `::operator delete[]`.
 */

#include "vector_library.h"

/**
 * @class Vector
 * @tparam T Element type stored by the container.
 * @brief  Contiguous grow‑able array owning its storage (similar to
 *         `std::vector`).
 */
template<typename T>
class Vector {
private:
    /** Pointer to the first element (or `nullptr` if empty). */
    T* array = nullptr;
    /** Number of constructed elements. */
    size_t size_ = 0;
    /** Allocated capacity (in elements). */
    size_t capacity_ = 0;

    /**
     * @brief Double the current capacity and reallocate storage.
     *
     * Called internally when an insertion would exceed the current capacity.
     * Relocates existing elements to the new buffer using move‑construction
     * when available, falling back to copy otherwise.
     *
     * @throw std::bad_alloc If memory allocation fails.
     * @complexity Linear in `size()` (element‑wise move/copy).
     */
    void double_the_capacity();

public:
    //-------------------------------------------------------------------------
    // Member types
    //-------------------------------------------------------------------------
    using size_type       = std::size_t; //!< Unsigned size type.
    using reference       = T&;          //!< Mutable reference.
    using const_reference = const T&;    //!< Immutable reference.

    /// @name Iterator types
    ///@{
    using iterator               = T*;  //!< Pointer iterator.
    using const_iterator         = const T*; //!< Immutable pointer iterator.
    using reverse_iterator       = std::reverse_iterator<iterator>;        //!< Reverse iterator.
    using const_reverse_iterator = std::reverse_iterator<const_iterator>; //!< Const reverse iterator.
    ///@}

    //-------------------------------------------------------------------------
    // Constructors / Destructor
    //-------------------------------------------------------------------------

    /**
     * @brief Construct an empty vector.
     *
     * No allocation is performed.
     * @post `size() == 0 && capacity() == 0`.
     */
    Vector() : array(nullptr), size_(0), capacity_(0) {}

    /**
     * @brief Construct `count` copies of `value`.
     *
     * Equivalent to default construction followed by `assign(count, value)`.
     *
     * @param count Number of elements to create.
     * @param value Value to copy into each new element.
     * @complexity O(count).
     */
    Vector(size_type count, const T& value = T())
        : array(nullptr), size_(0), capacity_(0) {
        assign(count, value);
    }

    /**
     * @brief Range constructor.
     *
     * Constructs a vector with the contents of the iterator range
     * `[first, last)`.
     *
     * @tparam InputIt  Non‑integral input iterator type.
     * @param first     Iterator to the first element.
     * @param last      Sentinel past the last element.
     * @complexity O(distance(first, last)).
     */
    template<typename InputIt, typename = std::enable_if_t<!std::is_integral<InputIt>::value>>
    Vector(InputIt first, InputIt last)
        : array(nullptr), size_(0), capacity_(0) {
        for (; first != last; ++first) {
            push_back(*first);
        }
    }

    /**
     * @brief Destroy the vector and its elements.
     *
     * Invokes the destructor on each element in reverse order of construction
     * and releases the allocated buffer.
     * @complexity O(size()).
     */
    ~Vector() {
        for (size_type i = 0; i < size_; ++i) {
            array[i].~T();
        }
        ::operator delete[](array);
    }

    //-------------------------------------------------------------------------
    // Copy / move semantics  (defined in vector_memberFunctions.h)
    //-------------------------------------------------------------------------

    /** @name Copy / move constructors */
    ///@{
    /** @brief Copy constructor. */
    Vector(const Vector& other);
    /** @brief Move constructor (guaranteed nothrow). */
    Vector(Vector&& other) noexcept;
    /** @brief Construct from an initializer list. */
    Vector(std::initializer_list<T> ilist);
    ///@}

    /** @name Assignment operators */
    ///@{
    /** @brief Replace contents with an initializer list. */
    Vector& operator=(std::initializer_list<T> ilist);
    /** @brief Copy assignment. */
    Vector& operator=(const Vector& other);
    /** @brief Move assignment (guaranteed nothrow). */
    Vector& operator=(Vector&& other) noexcept;
    ///@}

    //-------------------------------------------------------------------------
    // assign()
    //-------------------------------------------------------------------------

    /**
     * @brief Replace contents with `count` copies of `value`.
     * @complexity O(count).
     */
    void assign(size_type count, const T& value);

    /**
     * @brief Replace contents with the range `[first,last)`.
     *
     * @tparam InputIt  Non‑integral input iterator.
     * @param first     First element in the range.
     * @param last      Sentinel past the last element.
     * @complexity O(distance(first, last)).
     */
    template<class InputIt, typename = std::enable_if_t<!std::is_integral<InputIt>::value>>
    void assign(InputIt first, InputIt last);

    /**
     * @brief Replace contents with an initializer list.
     */
    void assign(std::initializer_list<T> ilist);

    //-------------------------------------------------------------------------
    // Comparisons
    //-------------------------------------------------------------------------

    /**
     * @brief Equality comparison.
     * @returns `true` if sizes are equal and all elements compare equal.
     * @complexity O(size()).
     */
    bool operator==(const Vector& other) const;

    /** @brief Inequality comparison. */
    bool operator!=(const Vector& other) const;
    /** @brief Lexicographical less‑than. */
    bool operator< (const Vector& other) const;
    /** @brief Less‑than‑or‑equal. */
    bool operator<=(const Vector& other) const;
    /** @brief Greater‑than. */
    bool operator> (const Vector& other) const;
    /** @brief Greater‑than‑or‑equal. */
    bool operator>=(const Vector& other) const;

    //-------------------------------------------------------------------------
    // Element access
    //-------------------------------------------------------------------------

    /**
     * @brief Bounds‑checked element access.
     * @param pos Index of element to return.
     * @throw std::out_of_range If `pos >= size()`.
     */
    reference at(size_type pos);

    /** @copydoc at(size_type) */
    const_reference at(size_type pos) const;

    /** @name Unchecked element access */
    ///@{
    /** @brief Unchecked access (undefined behavior if out of bounds). */
    T& operator[](size_type idx) { return array[idx]; }
    /** @brief Unchecked const access. */
    const T& operator[](size_type idx) const { return array[idx]; }
    ///@}

    /** @brief Access the first element. */
    reference front();
    /** @copydoc front() */
    const_reference front() const;

    /** @brief Access the last element. */
    reference back();
    /** @copydoc back() */
    const_reference back() const;

    /**
     * @brief Direct pointer to the underlying array.
     * @return Pointer to the first element (may be `nullptr` when empty).
     */
    constexpr T* data() noexcept { return array; }

    /** @copydoc data() */
    constexpr const T* data() const noexcept { return array; }

    //-------------------------------------------------------------------------
    // Iterators
    //-------------------------------------------------------------------------

    /** @name Forward iterators */
    ///@{
    /** @brief Iterator to the first element. */
    constexpr iterator begin() noexcept { return array; }
    /** @copydoc begin() */
    constexpr const_iterator begin() const noexcept { return array; }
    /** @brief Const iterator to the first element. */
    constexpr const_iterator cbegin() const noexcept { return array; }

    /** @brief Iterator past the last element. */
    constexpr iterator end() noexcept { return array + size_; }
    /** @copydoc end() */
    constexpr const_iterator end() const noexcept { return array + size_; }
    /** @brief Const iterator past the last element. */
    constexpr const_iterator cend() const noexcept { return array + size_; }
    ///@}

    /** @name Reverse iterators */
    ///@{
    constexpr reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
    constexpr const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }
    constexpr const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(end()); }

    constexpr reverse_iterator rend() noexcept { return reverse_iterator(begin()); }
    constexpr const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }
    constexpr const_reverse_iterator crend() const noexcept { return const_reverse_iterator(begin()); }
    ///@}

    //-------------------------------------------------------------------------
    // Capacity
    //-------------------------------------------------------------------------

    /** @brief Checks whether the container is empty. */
    constexpr bool empty() const noexcept;

    /** @brief Returns the number of elements. */
    constexpr size_type size() const noexcept;

    /** @brief Maximum number of elements the container could theoretically hold. */
    constexpr size_type max_size() const noexcept;

    /**
     * @brief Request a capacity at least `new_cap`.
     * @param new_cap Desired capacity (elements).
     * @throw std::bad_alloc If allocation fails.
     */
    void reserve(size_type new_cap);

    /** @brief Returns the number of elements that can be held without reallocation. */
    constexpr size_type capacity() const noexcept;

    /** @brief Reduces capacity to fit `size()`.  No effect on size. */
    void shrink_to_fit();

    //-------------------------------------------------------------------------
    // Modifiers
    //-------------------------------------------------------------------------

    /** @brief Erase all elements (`size()` becomes 0). */
    void clear() noexcept;

    /** @name insert */
    ///@{
    /** @brief Insert copy of `value` before `pos`. */
    iterator insert(const_iterator pos, const T& value);
    /** @brief Move `value` before `pos`. */
    iterator insert(const_iterator pos, T&& value);
    /** @brief Insert `count` copies of `value` before `pos`. */
    iterator insert(const_iterator pos, size_type count, const T& value);

    /**
     * @brief Insert elements from range `[first,last)` before `pos`.
     * @tparam InputIt Non‑integral input iterator type.
     */
    template<class InputIt, typename = std::enable_if_t<!std::is_integral<InputIt>::value>>
    iterator insert(const_iterator pos, InputIt first, InputIt last);

    /** @brief Insert an initializer list before `pos`. */
    iterator insert(const_iterator pos, std::initializer_list<T> ilist);
    ///@}

    /**
     * @brief Construct element in‑place before `pos`.
     * @tparam Args  Constructor argument pack for `T`.
     * @return Iterator pointing to the inserted element.
     */
    template<class... Args>
    iterator emplace(const_iterator pos, Args&&... args);

    /** @name erase */
    ///@{
    /** @brief Erase element at `pos`. Returns iterator following erased element. */
    iterator erase(iterator pos);
    /** @copydoc erase(iterator) */
    iterator erase(const_iterator pos);
    /** @brief Erase range `[first,last)` (half‑open). */
    iterator erase(iterator first, iterator last);
    /** @copydoc erase(iterator,iterator) */
    iterator erase(const_iterator first, const_iterator last);
    ///@}

    /** @name push_back */
    ///@{
    /** @brief Append a copy of `value` to the end. */
    void push_back(const T& value);
    /** @brief Append `value` to the end via move. */
    void push_back(T&& value);
    ///@}

    /**
     * @brief Construct element in‑place at the end.
     * @tparam Args Constructor argument pack for `T`.
     * @return Reference to the newly inserted element.
     */
    template<class... Args>
    reference emplace_back(Args&&... args);

    /** @brief Remove the last element. Undefined behavior if empty. */
    void pop_back();

    /** @name resize */
    ///@{
    /** @brief Resize to `count`, value‑initializing new elements. */
    void resize(size_type count);
    /** @brief Resize to `count`, fill new elements with `value`. */
    void resize(size_type count, const T& value);
    ///@}

    /**
     * @brief Swap contents with `other` in constant time.
     * @param other Vector to swap with.
     * @post This vector contains the previous contents of @p other and vice‑versa.
     */
    void swap(Vector& other) noexcept;
};

//------------------------------------------------------------------------------
// Implementation includes
//------------------------------------------------------------------------------
#include "Vector_impl.h"
#include "vector_modifiers.h"
#include "vector_capacity.h"
#include "vector_elementAccess.h"
#include "vector_memberFunctions.h"
#include "vector_non_member_functions.h"