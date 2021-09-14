#include <time.h>





/**
 * Speeds: 
 * Slow: 12
 * Normal: 8
 * Fast: 5
 * Very-Fast: 3
 * Extreme: 1
 */
void timerFunc(int speed) {
  speed = speed * 50000000;
  clock_t start = clock();
  volatile unsigned sink;

  for(size_t i = 0; i < speed; i++) {
    sink++;
  }

  clock_t end = clock();
}