#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "main.h"

int main() {
  while(1) {
    srand(time(NULL));
    float windowSize = 1;
    WINDOW *gameWin;

    //Init
    initscr();
    wclear(stdscr);
    cbreak();
    noecho();
    resizeterm(40, 80);
    mvprintw(19, 29, "PRESS ANY KEY TO START");
    //colors
    initColors();
    curs_set(0);
    refresh();

    getch();
    //UI
    gameWin = drawWindow(windowSize);
    
    //Player
    snake *snakePlayer = createPlayer(gameWin);
    // drawPlayer(snakePlayer, gameWin, false);

    //Items
    items *powerups = initiateItems(gameWin, snakePlayer, windowSize);
    randomItemSpawner(powerups, gameWin, snakePlayer, windowSize);
    drawItems(powerups, gameWin);

    //Game Loop
    gameLoop(snakePlayer, gameWin, windowSize, powerups);

    getch();
    // //High score
    wclear(stdscr);
    createHighScoreFile();
    char **scoreArr = getHighScoresFromFile();
    checkIfHighScore(snakePlayer->score, scoreArr);
    
    mvprintw(0, 0, "%s", "Press 'q' to exit\n'r' to replay");
    while(1) {
      int c = getch();
      if(c == 'q') {
        delwin(gameWin);
        endwin();
        system("clear");
        printf("See ya!");
        exit(1);
        break;
      } else if (c == 'r') {
        delwin(gameWin);
        endwin();
        break;
      }
    }
  }
  
  
}

void gameLoop(snake *snakePlayer, WINDOW *gameWin, float windowSize, items *powerups) {
  int direction = 1;
  int *speed, speedTimer, invisTimer;
  int *itemSpawner, itemSpawnerCounter;
  int keyDown;
  int height, width;
  bool *gameOver;
  bool *invisPtr;
  bool createNewTail = false;
  createNewTail = true;

  speed = (int *)malloc(sizeof(int));
  itemSpawner = (int *)malloc(sizeof(int));
  gameOver = (bool *)malloc(sizeof(bool));
  invisPtr = (bool *)malloc(sizeof(bool));
  *speed = 3;
  *invisPtr = false;
  *itemSpawner = (rand() % 5) + 5; 
  itemSpawnerCounter = 0;
  speedTimer = 0;
  *gameOver = false;

  //Enable keys
  keypad(gameWin, TRUE);
  nodelay(gameWin, TRUE);

  windowSize = 0.9;
  gameWin = changeWindowSize(gameWin, windowSize);
 
  while(1) {
    printScore(snakePlayer->score);
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
        powerups = useItemIfPos(snakePlayer, powerups, speed, gameWin, windowSize, &speedTimer, invisPtr);
        updatePlayer(snakePlayer);
        drawPlayer(snakePlayer, gameWin, invisPtr);
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
        powerups = useItemIfPos(snakePlayer, powerups, speed, gameWin, windowSize, &speedTimer, invisPtr);
        updatePlayer(snakePlayer);
        drawPlayer(snakePlayer, gameWin, invisPtr);
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
        powerups = useItemIfPos(snakePlayer, powerups, speed, gameWin, windowSize, &speedTimer, invisPtr);
        updatePlayer(snakePlayer);
        drawPlayer(snakePlayer, gameWin, invisPtr);
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
        powerups = useItemIfPos(snakePlayer, powerups, speed, gameWin, windowSize, &speedTimer, invisPtr);
        updatePlayer(snakePlayer);
        drawPlayer(snakePlayer, gameWin, invisPtr);
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
    } else if(*speed == 7 && speedTimer != 30) {
      speedTimer += 1;
    } else {
      *speed = 3;
      speedTimer = 0;
    }

    if(*invisPtr == true && invisTimer != 40) {
      invisTimer += 1;
    } else {
      *invisPtr = false;
      invisTimer = 0;
    }

    if(*gameOver == true) {
      mvprintw(19, 36, "GAME OVER");
      refresh();
      break;
    }
    refresh();    
  } 
}
