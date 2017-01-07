#include <ctime>
#include <thread>
#include <iostream>
#include "Timer.hpp"

using namespace std;

Timer::Timer(unsigned int sec):
  status(0), wait_for_sec(10), timeup(false) {
  wait_for_sec = sec;
}

void Timer::start() {
  time_t cur, start;
  time(&start);
  time(&cur);
  
  cout << this_thread::get_id() << ", "
    << "Class counting for " << wait_for_sec << "sec" << endl;
  while (status != -1 && !timeup) {
    time(&cur);
    time_t dt = difftime(cur, start);
    if (dt >= wait_for_sec) {
      timeup = true;
      break;
    }
  }
  cout << this_thread::get_id() << ", Counting done (" << status << ")" << endl;
}

void Timer::spawn() {
  cout << "Calling thread" << endl;
  thread t1(&Timer::start, this);
  t1.detach();
}

void Timer::stop() {
  cout << this_thread::get_id() << ", Killed (" << status << ")" << endl;
  status = -1;
}