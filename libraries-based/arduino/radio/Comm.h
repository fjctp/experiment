#ifndef COMM_H
#define COMM_H

#include "define.h"
#include <Arduino.h>

/*
 * Base class for all communication classes
 * 
 * Publc APIs
 * command_t get_command(); // read command from master. 
 *                          // if none, return COMMAND_CODE_WAIT
 * void send_message(char *msg); // send message to master
 */

class Comm {

protected:
  command_t prase_command(char* msg);
  
public:
  Comm();
  
  command_t get_command();
  void send_message(char *msg);
};

#endif
