#include <stdlib.h>
#include "./components/player.c"
#include "./components/mechanism.c"
#include "./components/UI.c"
#include "./components/items.c"

int game();
void gameLoop(snake *snakePlayer, WINDOW *gameWin, float windowSize, items *powerups);