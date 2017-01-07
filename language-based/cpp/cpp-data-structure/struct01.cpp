#include <iostream>
#define TEST_WITH_CHAR 'e'

using namespace std;

struct command_t {
  char code;
  int parameter;
};

int main () {
  command_t c1;
  c1.code = 'c';
  c1.parameter = 100;

  cout << TEST_WITH_CHAR << endl;
  return 0;
}
