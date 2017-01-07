#include <iostream>

using namespace std;

class foo {
public:
    int x;
};

void print(foo a) {
    cout << a.x << endl;
}

void byref(foo& a) {
    print(a);
    a.x = 20;
    print(a);
}


void byref_test(foo& a) {
    print(a);
    foo abc;
    abc.x = 100;
    a = abc;
    //a = foo();
    //a.x = 100;
    print(a);
}

int main () {
    foo a, b;
    a.x = 10;
    
    byref(a);
    print(a);
    
    byref_test(b);
    print(b);
    
    return 0;
}

