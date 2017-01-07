/*
 *
 * Explore ways to initialize a struct
 *
 */

#include <iostream>

using namespace std;

typedef struct command {
    char type;
    char const *message;
    
    command(): type(), message() {} // empty constructor
    command(char t, char const *m): type(t), message(m) {} // constructor with args
} command;

void print_command(command t) {
    cout << t.type << ", " << t.message << endl << endl;
}

int main () {
    command t1;
    t1.type='C';
    t1.message="1234";
    print_command(t1);
    
    command t2('A',"What are you doing");
    print_command(t2);
    
    // anonymous struct can be initialize with {...}
    struct {char type; char const *message;} t3 = {'B',"How are you doing?"};
    
    // readonly after initialization
    const command t4('C', "How are you?");
    print_command(t4);
    
    return 0;
}