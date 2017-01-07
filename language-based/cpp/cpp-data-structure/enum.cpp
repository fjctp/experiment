
#include <iostream> 

int main() {
  enum class CommandCode : char {
    error_status = 'e',
    wait_for_command = 'n',
    robot_forward = 'f',
    robot_backward = 'b',
    robot_left = 'l',
    robot_right = 'r',
    robot_stop = 's',
    robot_idle = 'i'
  };
  
  CommandCode cc1;
  
  std::cout << "Hello\n\n";
  std::cout << cc1.error_status;
  std::cout << CommandCode::error_status;
  std::cout << "\n";"
  
  return 0;
}
