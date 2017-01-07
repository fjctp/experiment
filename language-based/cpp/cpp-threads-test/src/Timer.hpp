#ifndef TIMER_HPP
#define TIMER_HPP

#include <ctime>
#include <thread>
#include <iostream>

using namespace std;

class Timer {
public:
  Timer(unsigned int sec);
  void start();
  void spawn();
  void stop();

private:

  unsigned int status; // TODO: use atomic class for thread safe operation
  unsigned int wait_for_sec;
  bool timeup;
};

#endif