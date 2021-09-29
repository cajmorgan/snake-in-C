#include <stdbool.h>

//Snake struct
typedef struct player {
  int posX;
  int prevX;
  int posY;
  int prevY;
  int score;
  bool head;
  struct player *next;
  struct player *prev;
} snake;


snake *createPlayer(WINDOW *gameWin);
void drawPlayer(snake *snakePlayer, WINDOW *gameWin, bool *invisPtr, bool *goThroughPtr); 
void removePlayer(snake *snakePlayer, WINDOW *gameWin);
snake *createTail(snake *snakePlayer);
void updatePlayer(snake *snakePlayer);
void updatePrev(snake *snakePlayer);
bool checkTail(snake *snakePlayer, bool createNewTail);
snake *selfBite(snake *snakePlayer, bool *gameOver, bool *goThroughPtr);