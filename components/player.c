#include "player.h"


snake *createPlayer() {
  snake *snakePlayer = NULL;
    snakePlayer = (snake *)malloc(sizeof(snake));
    if(snakePlayer == NULL)
      return NULL;

  snakePlayer->posX = 40;
  snakePlayer->posY = 20;
  snakePlayer->score = 0;
  snakePlayer->next = NULL;
  snakePlayer->prev = NULL;

  return snakePlayer;
}


void drawPlayer(snake *snakePlayer, WINDOW *gameWin) {
  //Loop through snakePlayer struct untill NULL and print by pos
  mvwprintw(gameWin, snakePlayer->posY, snakePlayer->posX, "%c", '*');
  wrefresh(gameWin);

}

void removePlayer(snake *snakePlayer, WINDOW *gameWin) {
  snake *current = snakePlayer;
  while(current != NULL) {
    mvwprintw(gameWin, current->posY, current->posX, "%c", ' ');
    current = current->next;
  }
  wrefresh(gameWin);
}