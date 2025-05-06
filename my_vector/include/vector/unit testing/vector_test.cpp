// test_vector.cpp
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "vector.h"
#include <vector>
#include <string>
#include <stdexcept>

TEST_CASE("Default constructor yields empty vector", "[constructors]") {
    Vector<int> v;
    REQUIRE(v.empty());
    REQUIRE(v.size() == 0);
    REQUIRE(v.capacity() == 0);
    REQUIRE(v.begin() == v.end());
}

TEST_CASE("Fill constructor and assign(count, value)", "[constructors][assign]") {
    Vector<std::string> v(3, "hello");
    REQUIRE_FALSE(v.empty());
    REQUIRE(v.size() == 3);
    for (size_t i = 0; i < v.size(); ++i)
        REQUIRE(v[i] == "hello");
    // assign to new size
    v.assign(5, "x");
    REQUIRE(v.size() == 5);
    for (auto& s : v) REQUIRE(s == "x");
}

TEST_CASE("Iterator-range constructor", "[constructors]") {
    std::vector<int> src = {1,2,3,4};
    Vector<int> v(src.begin(), src.end());
    REQUIRE(v.size() == src.size());
    REQUIRE(std::equal(v.begin(), v.end(), src.begin()));
}

TEST_CASE("Initializer-list constructor and assignment", "[constructors][assign]") {
    Vector<double> v = {0.1, 0.2, 0.3};
    REQUIRE(v.size() == 3);
    REQUIRE(v[0] == Approx(0.1));
    REQUIRE(v[2] == Approx(0.3));

    v = {9.9, 8.8};
    REQUIRE(v.size() == 2);
    REQUIRE(v[1] == Approx(8.8));
}

TEST_CASE("Copy and move semantics", "[special_members]") {
    Vector<int> orig = {1,2,3};
    Vector<int> copy(orig);
    REQUIRE(copy == orig);

    Vector<int> moved(std::move(copy));
    REQUIRE(moved == orig);
    REQUIRE(copy.size() == 0);
    REQUIRE(copy.capacity() == 0);

    Vector<int> a = {7,8};
    Vector<int> b;
    b = std::move(a);
    REQUIRE(b.size() == 2);
    REQUIRE(a.empty());
}

TEST_CASE("push_back, emplace_back, pop_back, clear", "[modifiers]") {
    Vector<std::string> v;
    v.push_back("a");
    v.push_back(std::string("b"));
    REQUIRE(v.size() == 2);
    REQUIRE(v.back() == "b");

    v.emplace_back(3, 'x');
    REQUIRE(v.size() == 3);
    REQUIRE(v.back() == "xxx");

    v.pop_back();
    REQUIRE(v.size() == 2);
    v.clear();
    REQUIRE(v.empty());
    REQUIRE(v.size() == 0);
}

TEST_CASE("insert and erase single and ranges", "[modifiers]") {
    Vector<int> v = {1,2,3,4};
    // single insert
    auto it = v.insert(v.begin()+2, 99);
    REQUIRE(*it == 99);
    REQUIRE(v.size() == 5);
    REQUIRE(v[2] == 99);

    // erase single
    it = v.erase(v.begin()+2);
    REQUIRE(*it == 3);
    REQUIRE(v.size() == 4);

    // range insert
    std::vector<int> more = {7,8,9};
    it = v.insert(v.begin()+1, more.begin(), more.end());
    REQUIRE(v.size() == 7);
    REQUIRE( (v[1] == 7 && v[3] == 9) );


    // range erase
    it = v.erase(v.begin()+1, v.begin()+4);
    REQUIRE(v.size() == 4);
    REQUIRE(v[1] == 2);
}

TEST_CASE("resize, reserve, shrink_to_fit", "[capacity]") {
    Vector<int> v;
    v.reserve(10);
    REQUIRE(v.capacity() >= 10);

    v.resize(5, 42);
    REQUIRE(v.size() == 5);
    for (auto x : v) REQUIRE(x == 42);

    size_t old_cap = v.capacity();
    v.shrink_to_fit();
    REQUIRE(v.capacity() == v.size());
    REQUIRE(v.capacity() <= old_cap);
}

TEST_CASE("at(), operator[], front(), back(), data()", "[element_access]") {
    Vector<char> v = {'a','b','c'};
    REQUIRE(v.at(0) == 'a');
    REQUIRE(v[1] == 'b');
    REQUIRE(v.front() == 'a');
    REQUIRE(v.back() == 'c');
    REQUIRE(v.data()[2] == 'c');

    // out-of-range
    REQUIRE_THROWS_AS(v.at(10), std::out_of_range);
    Vector<int> empty_vec;
    REQUIRE_THROWS_AS(empty_vec.front(), std::out_of_range);
    REQUIRE_THROWS_AS(empty_vec.back(), std::out_of_range);
}

TEST_CASE("iterators and reverse_iterators", "[iterators]") {
    Vector<int> v = {1,2,3};
    int sum = 0;
    for (auto it = v.begin(); it != v.end(); ++it) sum += *it;
    REQUIRE(sum == 6);

    sum = 0;
    for (auto rit = v.rbegin(); rit != v.rend(); ++rit) sum += *rit;
    REQUIRE(sum == 6);
}

TEST_CASE("comparison operators", "[non_member]") {
    Vector<int> a = {1,2,3}, b = {1,2,3}, c = {1,2,4};
    REQUIRE(a == b);
    REQUIRE(a != c);
    REQUIRE(a < c);
    REQUIRE(c > a);
    REQUIRE(a <= b);
    REQUIRE(c >= b);
}

