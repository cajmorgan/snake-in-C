//Snake struct
typedef struct player {
  int posX;
  int posY;
  int score;
  struct player *next;
  struct player *prev;
} snake;


void drawPlayer(snake *snakePlayer, WINDOW *gameWin);
void removePlayer(snake *snakePlayer, WINDOW *gameWin);