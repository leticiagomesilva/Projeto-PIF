/**
 * main.h
 * Created on Aug, 23th 2023
 * Author: Tiago Barros
 * Based on "From C to C++ course - 2002"
*/

#include <string.h>

#include "screen.h"
#include "keyboard.h"
#include "timer.h"

int score = 0;
int margemX = 3;
int margemY = 1;

// Colors: BLACK, RED, GREEN, BROWN, BLUE, MAGENTA, CYAN, LIGHTGRAY,DARKGRAY, LIGHTRED, LIGHTGREEN, YELLOW, LIGHTBLUE, LIGHTMAGENTA, LIGHTCYAN, WHITE

typedef struct objeto{
  char nome[50];

  double x;
  double y;

  double incX;
  double incY;
}objeto;


void printObject(double nextX, double nextY, char *objeto, int color){
  screenSetColor(color, DARKGRAY);
  screenGotoxy(nextX, nextY);
  printf("%s", objeto);
}

void deleteObjects(){
  for (int i = 9; i < MAXY; i++){
    screenGotoxy(MINX+1, i);
    for (int j = 0; j < 77; j++){
      printf(" ");
    }
  }
}

void printScore(int ch){
  screenSetColor(YELLOW, DARKGRAY);
  screenGotoxy(35, 4);
  printf("SCORE:");
  
  screenGotoxy(43, 4);
  printf("         ");

  screenGotoxy(43, 4);
  printf("%d ", score);
}

int main(){
  static int ch = 0;

  // Chick
  objeto chick;
  chick.x = 20.0;
  chick.y = MAXY-1;
  chick.incY = 1.5;

  // Cerca
  objeto cerca;
  cerca.x = 60;
  cerca.y = MAXY-1;
  cerca.incX = -0.8;


  screenInit(1);
  keyboardInit();
  timerInit(50);

  //printObject(x, y, "Chick");
  
  screenUpdate();
  
  while (ch != 10) //enter
  {
    // Handle user input
    if (keyhit() && chick.y >= MAXY-1){
        ch = readch();
        printScore(score);
        screenUpdate();
    }

    // Update game state (move elements, verify collision, etc)
    if (timerTimeOver() == 1){
      // Limpar tela
      deleteObjects();
      
      // Movimento dos objetos
      chick.y = chick.y + chick.incY;
      cerca.x = cerca.x + cerca.incX;

      // Pulo do Chick
      if (ch == 32 || chick.y <= 10) chick.incY = -chick.incY, ch = 0;

      // Chão
      if (chick.y >= MAXY-1) chick.y = MAXY-1;
      if (cerca.y >= MAXY-1) cerca.y = MAXY-1;

      // Loop de obstaculos
      if (cerca.x <= MINX+1) cerca.x = MAXX-6, score++, cerca.incX -= 0.1;

      // Colisões
      if (abs(chick.x - cerca.x) <= margemX && abs(chick.y - cerca.y) <= margemY){
        cerca.incX = 0;
        printObject(35, 12, "GAME OVER", 1);
      }

      // Recomeçar
      if (cerca.incX == 0 && ch == 114){
        cerca.incX = -0.8;
        cerca.x = 60;
        deleteObjects();
        score = 0;
        ch = 0;
      }
      // Prints
      printScore(score);
      printObject(chick.x, chick.y, "Chick", 6);
      printObject(cerca.x, cerca.y, "Cerca", 5);

      screenUpdate();
    }
  }

    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;
}
