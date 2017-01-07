#include "define.h"
#include "RadioComm.h"
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <cstdio>
#include "RF24/RF24.h"

using namespace std;

RadioComm* r1;
bool isSender = true;

void setup() {
  r1 = new RadioComm(25, 0);
  cout << "Comm Started" << endl;
}

void loop() {
  if (isSender) {
    cout << "> ";
    char bf[4];
    cin >> bf;
    cout << (bf[3] == '\0') << endl;
    //cout << "Got: " <<  bf << endl;
    r1->send_message(bf);
    
    //command_t cmd1 = r1->get_command();
    //char tmp[4];
    //sprintf(tmp, "%c%d", cmd1.code, cmd1.parameter);
    //cout << "Remote> " << tmp << endl;
  }
  else {
    command_t cmd1 = r1->get_command();
    char tmp[2];
    tmp[0] = cmd1.code;
    tmp[1] = '\0';
  }
  //delay(2*100);
}

int main () {
  setup();

  while(true) {
    loop();
  }
}
