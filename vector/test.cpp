#include "my_library.h"
#include "vector.h"

int main(){
    cout << "This is v3.0" << endl;
    Vector<int> a;

    a.push_back(5);
    a.push_back(10);
    cout << a.size() << endl;
    cout << a.capacity() << endl;

    for(int i=0; i < a.size(); i++){
        cout << a[i] << endl;
    }

    return 0;
}