TEST_CASE("swap member and std::swap", "[modifiers]") {
    Vector<int> a = {1,2}, b = {3};
    a.swap(b);
    REQUIRE(a.size() == 1);
    REQUIRE(a[0] == 3);

    std::swap(a, b);
    REQUIRE(b.size() == 1);
    REQUIRE(b[0] == 3);
}

// Copy‐assignment operator
TEST_CASE("Copy assignment operator", "[special_members][assign]") {
    Vector<int> src = {1,2,3,4};
    Vector<int> dest;
    dest = src;
    REQUIRE(dest == src);
    REQUIRE(dest.size() == src.size());
    REQUIRE(dest.capacity() == src.capacity());
    // original still intact
    REQUIRE(src.size() == 4);
    for (size_t i = 0; i < src.size(); ++i)
        REQUIRE(src[i] == static_cast<int>(i + 1));
}

// assign(InputIt, InputIt) overload
TEST_CASE("assign(InputIt, InputIt) overload", "[assign]") {
    std::vector<std::string> src = {"foo","bar","baz"};
    Vector<std::string> v;
    v.assign(src.begin(), src.end());
    REQUIRE(v.size() == src.size());
    for (size_t i = 0; i < src.size(); ++i)
        REQUIRE(v[i] == src[i]);
}

// assign(initializer_list) member function
TEST_CASE("assign(initializer_list) member function", "[assign]") {
    Vector<double> v;
    v.assign({3.14, 2.71, 1.62});
    REQUIRE(v.size() == 3);
    REQUIRE(v[0] == Approx(3.14));
    REQUIRE(v[1] == Approx(2.71));
    REQUIRE(v[2] == Approx(1.62));
}

// resize(count) without fill‐value
TEST_CASE("resize(count) without fill‐value", "[capacity][modifiers]") {
    Vector<std::string> v = {"a","b"};
    v.resize(4);
    REQUIRE(v.size() == 4);
    REQUIRE(v[0] == "a");
    REQUIRE(v[1] == "b");
    // new elements should be value‐initialized
    REQUIRE(v[2].empty());
    REQUIRE(v[3].empty());
}

// insert(pos, T&&) rvalue overload
TEST_CASE("insert(pos, T&&) rvalue overload", "[modifiers]") {
    Vector<std::string> v = {"x","y","z"};
    auto it = v.insert(v.begin() + 1, std::string("moved"));
    REQUIRE(*it == "moved");
    REQUIRE(v.size() == 4);
    REQUIRE(v[1] == "moved");
}

// insert(pos, count, value) overload
TEST_CASE("insert(pos, count, value) overload", "[modifiers]") {
    Vector<int> v = {1,2,3};
    auto it = v.insert(v.begin() + 1, 3, 9);
    REQUIRE(v.size() == 6);
    REQUIRE(v[0] == 1);
    REQUIRE(v[1] == 9);
    REQUIRE(v[3] == 9);
    REQUIRE(v[4] == 2);
    REQUIRE(v[5] == 3);
    REQUIRE(*it == 9);
}

// insert(pos, initializer_list) overload
TEST_CASE("insert(pos, initializer_list) overload", "[modifiers]") {
    Vector<int> v = {1,2,3};
    auto it = v.insert(v.begin() + 2, {7,8});
    REQUIRE(v.size() == 5);
    REQUIRE(v[2] == 7);
    REQUIRE(v[3] == 8);
    REQUIRE(*it == 7);
}

// emplace(pos, Args&&...) in‐place insert
TEST_CASE("emplace(pos, Args&&...) in-place insert", "[modifiers]") {
    Vector<std::string> v = {"a","c"};
    auto it = v.emplace(v.begin() + 1, 3, 'b');
    REQUIRE(*it == "bbb");
    REQUIRE(v.size() == 3);
    REQUIRE(v[0] == "a");
    REQUIRE(v[1] == "bbb");
    REQUIRE(v[2] == "c");
}

// erase(const_iterator) overload
TEST_CASE("erase(const_iterator) overload", "[modifiers]") {
    Vector<int> v = {1,2,3,4};
    auto it = v.erase(v.cbegin() + 2);
    REQUIRE(v.size() == 3);
    REQUIRE(v[0] == 1);
    REQUIRE(v[1] == 2);
    REQUIRE(v[2] == 4);
    REQUIRE(it == v.begin() + 2);
}

// empty(), size(), capacity() after copy‐assign and shrink_to_fit
TEST_CASE("empty, size, capacity after copy-assign and shrink", "[capacity][special_members]") {
    Vector<int> v1(5, 1);
    v1.reserve(10);
    REQUIRE(v1.capacity() >= 10);

    Vector<int> v2;
    v2 = v1;
    REQUIRE(v2.size() == 5);
    REQUIRE(v2.capacity() >= 5);
    REQUIRE_FALSE(v2.empty());

    v2.shrink_to_fit();
    REQUIRE(v2.capacity() == v2.size());
}

// const overloads of at, front, back, data, and const iterators
TEST_CASE("const overloads of element access and const iterators", "[element_access][iterators]") {
    const Vector<int> cv = {5,6,7};
    REQUIRE(cv.at(1) == 6);
    REQUIRE(cv.front() == 5);
    REQUIRE(cv.back() == 7);
    REQUIRE(cv.data()[2] == 7);

    int sum = 0;
    for (auto it = cv.cbegin(); it != cv.cend(); ++it)
        sum += *it;
    REQUIRE(sum == 18);

    sum = 0;
    for (auto rit = cv.crbegin(); rit != cv.crend(); ++rit)
        sum += *rit;
    REQUIRE(sum == 18);
}
