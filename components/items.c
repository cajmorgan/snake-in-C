#include <ncurses.h>
#include "items.h"


#define FOODCOLOR 3

items *initiateItems(WINDOW *gameWin, snake *snakePlayer, float winSize) {
  items *powerups = NULL;
  powerups = (items *)malloc(sizeof(items));
  if(powerups == NULL)
    return NULL;

  powerups->item = 0;
  powerups->posX = randomItemPos('x', gameWin, snakePlayer, winSize);
  powerups->posY = randomItemPos('y', gameWin, snakePlayer, winSize);
  powerups->next = NULL;

  return powerups;
}

int randomItemPos(char isWhat, WINDOW *gameWin, snake *snakePlayer, float winSize) {
  int width, height, random, widthReduced, heightReduced;
  getmaxyx(stdscr, height, width);
  widthReduced = width * winSize;
  heightReduced = height * winSize;
  //Implement random with modulus remainder of height/width, 
  // should probably check position of player as well

  if(isWhat == 'x') {
    random = (rand() % widthReduced);
    if(random % 2 != 0) {
      random = random - 1;
    } 

    if(random == (width - widthReduced)) {
      random += 4;
    } else if (random == widthReduced) {
      random -= 4;
    }
    return random;
  } else if (isWhat == 'y') {
    random = (rand() % heightReduced);
    
    if(random == (height - heightReduced)) {
      random += 4;
    } else if (random == heightReduced) {
      random -= 4;
    }
    
    return random;
  }

  return 0;
}


/**
 * Food - 0
 * Superspeed
 * Go-through  
 * make window larger
 * make window smaller
 * Slowmotion
 * Invert Controls
 * Invisibility
 * Nuke
 * 
 * For timing the powerups that are continuos, try create a new thread
 */


items *useItemIfPos(snake *snakePlayer, items *powerups, int *speed) {
  items *currentItem = powerups;
  while(currentItem != NULL) {
    if(currentItem->posX == snakePlayer->posX && currentItem->posY == snakePlayer->posY) {
      switch(currentItem->item) {
        case 0:
          createTail(snakePlayer);
          break;
        case 1:
          changeSpeed(speed, 1);
          break;
      }
      powerups = removeItemByPos(&powerups, currentItem);
      break;
    }
    currentItem = currentItem->next;
  }

  return powerups;
}

void addItem(items *powerups, int item, WINDOW *gameWin, snake *snakePlayer, float winSize) {
  items *current = powerups;

  while(current->next != NULL) {
    current = current->next;
  }

  current->next = (items *)malloc(sizeof(items));
  current->next->item = item;
  current->next->posX = randomItemPos('x', gameWin, snakePlayer, winSize);
  current->next->posY = randomItemPos('y', gameWin, snakePlayer, winSize);
  current->next->next = NULL;
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
    while(second != NULL) {
      if(current->next->posX == itemToRemove->posX && current->next->posY == itemToRemove->posY) {
        if(second->next != NULL) {
          second = second->next;
          current->next = NULL;
          free(current->next);
          current->next = second;
          second->next = current->next->next;
          break;
        } else if (second->next == NULL) {
          current->next = NULL;
          free(current->next);
          break;
        }
        
       
        
        break;
      }
      current = current->next;
      second = second->next;
      
    }
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
      case 1:
        wattron(gameWin, A_BOLD);
        wattron(gameWin, COLOR_PAIR(1));
        mvwprintw(gameWin, current->posY, current->posX, "%c", 'S');
        break;
    }
    wrefresh(gameWin);
    current = current->next;
  }
}

void randomItemSpawner(items *powerups, WINDOW *gameWin, snake *snakePlayer, float windowSize) {
  int random = rand() % 2;
  addItem(powerups, random, gameWin, snakePlayer, windowSize);
  drawItems(powerups, gameWin);
}


// items *createItem(items *powerups, int item) {
//   //Push onto powerups

//   return powerups;
// }

