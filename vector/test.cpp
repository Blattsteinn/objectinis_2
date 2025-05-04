#include "Vector.h"
#include "my_library.h"


struct S { 
    int x; 
    S(int v): x(v) {} 
};

struct P { 
    int x, y; 
    P(int a, int b): x(a), y(b) {} 
};

int main() {
    // 1. Default construction
    {
        Vector<int> v;
        assert(v.empty());
        assert(v.size() == 0);
        assert(v.capacity() == 0);
    }

    // 2. Fill constructor (count + value)
    {
        Vector<std::string> v(3, "hi");
        assert(v.size() == 3 && v.capacity() == 3);
        assert(v[0] == "hi" && v[1] == "hi" && v[2] == "hi");
    }

    // 3. Range constructor
    {
        int a[] = {1,2,3,4};
        Vector<int> v(std::begin(a), std::end(a));
        assert(v.size() == 4 && v.capacity() == 4);
        assert(v[0]==1 && v[1]==2 && v[2]==3 && v[3]==4);
    }

    // 4. Initializer-list constructor
    {
        Vector<char> v = {'a','b','c'};
        assert(v.size() == 3 && v.capacity() == 3);
        assert(v[0]=='a' && v[1]=='b' && v[2]=='c');
    }

    // 5. Copy constructor & copy assignment
    {
        Vector<int> x = {10,20,30};
        Vector<int> y(x);
        Vector<int> z;
        z = x;
        x[0] = 99;
        assert(y[0] == 10 && z[0] == 10);  // deep copy
    }

    // 6. Move constructor & move assignment
    {
        Vector<int> a = {1,2,3};
        Vector<int> b(std::move(a));
        Vector<int> c;
        c = std::move(b);
        assert(c.size()==3 && c[0]==1 && c[1]==2 && c[2]==3);
        assert(a.empty() && b.empty());
    }

    // 7. Element access: at() vs operator[]
    {
        Vector<int> v = {5,6,7};
        int x = v.at(1);
        v[2] = 42;
        assert(x == 6 && v[2] == 42);
        bool caught = false;
        try { v.at(3); }
        catch(const std::out_of_range&) { caught = true; }
        assert(caught);
    }

    // 8. front() / back() on non-empty & empty
    {
        Vector<int> v = {8,9};
        assert(v.front() == 8 && v.back() == 9);
        Vector<int> e;
        bool caught = false;
        try { e.front(); }
        catch(const std::out_of_range&) { caught = true; }
        assert(caught);
    }

    // 9. Capacity management: reserve() / shrink_to_fit()
    {
        Vector<int> v;
        v.reserve(5);
        assert(v.capacity() >= 5);
        v.push_back(1);
        v.push_back(2);
        assert(v.size() == 2 && v[0]==1 && v[1]==2);
        v.shrink_to_fit();
        assert(v.capacity() == v.size());
    }

    // 10. empty(), size(), max_size()
    {
        Vector<double> v(100);
        assert(!v.empty() && v.size() == 100);
        assert(v.max_size() > 100);
    }

    // 11. push_back (lvalue & rvalue) & emplace_back
    {
        Vector<S> v;
        S s(7);
        v.push_back(s);
        v.push_back(S(8));
        v.emplace_back(9);
        assert(v.size() == 3);
        assert(v[0].x == 7 && v[1].x == 8 && v[2].x == 9);
    }

    // 12. pop_back()
    {
        Vector<int> v = {1,2,3};
        v.pop_back();
        assert(v.size() == 2 && v[0]==1 && v[1]==2);
    }

    // 13. insert() overloads
    {
        Vector<int> v = {1,3};
        v.insert(v.begin()+1, 2);
        v.insert(v.end(), 2, 4);
        int a[] = {5,6};
        v.insert(v.begin(), a, a+2);
        v.insert(v.end(), {7,8});
        // expect {5,6,1,2,3,4,4,7,8}
        int expected[] = {5,6,1,2,3,4,4,7,8};
        assert(v.size() == 9);
        for (size_t i = 0; i < v.size(); ++i)
            assert(v[i] == expected[i]);
    }

    // 14. emplace() in middle
    {
        Vector<P> v;
        v.emplace(v.begin(), 1, 2);
        assert(v.size()==1 && v[0].x==1 && v[0].y==2);
    }

    // 15. erase() single & range
    {
        Vector<int> v = {1,2,3,4};
        v.erase(v.begin()+1);
        assert(v.size()==3 && v[0]==1 && v[1]==3 && v[2]==4);
        v.erase(v.begin(), v.begin()+2);
        assert(v.size()==1 && v[0]==4);
    }

    // 16. clear()
    {
        Vector<int> v = {1,2,3};
        v.clear();
        assert(v.empty() && v.size()==0);
    }

    // 17. assign() variants
    {
        Vector<int> v;
        v.assign(3, 7);
        assert(v.size()==3 && v[0]==7 && v[1]==7 && v[2]==7);
        int a[] = {8,9};
        v.assign(a, a+2);
        assert(v.size()==2 && v[0]==8 && v[1]==9);
        v.assign({10,11,12});
        assert(v.size()==3 && v[0]==10 && v[1]==11 && v[2]==12);
    }

    // 18. resize() up & down
    {
        Vector<int> v = {1,2,3,4};
        v.resize(2);
        assert(v.size()==2 && v[0]==1 && v[1]==2);
        v.resize(5);
        assert(v.size()==5 && v[2]==0 && v[3]==0 && v[4]==0);
        v.resize(7, 9);
        assert(v.size()==7 && v[5]==9 && v[6]==9);
    }

    // 19. swap()
    {
        Vector<int> a = {1,2}, b = {3};
        a.swap(b);
        assert(a.size()==1 && a[0]==3);
        assert(b.size()==2 && b[0]==1 && b[1]==2);
    }

    // 20. Iterators & relational operators
    {
        Vector<int> v = {1,2,3};
        int sum = 0;
        for (auto it = v.begin(); it != v.end(); ++it)
            sum += *it;
        assert(sum == 6);
        sum = 0;
        for (auto rit = v.rbegin(); rit != v.rend(); ++rit)
            sum += *rit;
        assert(sum == 6);

        Vector<int> x = {1,2}, y = {1,3};
        assert(x < y);
        assert(y > x);
        assert(!(x == y));
    }

    return 0;
}
