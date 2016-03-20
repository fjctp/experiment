#include <iostream>

using namespace std;

void print_array (unsigned int x[], unsigned int size) {
    for (int i=0;i<size;i++) {
        cout << x[i] << endl;
    }
}

void change_array (unsigned int x[], unsigned int size) {
    for (int i=0;i<size;i++) {
        x[i]=i;
    }
}

int main () {
    int size = 4;
    unsigned int x[size];
    for (int i=0;i<size;i++) {
        x[i]=i*10;
    }
    print_array(x, size);
    
    change_array(x, size);
    print_array(x, size);
    
    return 0;
}