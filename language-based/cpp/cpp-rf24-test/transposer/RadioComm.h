#ifndef RADIOCOMM_H
#define RADIOCOMM_H

#include "define.h"
#include "Comm.h"
#include <cstdint>
#include "RF24/RF24.h"

class RadioComm : Comm {

private:
  const unsigned char addresses[2][6] = {"1Node", "2Node"};
  const bool isMaster = true;
  
  RF24* rf;
  
public:
  RadioComm(uint8_t ce_pin, uint8_t cs_pin);
  command_t get_command(); // if no new command 
                           //   return null
  void send_message(char *msg);
};

#endif
