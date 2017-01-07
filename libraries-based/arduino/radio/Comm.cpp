#include "define.h"
#include "Comm.h"


Comm::Comm() {
  
}

command_t Comm::prase_command(char* msg) {
  command_t cmd1;
  cmd1.code = COMMAND_CODE_ERROR;
  cmd1.parameter = 0;
  
  if ((sizeof(msg)/sizeof(*msg))>COMMAND_BUFFER_LENGTH+1) {
    return cmd1;
  }
  
  if(isalpha(msg[0]) && isdigit(msg[1]) && isdigit(msg[2])) {
    char tmp[2];
    tmp[0] = msg[1];
    tmp[1] = msg[2];
    cmd1.code=tolower(msg[0]);
    cmd1.parameter=atoi(tmp);
  }
  
  return cmd1;
}
 
command_t Comm::get_command() {
  // override this functiona
}

void Comm::send_message(char *msg) {
  // override this function
}
