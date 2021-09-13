#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "main.h"
#include "./components/UI.c"
#include "./components/mechanism.c"




int main() {

  float windowSize = 1;
  WINDOW *gameWin;
  int test = 0;
  scanf("%d", &test);
  scanf("%d", &test);

  //Init
  initscr();
  cbreak();
  noecho();
  resizeterm(40, 80);
  //colors
  start_color();
  init_pair(10, COLOR_WHITE, COLOR_BLACK);
  init_pair(HEADCOLOR, COLOR_GREEN, COLOR_BLACK);
  init_pair(TAILCOLOR, COLOR_WHITE, COLOR_BLACK);
  bkgd(COLOR_PAIR(10));
  curs_set(0);
  refresh();

  getch();
  //UI
  gameWin = drawWindow(windowSize);
  


  //Player
  snake *snakePlayer = createPlayer();
  drawPlayer(snakePlayer, gameWin);

  //Game Loop
  gameLoop(snakePlayer, gameWin, windowSize);

  getch();
  
}



void gameLoop(snake *snakePlayer, WINDOW *gameWin, float windowSize) {
  int direction = 1;
  int speed = 1;
  int keyDown;
  int height, width;
  bool createNewTail = false;
  createNewTail = true;

  //Enable keys
  keypad(gameWin, TRUE);
  nodelay(gameWin, TRUE);
 

  while(1) {
    getmaxyx(gameWin, height, width);
    timerFunc(speed);

    //Direction
    keyDown = wgetch(gameWin);
    switch(keyDown) {
      case KEY_UP:
        if(direction != 3)
          direction = 1;
        
        break;
      case KEY_RIGHT:
        if(direction != 4)
          direction = 2;
        break;
      case KEY_DOWN:
        if(direction != 1)
          direction = 3;
        break;
      case KEY_LEFT:
        if(direction != 2)
          direction = 4;
        break;  
    }
    switch(direction) {
      case 1:
        removePlayer(snakePlayer, gameWin);
        updatePrev(snakePlayer);

        if(snakePlayer->posY == (height - height) + 1) {
          snakePlayer->posY = height - 2;
        } else {
          snakePlayer->posY -= 1;
        }
        
        createNewTail = checkTail(snakePlayer, createNewTail);
        snakePlayer = selfBite(snakePlayer);
        updatePlayer(snakePlayer);
        drawPlayer(snakePlayer, gameWin);
        break;
      case 2:
        removePlayer(snakePlayer, gameWin);
        updatePrev(snakePlayer);

        if(snakePlayer->posX == width - 2) {
          snakePlayer->posX = ((width - width) + 2);
        } else {
          snakePlayer->posX += 2;
        }

        createTail(snakePlayer);
        createNewTail = checkTail(snakePlayer, createNewTail);
        snakePlayer = selfBite(snakePlayer);
        updatePlayer(snakePlayer);
        drawPlayer(snakePlayer, gameWin);
        break;
      case 3:
        removePlayer(snakePlayer, gameWin);
        updatePrev(snakePlayer);

        if(snakePlayer->posY == height - 2) {
          snakePlayer->posY = (height - height) + 1;
        } else {
          snakePlayer->posY += 1;
        }

        createNewTail = checkTail(snakePlayer, createNewTail);
        snakePlayer = selfBite(snakePlayer);
        updatePlayer(snakePlayer);
        drawPlayer(snakePlayer, gameWin);
        break;
      case 4:
        removePlayer(snakePlayer, gameWin);
        updatePrev(snakePlayer);
       
        if(snakePlayer->posX == (width - width) + 2) {
          snakePlayer->posX = width - 2;
        } else {
          snakePlayer->posX -= 2;
        }

        createNewTail = checkTail(snakePlayer, createNewTail);
        snakePlayer = selfBite(snakePlayer);
        updatePlayer(snakePlayer);
        drawPlayer(snakePlayer, gameWin);
        break;
    }
    refresh();
  } 
}
