#include "my_library.h"
#include "vector.h"

int main(){
    cout << "This is v3.0" << endl;

    Vector<int> v;
    v.push_back(14);
    for(int i = 0; i < 5; i++){
        v.push_back(i+2);
    }

    for(int i = 0; i < v.size(); i++){
        cout << v[i] << endl;
    }

    auto pos = v.rbegin();
    for(auto i = pos; i != v.rend(); i++){
        cout << *i;
    }

    return 0;
}