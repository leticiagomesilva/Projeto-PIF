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

typedef struct objeto{
  char nome[50];

  double x;
  double y;

  double incX;
  double incY;
}objeto;

double x = 20, y = MAXY-1;

void printObjeto(double nextX, double nextY, char *objeto){
  screenSetColor(CYAN, DARKGRAY);
  screenGotoxy(x, y);
  
  for (int i = 0; i < strlen(objeto); i++) printf(" ");
  
  x = nextX;
  y = nextY;
  
  screenGotoxy(x, y);
  printf("%s", objeto);
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


  screenInit(1);
  keyboardInit();
  timerInit(50);

  printObjeto(x, y, "Chick");
  
  screenUpdate();
  
  while (ch != 10) //enter
  {
    // Handle user input
    if (keyhit() && y >= MAXY-1){
        ch = readch();
        printScore(score);
        screenUpdate();
    }

    // Update game state (move elements, verify collision, etc)
    if (timerTimeOver() == 1){
      chick.y = chick.y + chick.incY;

      // Pulo do Chick
      if (ch == 32 || chick.y <= 10) chick.incY = -chick.incY, ch = 0, score++;

      // Chão
      if (chick.y >= MAXY-1) chick.y = MAXY-1;

      printScore(score);
      printObjeto(chick.x, chick.y, "Chick");

      screenUpdate();
    }
  }

    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;
}
