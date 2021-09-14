#include <ncurses.h>
#include "items.h"


#define FOODCOLOR 3

items *initiateItems(WINDOW *gameWin, snake *snakePlayer) {
  items *powerups = NULL;
  powerups = (items *)malloc(sizeof(items));
  if(powerups == NULL)
    return NULL;

  powerups->item = 0;
  powerups->posX = randomItemPos('x', gameWin, snakePlayer);
  powerups->posY = randomItemPos('y', gameWin, snakePlayer);
  powerups->next = NULL;

  return powerups;
}

int randomItemPos(char isWhat, WINDOW *gameWin, snake *snakePlayer) {
  int width, height, random;
  getmaxyx(gameWin, height, width);

  //Implement random with modulus remainder of height/width, 
  // should probably check position of player as well
  if(isWhat == 'x') {
    random = (rand() % width) + 1;
    if(random > width || random % 2 != 0) {
      random = random - 1;
    }

    return random;
  } else if (isWhat == 'y') {
    random = (rand() % height) + 2;
    if(random > height) {
      random = random - 4;
    }
    
    return random;
  }

  return 0;
}


/**
 * Food - 0
 * Superspeed
 * Go-through  
 * Slowmotion
 * Invert Controls
 * Invisibility
 * Nuke
 * 
 * 
 */


items *useItemIfPos(snake *snakePlayer, items *powerups) {
  items *currentItem = powerups;
  while(currentItem != NULL) {
    if(currentItem->posX == snakePlayer->posX && currentItem->posY == snakePlayer->posY) {
      switch(currentItem->item) {
        case 0:
          createTail(snakePlayer);
          break;
      }
      powerups = removeItemByPos(&powerups, currentItem);
      break;
    }
    currentItem = currentItem->next;
  }

  return powerups;
}

items *removeItemByPos(items **powerups, items *itemToRemove) {
  items *current, *second;

  current = *powerups;
  second = (*powerups)->next;
  if(current->posX == itemToRemove->posX && current->posY == itemToRemove->posY) {
    *powerups = NULL;
    free(*powerups);
    *powerups = second;
  } else {
    //Write loop to handle multiple objects
  }
  

  return *powerups;
}

void drawItems(items *powerups, WINDOW *gameWin) {
  items *current = powerups;
  wattrset(gameWin, A_BOLD);

  while(current != NULL) {
    
    switch(current->item) {
      case 0:
        wattron(gameWin, COLOR_PAIR(FOODCOLOR));
        mvwprintw(gameWin, current->posY, current->posX, "%c", '^');
        break;
    }
    current = current->next;
  }
}


// items *createItem(items *powerups, int item) {
//   //Push onto powerups

//   return powerups;
// }

