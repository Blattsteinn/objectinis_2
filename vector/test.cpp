#include "my_library.h"
#include "vector.h"

int main(){
    cout << "This is v3.0" << endl;

    const int n = 5;
    int A1[n] = {10, 4, 7, 8, 9};
    int A2[n] = {9, 3, 5, 4, 8};

    Vector<int> v1(A1, A1+n);
    Vector<int> v2(A2, A2+n);

    // V1
    for(int i=0; i < v1.size(); i++){
        cout << v1[i] << " ";
    } cout << endl;

    
    // V2
    for(int i=0; i < v2.size(); i++){
        cout << v2[i] << " ";
    } cout << endl;

    if(v1 > v2){
        cout << "v1 is bigger!" << endl;
    }



    return 0;
}