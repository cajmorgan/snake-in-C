#include <stdio.h>

void timerFunc(int speed);
void changeSpeed(int *speed, int newSpeed, int *speedTimer);
void createHighScoreFile();
void updateHighScoreFile(int *scoreArr);
char **getHighScoresFromFile();
void checkIfHighScore(int playerScore, char **scoreArr);