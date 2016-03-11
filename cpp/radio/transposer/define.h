// common information
#include <cstdint>

#ifndef DEFINE_H
#define DEFINE_H

#define COMMAND_TERMINATE_CHAR '\n'
#define COMMAND_BUFFER_LENGTH 3
#define COMMAND_CODE_ERROR 'e'
#define COMMAND_CODE_WAIT 'w'
#define COMMAND_CODE_MOTION_FORWARD 'f'
#define COMMAND_CODE_MOTION_BACKWARD 'b'
#define COMMAND_CODE_MOTION_LEFT 'l'
#define COMMAND_CODE_MOTION_RIGHT 'r'
#define COMMAND_CODE_MOTION_STOP 's'
#define COMMAND_CODE_MOTION_IDLE 'i'


struct command_t {
  char code;
  uint8_t parameter;
};

#endif
