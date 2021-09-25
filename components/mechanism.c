#include <time.h>
#include <pthread.h>
#include "mechanism.h"
#include <math.h>




/**
 * Speeds: 
 * Slow: 12
 * Normal: 8
 * Fast: 5
 * Very-Fast: 3
 * Extreme: 1
 */

int ex = 1;
void timerFunc(int speed) {
  speed = speed * 50000000;
  clock_t start = clock();
  volatile unsigned sink;

  for(size_t i = 0; i < speed; i++) {
    sink++;
  }

  clock_t end = clock();
}

void changeSpeed(int *speed, int newSpeed, int *speedTimer) {
  *speed = newSpeed;
  *speedTimer = 0;
}

void createHighScoreFile() {
  FILE *fp = fopen("./snake/scores.dat", "rb");
  if(fp == NULL) {
    system("mkdir ~/snake");
    fp = fopen("./snake/scores.dat", "a+");
    char *scoreInitiater = (char *)malloc(sizeof(char) * 26);
    scoreInitiater = "0000\n0000\n0000\n0000\n0000";
    fwrite(scoreInitiater, sizeof(char), 26, fp);
    fclose(fp);
  }

}

void updateHighScoreFile(int *scoreArr) {
  //Convert scoreArr to correct format and replace filecontent with it: 0000\n0000\n0000\n0000\n0000
  //Create dynamic 2D-Array
  char **arr;
  int column = 0, counter = 0;
  arr = (char **)malloc(sizeof(char *) * 5);
  for (int i = 0; i <= 5; i++) {
    arr[i] = (char *)malloc(sizeof(char) * 5);
  }

  for(int row = 0; row < 5; row++) {
    while(scoreArr[row] > -1) {
      if(scoreArr[row] >= 1000 || counter == 0) {
        if(scoreArr[row] < 1000) {
          arr[row][column] = '0';
        } else {
          arr[row][column] = floor(scoreArr[row] / 1000) + '0';
          scoreArr[row] -= (floor(scoreArr[row] / 1000) * 1000);
        }
        
        counter += 1;
        column += 1;
      } else if (scoreArr[row] >= 100 || counter == 1) {
        if(scoreArr[row] < 100) {
          arr[row][column] = '0';
        } else {
          arr[row][column] = floor(scoreArr[row] / 100) + '0';
          scoreArr[row] -= (floor(scoreArr[row] / 100) * 100);
        }

        counter += 1;
        column += 1;
      } else if (scoreArr[row] >= 10 || counter == 2) {
         if(scoreArr[row] < 10) {
          arr[row][column] = '0';
        } else {
          arr[row][column] = floor(scoreArr[row] / 10) + '0';
          scoreArr[row] -= (floor(scoreArr[row] / 10) * 10);
        }

        
        counter += 1;
        column += 1;
      } else if (scoreArr[row] >= 1 || counter == 3) {
         if(scoreArr[row] < 1) {
          arr[row][column] = '0';
        } else {
          arr[row][column] = scoreArr[row] + '0';
          scoreArr[row] -= scoreArr[row];
        }

        counter += 1;
        column += 1;
      } else {
        arr[row][column] = '\n';
        scoreArr[row] = -1;
        column = 0;
        counter = 0;
      }
    }
  }

  printf("%s", arr[4]);

}

void checkIfHighScore(int playerScore, char **scoreArr) {
  //Create function to convert every column to correct integer and put in new array
  int convertToInt, counter = 0, adder = 0;
  static int scoreArrIntegers[5];

  playerScore = 2323;

  //Convert previous scores to integers
  for (int row = 0; row < 5; row++) {
    for (int column = 0; column < 5; column++) {
        if(counter != 4) {
          convertToInt = scoreArr[row][column] - '0';
          switch(column) {
            case 0: 
              convertToInt = convertToInt * 1000;
              break;
            case 1: 
              convertToInt = convertToInt * 100;
              break;
            case 2: 
              convertToInt = convertToInt * 10;
              break;
            case 3: 
              convertToInt = convertToInt * 1;
              break;
          };
          adder += convertToInt;
          counter += 1;
        } else {
          scoreArrIntegers[row] = adder;
          counter = 0;
          adder = 0;
        }
    }
  }

  for(int i = 0; i < 5; i++) {
    if(playerScore > scoreArrIntegers[i]) {
      scoreArrIntegers[i] = playerScore;
      updateHighScoreFile(scoreArrIntegers);
      scoreArr = NULL;
      free(scoreArr);
      break;
    } else {
      scoreArr = NULL;
      free(scoreArr);
    }
  }



}

char **getHighScoresFromFile() {
  FILE *fp = fopen("./snake/scores.dat", "r");

  //Create dynamic 2D-Array
  static char **arr;
  arr = (char **)malloc(sizeof(char *) * 5);
  for (int i = 0; i <= 5; i++) {
    arr[i] = (char *)malloc(sizeof(char) * 4);
  }

  int c, counter = 0, index = 0;
  while((c = fgetc(fp)) != EOF) {
    arr[index][counter] = c;
    counter += 1;
    if(counter % 5 == 0) {
      index += 1;
      counter = 0;
    }
  }

  fclose(fp);
  
  return arr;
}


