/**
 * main.h
 * Created on Aug, 23th 2023
 * Author: Tiago Barros
 * Based on "From C to C++ course - 2002"
*/

#include <string.h>
#include <stdlib.h>

#include "screen.h"
#include "keyboard.h"
#include "timer.h"

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

void printScore(int points){
  screenSetColor(YELLOW, DARKGRAY);
  screenGotoxy(35, 4);
  printf("SCORE:");
  
  screenGotoxy(43, 4);
  printf("         ");

  screenGotoxy(43, 4);
  printf("%d ", points);
}

int main(){
  static int ch = 0;
  int score = 0;
  int margemX = 5;
  int margemY = 0;
  double gravidade = 0.22;
  int colisao = 0;

  // Chick
  objeto chick;
  chick.x = 20.0;
  chick.y = MAXY-1;
  chick.incY = 0;

  // Cerca
  objeto cerca1;
  cerca1.x = 60;
  cerca1.y = MAXY-1;
  cerca1.incX = -1.0;

  objeto cerca2;
  cerca2.x = 60;
  cerca2.y = MAXY-2;
  cerca2.incX = -1.0;


  screenInit(1);
  keyboardInit();
  timerInit(50);
  
  screenUpdate();
  
  while (ch != 10) //enter
  {
    // Handle user input
    if (keyhit() && chick.y >= MAXY-3){
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
      cerca1.x = cerca1.x + cerca1.incX;
      cerca2.x = cerca2.x + cerca2.incX;

      // Gravidade
      chick.incY = chick.incY + gravidade;

      // Pulo do Chick
      if (ch == 32 && chick.y >= MAXY-1) chick.incY = -2.0, ch = 0;

      // Chão
      if (chick.y >= MAXY-1) chick.y = MAXY-1;
      if (cerca1.y >= MAXY-1) cerca1.y = MAXY-1;
      if (cerca2.y >= MAXY-2) cerca2.y = MAXY-2;

      // Loop de obstaculos
      if (cerca1.x <= MINX+1) cerca1.x = MAXX-8, score++, cerca1.incX -= 0.1;
      if (cerca2.x <= MINX+1) cerca2.x = MAXX-8, cerca2.incX -= 0.1;

      // Colisões
      if ((abs((int)chick.x - (int)cerca1.x) <= margemX && abs((int)chick.y - (int)cerca1.y) <= margemY) || (abs((int)chick.x - (int)cerca2.x) <= margemX && abs((int)chick.y - (int)cerca2.y) <= margemY)){
        colisao = 1;
        
        cerca1.incX = 0;
        cerca2.incX = 0;
        
        chick.incY = 0;
        gravidade = 0;

        if (abs((int)chick.y - (int)cerca2.y) <= margemY) chick.y = cerca2.y-1;
        else if (abs((int)chick.x - (int)cerca1.x) <= margemX) chick.x = cerca1.x-5;
      }

      // GAME OVER
      if (colisao == 1) printObject(35, 12, "GAME OVER", 1);

      // Recomeçar
      if (cerca1.incX == 0 && ch == 114){
        colisao = 0;
        
        cerca1.incX = -1.0;
        cerca2.incX = -1.0;
        
        chick.incY = 0;
        gravidade = 0.2;
        
        cerca1.x = 60;
        cerca2.x = 60;
        
        deleteObjects();
        score = 0;
        ch = 0;
      }
      
      // Prints
      printScore(score);
      
      printObject(chick.x, chick.y, "Chick", 6);
      
      printObject(cerca1.x, cerca1.y, "|--|--|", 5);
      printObject(cerca2.x, cerca2.y, "|--|--|", 5);

      // Atualização da tela
      screenUpdate();
    }
  }

  keyboardDestroy();
  screenDestroy();
  timerDestroy();

  return 0;
}