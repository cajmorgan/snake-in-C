#include <ncurses.h>
#include "player.h"
#include <stdbool.h>

#define HEADCOLOR 1
#define TAILCOLOR 2


snake *createPlayer() {
  snake *snakePlayer = NULL;
    snakePlayer = (snake *)malloc(sizeof(snake));
    if(snakePlayer == NULL)
      return NULL;
  
  snakePlayer->head = true;
  snakePlayer->posX = 40;
  snakePlayer->posY = 20;
  snakePlayer->score = 0;
  snakePlayer->next = NULL;
  snakePlayer->prev = NULL;

  // snakePlayer->next->posX = 41;
  // snakePlayer->next->posY = 21;
  // snakePlayer->next->prev = snakePlayer;

  return snakePlayer;
}


void drawPlayer(snake *snakePlayer, WINDOW *gameWin) {
  snake *current = snakePlayer;
  while(current != NULL) {
    if(current->head == true) {
      wattrset(gameWin, COLOR_PAIR(HEADCOLOR));
      mvwprintw(gameWin, current->posY, current->posX, "%c", '*');
      wattroff(gameWin, COLOR_PAIR(HEADCOLOR));
    } else {
      wattrset(gameWin, COLOR_PAIR(TAILCOLOR));
      mvwprintw(gameWin, current->posY, current->posX, "%c", '*');
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

snake *selfBite(snake *snakePlayer) {
  snake *tail = snakePlayer;

  while(tail->next != NULL) {
    if(snakePlayer->posX == tail->next->posX && snakePlayer->posY == tail->next->posY) {
      if(tail->next->next != NULL) {
         tail->next->next = NULL;
         free(tail->next->next);
      }
     
      break;
    } 
    tail = tail->next;
  }

  return snakePlayer;
}

void removeTail();