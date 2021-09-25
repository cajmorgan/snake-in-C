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

void printScore(int score) {
  int height, width;
  getmaxyx(stdscr, height, width);
  mvprintw(1, 35, "Score: %d", score);
  refresh();
}

WINDOW *changeWindowSize(WINDOW *gameWin, float windowSize) {
  int height, width, startX, startY;
  getmaxyx(gameWin, height, width);
  getmaxyx(stdscr, startY, startX);
  wclear(gameWin);
  wrefresh(gameWin);
  wresize(gameWin, height * windowSize, width * windowSize);
  startX = ((startX - (startX * windowSize)) / 2);
  startY = ((startY - (startY * windowSize)) / 2);
  mvwin(gameWin, startY, startX);
  wattrset(gameWin, COLOR_PAIR(10));
  wborder(gameWin, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
  wrefresh(gameWin);

  return gameWin;
}