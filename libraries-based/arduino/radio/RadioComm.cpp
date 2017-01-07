#include "define.h"
#include "RadioComm.h"
#include <Arduino.h>
#include <SPI.h>
#include <RF24.h>

RadioComm::RadioComm(uint8_t ce_pin, uint8_t cs_pin) {
  rf = new RF24(ce_pin, cs_pin);
  rf->begin();
  rf->enableAckPayload();
  rf->enableDynamicPayloads();
  if(this->isMaster) {
    rf->openWritingPipe(addresses[1]);
    rf->openReadingPipe(1, addresses[0]);
  }
  else {
    rf->openWritingPipe(addresses[0]);
    rf->openReadingPipe(1, addresses[1]);
  }
  rf->startListening();
}

command_t RadioComm::get_command() {
  command_t cmd1;
  cmd1.code = COMMAND_CODE_WAIT;
  cmd1.parameter = 0;
  
  if (rf->available()) {
    char bf[3];
    rf->read(bf, sizeof(bf)/sizeof(*bf));
    cmd1 = this->prase_command(bf);
  }
  
  return cmd1;
}

void RadioComm::send_message(char *msg) {
  rf->stopListening();
  rf->write(msg, sizeof(msg)/sizeof(*msg));
  rf->startListening();  
}
