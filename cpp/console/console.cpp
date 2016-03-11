#include <ncurses.h>


int main (int argc, const char* argv[]) {
  initscr();
  raw();
  keypad(stdscr, TRUE);
  noecho();

  int ch = getch();
  
  printw("Key pressed: %c", ch);
  
  getch();
  endwin();
  return 0;
}
