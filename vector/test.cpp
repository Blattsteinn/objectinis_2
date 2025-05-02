#include "my_library.h"
#include "vector.h"

int main(){
    cout << "This is v3.0" << endl;

    int A [5] = {5,4,2,4,10};

    Vector<int> v(A, A + 5);
    for(int i = 0; i< v.size(); i++){
        cout << v[i] << " ";
    } cout << endl;


    cout << "inserting 5!" << endl;
    auto pos = v.begin();
    v.insert(pos, 88);

    int gamer = 777;
    pos = v.begin() + 2;
    v.insert(pos, std::move(gamer));  // also binds to the T&& overload

    for(int i = 0; i< v.size(); i++){
        cout << v[i] << " ";
    } cout << endl;

    cout << "x value is: " << gamer << endl;

    return 0;
}