#include <ncurses.h>
#include "items.h"



items *initiateItems(WINDOW *gameWin, snake *snakePlayer, float winSize) 
{
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

int randomItemPos(char isWhat, WINDOW *gameWin, snake *snakePlayer, float winSize) 
{
  int width, height, random, widthReduced, heightReduced;
  getmaxyx(stdscr, height, width);
  widthReduced = (width * winSize) - 2;
  heightReduced = (height * winSize) - 2;
  //Implement random with modulus remainder of height/width, 
  // should probably check position of player as well

  if(isWhat == 'x') {
    random = (rand() % widthReduced);
    if(random % 2 != 0) {
      random = random - 1;
    }
    
    if(random == 0) {
      random += 2;
    }

    return random;
  } else if (isWhat == 'y') {
    random = (rand() % heightReduced);
    if(random == 0) {
      random += 2;
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
 * Invisibility - Blinking snake
 * Nuke - Delete all items
 * 
 * For timing the powerups that are continuos, try create a new thread
 */


items *useItemIfPos(snake *snakePlayer, items *powerups, int *speed, WINDOW *gameWin, float winSize, int *speedTimer, bool *invisPtr, bool *goThroughPtr) 
{
  items *currentItem = powerups;
  while(currentItem != NULL) {
    if(currentItem->posX == snakePlayer->posX && currentItem->posY == snakePlayer->posY) {
      switch(currentItem->item) {
        case 0:
          createTail(snakePlayer);
          snakePlayer->score += 1;
          break;
        case 1:
          createTail(snakePlayer);
          snakePlayer->score += 1;
          break;
        case 2:
          createTail(snakePlayer);
          snakePlayer->score += 1;
          break;
        case 3:
          //Superspeed
          changeSpeed(speed, 1, speedTimer);
          break;
        case 4:
          //Slowmotion
          changeSpeed(speed, 7, speedTimer);
          break;
        case 5:
          //Nuke
          powerups = removeAllItems(powerups, gameWin);
          break;
        case 6:
          *invisPtr = true;
          break;
        case 7:
          *goThroughPtr = true;
          break;
      }
      powerups = removeItemByPos(&powerups, currentItem, gameWin, snakePlayer, winSize);
      break;
    }
    currentItem = currentItem->next;
  }

  return powerups;
}

void addItem(items *powerups, int item, WINDOW *gameWin, snake *snakePlayer, float winSize) 
{
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

items *removeItemByPos(items **powerups, items *itemToRemove, WINDOW *gameWin, snake *snakePlayer, float winSize) 
{
  items *current, *second;

  current = *powerups;
  second = (*powerups)->next;
  if(current->posX == itemToRemove->posX && current->posY == itemToRemove->posY) {
    if(current->next == NULL) {
      addItem(*powerups, 0, gameWin, snakePlayer, winSize);
      second = (*powerups)->next;
      drawItems(*powerups, gameWin);
    }
    free(*powerups);
    *powerups = NULL;
    *powerups = second;
  } else {
    while(second != NULL) {
      if(current->next->posX == itemToRemove->posX && current->next->posY == itemToRemove->posY) {
        if(second->next != NULL) {
          second = second->next;
          free(current->next);
          current->next = NULL;
          current->next = second;
          second->next = current->next->next;
          break;
        } else if (second->next == NULL) {
          free(current->next);
          current->next = NULL;
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

items *removeAllItems(items *powerups, WINDOW *gameWin) 
{
  items *current = powerups;
 
  while(powerups->next != NULL) {
    if(powerups->next->next == NULL) {
      free(powerups->next);
      powerups->next = NULL;
    } else {
      while(current->next->next != NULL) {
      current = current->next;
      if(current->next->next == NULL) {
        free(current->next);
        current->next = NULL;
        current = powerups;
      }
    }
    }
   
    
  }
  
  wclear(gameWin);
  drawItems(powerups, gameWin);
  wborder(gameWin, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
  return powerups;
} 

void drawItems(items *powerups, WINDOW *gameWin) 
{
  items *current = powerups;
  wattrset(gameWin, A_BOLD);

  while(current != NULL) {
    
    switch(current->item) {
      case 0:
        wattron(gameWin, COLOR_PAIR(FOODCOLOR));
        mvwprintw(gameWin, current->posY, current->posX, "%c", '^');
        break;
      case 1:
        wattron(gameWin, COLOR_PAIR(FOODCOLOR));
        mvwprintw(gameWin, current->posY, current->posX, "%c", '^');
        break;
      case 2:
        wattron(gameWin, COLOR_PAIR(FOODCOLOR));
        mvwprintw(gameWin, current->posY, current->posX, "%c", '^');
        break;
      case 3:
        wattron(gameWin, A_BOLD);
        wattron(gameWin, COLOR_PAIR(1));
        mvwprintw(gameWin, current->posY, current->posX, "%c", 'S');
        break;
      case 4:
        wattron(gameWin, A_BOLD);
        wattron(gameWin, COLOR_PAIR(SLOWMOCOLOR));
        mvwprintw(gameWin, current->posY, current->posX, "%c", 'S');
        break;
      case 5:
        wattron(gameWin, A_BOLD);
        wattron(gameWin, A_BLINK);
        wattron(gameWin, COLOR_PAIR(NUKECOLOR));
        mvwprintw(gameWin, current->posY, current->posX, "%c", 'X');
        wattroff(gameWin, A_BLINK);
        break;
      case 6:
        wattron(gameWin, A_BOLD);
        wattron(gameWin, A_BLINK);
        wattron(gameWin, COLOR_PAIR(INVISCOLOR));
        mvwprintw(gameWin, current->posY, current->posX, "%c", '@');
        wattroff(gameWin, A_BLINK);
        break;
      case 7:
        wattron(gameWin, A_BOLD);
        wattron(gameWin, COLOR_PAIR(GOTHROUGHCOLOR));
        mvwprintw(gameWin, current->posY, current->posX, "%c", '&');
        break;
    }
    wrefresh(gameWin);
    current = current->next;
  }
}

void randomItemSpawner(items *powerups, WINDOW *gameWin, snake *snakePlayer, float windowSize) 
{
  int random = rand() % 8;
  addItem(powerups, random, gameWin, snakePlayer, windowSize);
  drawItems(powerups, gameWin);
}


// items *createItem(items *powerups, int item) {
//   //Push onto powerups

//   return powerups;
// }

