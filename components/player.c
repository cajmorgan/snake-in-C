#include <ncurses.h>
#include <stdbool.h>
#include "player.h"

#define HEADCOLOR 1
#define TAILCOLOR 2


snake *createPlayer(WINDOW *gameWin) {
  snake *snakePlayer = NULL;
  int height, width;
  snakePlayer = (snake *)malloc(sizeof(snake));
  if(snakePlayer == NULL)
    return NULL;

  getmaxyx(stdscr, height, width);
  
  snakePlayer->head = true;
  snakePlayer->posX = width / 2;
  snakePlayer->posY = height / 2;
  snakePlayer->score = 0;
  snakePlayer->next = NULL;
  snakePlayer->prev = NULL;

  return snakePlayer;
}


void drawPlayer(snake *snakePlayer, WINDOW *gameWin) {
  snake *current = snakePlayer;
  while(current != NULL) {
    if(current->head == true) {
      wattrset(gameWin, COLOR_PAIR(HEADCOLOR));
      wattron(gameWin, A_BOLD);
      mvwaddch(gameWin, current->posY, current->posX, ACS_DIAMOND);
      // mvwprintw(gameWin, current->posY, current->posX, "%c", '*');
      wattroff(gameWin, COLOR_PAIR(HEADCOLOR));
    } else {
      wattrset(gameWin, COLOR_PAIR(TAILCOLOR));
      mvwaddch(gameWin, current->posY, current->posX, ACS_DIAMOND);
      // mvwprintw(gameWin, current->posY, current->posX, "%c", '*');
      wattroff(gameWin, COLOR_PAIR(TAILCOLOR));
    }
    current = current->next;
    wrefresh(gameWin);
  }
}

void updatePlayer(snake *snakePlayer) {
  snake *current = snakePlayer;

  while(current->next != NULL) {
    current->next->posX = current->prevX;
    current->next->posY = current->prevY;
    current = current->next;
  }
}

void updatePrev(snake *snakePlayer) {
  snake *current = snakePlayer;
  while(current != NULL) {
    current->prevY = current->posY;
    current->prevX = current->posX;
    current = current->next;
  }
}

void removePlayer(snake *snakePlayer, WINDOW *gameWin) {
  snake *current = snakePlayer;
  while(current != NULL) {
    mvwprintw(gameWin, current->posY, current->posX, "%c", ' ');
    current = current->next;
    wrefresh(gameWin);
  }
}

snake *createTail(snake *snakePlayer) {
  snake *tail = snakePlayer;
  while(tail->next != NULL) {
    tail = tail->next;
  }
  tail->next = (snake *)malloc(sizeof(snake));
  tail->next->posX = snakePlayer->prevX;
  tail->next->posY = snakePlayer->prevY;
  tail->next->prev = tail;
  tail->next->next = NULL;
  tail->next->head = false;

  return snakePlayer;
}

bool checkTail(snake *snakePlayer, bool createNewTail) {
  if(createNewTail == true) {
    snakePlayer = createTail(snakePlayer);
    createNewTail = false;
  }

  return createNewTail;
}

snake *selfBite(snake *snakePlayer, bool *gameOver) {
  snake *tail = snakePlayer;

  while(tail->next != NULL) {
    if(snakePlayer->posX == tail->next->posX && snakePlayer->posY == tail->next->posY) {
      *gameOver = true;
      //If you want to eat your tail instead:
      // if(tail->next->next != NULL) {
      //    tail->next->next = NULL;
      //    free(tail->next->next);
      // }
      break;
    } 
    tail = tail->next;
  }

  return snakePlayer;
}
