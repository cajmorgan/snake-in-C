#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"
#include "./components/UI.c"
#include "./components/mechanism.c"



int main() {

  float windowSize = 1;
  WINDOW *gameWin;


  //Init
  initscr();
  cbreak();
  noecho();
  resizeterm(40, 80);
  start_color();
  init_pair(10, COLOR_WHITE, COLOR_BLACK);
  bkgd(COLOR_PAIR(10));
  curs_set(0);
  refresh();

  //UI
  gameWin = drawWindow(windowSize);
  


  //Player
  snake *snakePlayer = createPlayer();
  drawPlayer(snakePlayer, gameWin);

  //Game Loop
  gameLoop(snakePlayer, gameWin);

  getch();
  
}



void gameLoop(snake *snakePlayer, WINDOW *gameWin) {
  int direction = 1;
  int speed = 7;
  int keyDown;

  //Enable keys
  keypad(gameWin, TRUE);
  nodelay(gameWin, TRUE);
  
  

  while(1) {
    //Direction
    keyDown = wgetch(gameWin);
    switch(keyDown) {
      case KEY_UP:
        direction = 1;
        break;
      case KEY_RIGHT:
        direction = 2;
        break;
      case KEY_DOWN:
        direction = 3;
        break;
      case KEY_LEFT:
        direction = 4;
        break;  
    }

    switch(direction) {
      case 1:
        removePlayer(snakePlayer, gameWin);
        snakePlayer->posY -= 1;
        drawPlayer(snakePlayer, gameWin);
        break;
      case 2:
        removePlayer(snakePlayer, gameWin);
        snakePlayer->posX += 2;
        drawPlayer(snakePlayer, gameWin);
        break;
      case 3:
        removePlayer(snakePlayer, gameWin);
        snakePlayer->posY += 1;
        drawPlayer(snakePlayer, gameWin);
        break;
      case 4:
        removePlayer(snakePlayer, gameWin);
        snakePlayer->posX -= 2;
        drawPlayer(snakePlayer, gameWin);
        break;
    }
    refresh();
    timerFunc(speed);
  } 
}
