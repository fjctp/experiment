#include <ctime>
#include <thread>
#include <iostream>
#include "Timer.hpp"

using namespace std;

void func_wait(unsigned int sec) {
  time_t cur, start;
  time(&start);
  time(&cur);
  
  bool timeup = false;
  cout << this_thread::get_id() << ", "
    << "Start counting for " << sec << "sec" << endl;
  while (!timeup) {
    time(&cur);
    if (difftime(cur, start) >= sec) {
      timeup = true;
      cout << this_thread::get_id() << ", Counting done" << endl;
    }
  }
}


void func_say_hi() {
  cout << this_thread::get_id() << ", " << "Hello" << endl;
}

int main (int argc, char* argv[]) {
  Timer t1(10);
  t1.spawn();

  //Timer t2(20);
  //t2.spawn();

  //thread td1(func_say_hi);
  //thread td2(func_wait, 10);
  //thread td3(func_wait, 5);
  
  // join or detach MUST be called for each thread!!!
  //td1.join();
  //td2.join();
  //td3.join();
  t1.stop();
  //t2.stop();

  return 0;
}