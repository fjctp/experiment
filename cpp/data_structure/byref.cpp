#include <iostream>

using namespace std;

void print(int a, int b) {
    cout << a << ',' << b << endl;
}

void byref(int& a, int&b) {
    print(a, b);
    a = 20;
    b = 30;
    print(a, b);
}

int main () {
    int a = 10;
    int b = 15;
    
    byref(a, b);
    print(a, b);
    
    return 0;
}

