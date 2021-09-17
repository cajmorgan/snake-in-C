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
items *useItemIfPos(snake *snakePlayer, items *powerups, int *speed);
items *removeItemByPos(items **powerups, items *itemToRemove);
void addItem(items *powerups, int item, WINDOW *gameWin, snake *snakePlayer, float winSize);
void randomItemSpawner(items *powerups, WINDOW *gameWin, snake *snakePlayer, float windowSize);
