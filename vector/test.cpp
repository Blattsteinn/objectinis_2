#include "my_library.h"
#include "vector.h"

int main(){
    cout << "This is v3.0" << endl;

    Vector<int> v;
    v.push_back(0);
    v.push_back(0);
    v.push_back(0);
    v.push_back(0);

    cout << v.capacity() << endl;

    v.pop_back();
    v.pop_back();

    cout << v.capacity() << endl;
    v.shrink_to_fit();

    cout << v.capacity() << endl;

    return 0;
}