/*
 *
 * Explore bit operations
 * it applies to int only
 *
 */

#include <iostream>

using namespace std;

int main () {
    
    const char *foo = "This is a test";
    unsigned int x=0xEC; //b1110 1100, d236
    
    cout << sizeof(char) << endl; // 1 byte
    cout << sizeof(unsigned int) << endl; // 4 bytes
    cout << endl;
    
    cout << *(foo+0) << endl;
    cout << foo << endl;
    cout << x << endl;
    cout << (x>>4) << endl; // right shift 4 bytes, x/(2^4)
    cout << (x>>2) << endl; // right shift 2 bytes
    cout << (x&0xA) << endl;
    cout << endl;
    
    cout << 10 << endl; // 10*5
    cout << (10<<2) + 10 << endl; // 10*5
    
    return 0;
}
