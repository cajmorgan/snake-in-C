#include <curses.h> 
#include "UI.h"



WINDOW *drawWindow(float windowSize) {
  WINDOW *gameWin;
  int width, height, startY, startX;
  width = 80 * windowSize;
  height = 40 * windowSize;
  getmaxyx(stdscr, startY, startX);

  startX = ((startX - (startX * windowSize)) / 2);
  startY = ((startY - (startY * windowSize)) / 2);

  gameWin = newwin(height, width, startY, startX);
  wborder(gameWin, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
  wbkgd(gameWin, COLOR_PAIR(11));
  wrefresh(gameWin);
  
  return gameWin;
}
