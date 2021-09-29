typedef struct items {
  int item;
  int posX;
  int posY;
  struct items *next;
} items;

items *initiateItems(WINDOW *gameWin, snake *snakePlayer, float winSize);
void drawItems(items *powerups, WINDOW *gameWin);
items *createItem(items *powerups, int item);
int randomItemPos(char isWhat, WINDOW *gameWin, snake *snakePlayer, float winSize);
items *useItemIfPos(snake *snakePlayer, items *powerups, int *speed, WINDOW *gameWin, float winSize, int *speedTimer, bool *invisPtr, bool *goThroughPtr);
items *removeItemByPos(items **powerups, items *itemToRemove, WINDOW *gameWin, snake *snakePlayer, float winSize);
void addItem(items *powerups, int item, WINDOW *gameWin, snake *snakePlayer, float winSize);
void randomItemSpawner(items *powerups, WINDOW *gameWin, snake *snakePlayer, float windowSize);
items *removeAllItems(items *powerups, WINDOW *gameWin);