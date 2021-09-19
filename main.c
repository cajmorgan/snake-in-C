#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "main.h"
#include <pthread.h>

int main() {
  srand(time(NULL));
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
  init_pair(11, COLOR_WHITE, COLOR_BLACK);
  init_pair(HEADCOLOR, COLOR_YELLOW, COLOR_BLACK);
  init_pair(TAILCOLOR, COLOR_GREEN, COLOR_BLACK);
  init_pair(FOODCOLOR, COLOR_MAGENTA, COLOR_BLACK);
  bkgd(COLOR_PAIR(10));
  curs_set(0);
  refresh();

  getch();
  //UI
  gameWin = drawWindow(windowSize);
  
  //Player
  snake *snakePlayer = createPlayer(gameWin);
  drawPlayer(snakePlayer, gameWin);

  //Items
  items *powerups = initiateItems(gameWin, snakePlayer, windowSize);
  randomItemSpawner(powerups, gameWin, snakePlayer, windowSize);
  drawItems(powerups, gameWin);

  //Game Loop
  gameLoop(snakePlayer, gameWin, windowSize, powerups);

  getch();
  
}

void gameLoop(snake *snakePlayer, WINDOW *gameWin, float windowSize, items *powerups) {
  int direction = 1;
  int *speed, speedTimer;
  int *itemSpawner, itemSpawnerCounter;
  int keyDown;
  int height, width;
  bool *gameOver;
  bool createNewTail = false;
  createNewTail = true;

  speed = (int *)malloc(sizeof(int));
  itemSpawner = (int *)malloc(sizeof(int));
  gameOver = (bool *)malloc(sizeof(bool));
  *speed = 3;
  *itemSpawner = (rand() % 5) + 5; 
  itemSpawnerCounter = 0;
  speedTimer = 0;
  *gameOver = false;

  //Enable keys
  keypad(gameWin, TRUE);
  nodelay(gameWin, TRUE);

  windowSize = 0.4;
  gameWin = changeWindowSize(gameWin, windowSize);
 
  while(1) {
    getmaxyx(gameWin, height, width);
    timerFunc(*speed);

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
      case ' ':
        createTail(snakePlayer);
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
        snakePlayer = selfBite(snakePlayer, gameOver);
        powerups = useItemIfPos(snakePlayer, powerups, speed, gameWin, windowSize, &speedTimer);
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

        createNewTail = checkTail(snakePlayer, createNewTail);
        snakePlayer = selfBite(snakePlayer, gameOver);
        powerups = useItemIfPos(snakePlayer, powerups, speed, gameWin, windowSize, &speedTimer);
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
        snakePlayer = selfBite(snakePlayer, gameOver);
        powerups = useItemIfPos(snakePlayer, powerups, speed, gameWin, windowSize, &speedTimer);
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
        snakePlayer = selfBite(snakePlayer, gameOver);
        powerups = useItemIfPos(snakePlayer, powerups, speed, gameWin, windowSize, &speedTimer);
        updatePlayer(snakePlayer);
        drawPlayer(snakePlayer, gameWin);
        break;
    }

    //Item spawner
    if(*itemSpawner == itemSpawnerCounter) {
      randomItemSpawner(powerups, gameWin, snakePlayer, windowSize);
      itemSpawnerCounter = 0;
      *itemSpawner = (rand() % 5) + 5; 
    } else {
      itemSpawnerCounter += 1;
    }

    //FX timers
    if(*speed == 1 && speedTimer != 150) {
      speedTimer += 1;
    } else {
      *speed = 3;
      speedTimer = 0;
    }

    if(*gameOver == true) {
      printw("GAME OVER");
      refresh();
      break;
    }
    refresh();    
  } 
}
