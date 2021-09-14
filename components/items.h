typedef struct items {
  int item;
  int posX;
  int posY;
  struct items *next;
} items;

items *initiateItems(WINDOW *gameWin, snake *player);
void drawItems(items *powerups, WINDOW *gameWin);
items *createItem(items *powerups, int item);
int randomItemPos(char isWhat, WINDOW *gameWin, snake *player);
items *useItemIfPos(snake *snakePlayer, items *powerups);
items *removeItemByPos(items **powerups, items *itemToRemove);
