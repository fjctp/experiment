#include "define.h"
#include "RadioComm.h"
#include <Arduino.h>
#include <SPI.h>
#include <RF24.h>

RadioComm* r1;
bool isSender = false;

void setup() {
  Serial.begin(115200);
  Serial.println("RF24 Test");
  
  r1 = new RadioComm(40, 4);
}

void loop() {
  if (isSender)
    r1->send_message("f00;");
  else {
    command_t cmd1 = r1->get_command();
    char tmp[2];
    tmp[0] = cmd1.code;
    tmp[1] = '\0';
    Serial.print("cmd: ");
    Serial.print(tmp);
    Serial.print(":");
    Serial.println(cmd1.parameter);
  }
  delay(2*1000);
}
