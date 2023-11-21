/**
 * main.h
 * Created on Aug, 23th 2023
 * Author: Tiago Barros
 * Based on "From C to C++ course - 2002"
*/

#include <string.h>
#include <stdlib.h>
#include <time.h>

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

typedef struct node{
  int valor;
  struct node *next;
}lista;


float randomInc(){
  srand(time(0));
  float random = rand() % 120 + 1;

  float inc;

  if (random >= 10) inc = random / 1000;
  else inc = random / 100;

  if (random <= 60) return inc;
  else return -inc;
}

void addNodeDesc(lista **head, int var){
  lista *n = *head;
  lista *novo = (lista *)malloc(sizeof(lista));

  novo->valor = var;
  novo->next = NULL;

  if (*head == NULL) {
    *head = novo;
  } else if (n->valor < var) { 
    novo->next = *head;
    *head = novo;
  } else {
    while (n->next != NULL && n->next->valor > var) { 
      n = n->next;
    }
    if (n->next == NULL) {
      novo->next = NULL;
      n->next = novo;
    } else {
      novo->next = n->next;
      n->next = novo;
    }
  }
}


void printObject(double nextX, double nextY, char *objeto, int color){
  screenSetColor(color, DARKGRAY);
  screenGotoxy(nextX, nextY);
  printf("%s", objeto);
}

void deleteObjects(){
  int lim = 0;

  for (int i = 8; i < MAXY; i++){
    screenGotoxy(MINX+1, i);

    if (i < MAXY-2) lim = 44;
    else lim = 77;

    for (int j = 0; j < lim; j++){
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

void printHighScore(lista *head, int score){

  screenSetColor(YELLOW, DARKGRAY);
  screenGotoxy(30, 6);
  printf("HIGH SCORE:");

  screenGotoxy(43, 6);
  printf("                    ");

  screenGotoxy(43, 6);
  if (head == NULL || score > head->valor) printf("%d", score);
  else printf("%d", head->valor);

}

void printList(lista *head){
  struct node *n = head;
  while(n!= NULL){
    printf(" %d ",n->valor);
    n = n -> next;
  }
  printf("\n");
}

int main(){
  static int ch = 0;
  int score = 0, margemX = 7, margemY = 0, colisao = 0, addHighscore = 1;
  double gravidade = 0.22;
  lista *head = NULL;

  // Chick
  objeto chick_corpo; // Parte de baixo
  chick_corpo.x = 20.0;
  chick_corpo.y = MAXY-1;
  chick_corpo.incY = 0;

  objeto chick_cara; // Parte do meio
  chick_cara.x = 20.0;
  chick_cara.y = MAXY-2;
  chick_cara.incY = 0;

  objeto chick_cabeca; // Parte de cima
  chick_cabeca.x = 20.0;
  chick_cabeca.y = MAXY-3;
  chick_cabeca.incY = 0;

  // Cerca
  objeto cerca1; // Parte de baixo
  cerca1.x = 60;
  cerca1.y = MAXY-1;
  cerca1.incX = -1.0;

  objeto cerca2; // Parte de cima
  cerca2.x = 60;
  cerca2.y = MAXY-2;
  cerca2.incX = -1.0;

  // Estado inicial do jogo
  screenInit(1);
  keyboardInit();
  timerInit(50);
  screenUpdate();

  while (ch != 10) // Enter
  {
    // Input do usuário
    if (keyhit() && chick_corpo.y >= MAXY-3){
        ch = readch();
        printScore(score);
        screenUpdate();
    }

    // Atualizar o estado do jogo
    if (timerTimeOver() == 1){

      // Limpar tela
      deleteObjects();

      // Movimento dos objetos
      chick_corpo.y = chick_corpo.y + chick_corpo.incY;
      chick_cara.y = chick_cara.y + chick_cara.incY;
      chick_cabeca.y = chick_cabeca.y + chick_cabeca.incY;

      cerca1.x = cerca1.x + cerca1.incX;
      cerca2.x = cerca2.x + cerca2.incX;

      // Gravidade
      chick_corpo.incY = chick_corpo.incY + gravidade;
      chick_cara.incY = chick_cara.incY + gravidade;
      chick_cabeca.incY = chick_cabeca.incY + gravidade;

      // Pulo do Chick
      if (ch == 32 && chick_corpo.y >= MAXY-1) chick_corpo.incY = -2.2, chick_cara.incY = -2.2, chick_cabeca.incY = -2.2, ch = 0;

      // Chão
      if (chick_corpo.y >= MAXY-1) chick_corpo.y = MAXY-1;
      if (chick_cara.y >= MAXY-2) chick_cara.y = MAXY-2;
      if (chick_cabeca.y >= MAXY-3) chick_cabeca.y = MAXY-3;

      if (cerca1.y >= MAXY-1) cerca1.y = MAXY-1;
      if (cerca2.y >= MAXY-2) cerca2.y = MAXY-2;

      // Loop de obstaculos
      float randinc = randomInc();
      if (cerca1.x <= MINX+1) cerca1.x = MAXX-8, score++, cerca1.incX += randinc;
      if (cerca2.x <= MINX+1) cerca2.x = MAXX-8, cerca2.incX += randinc;

      // Colisões
      if ((abs((int)chick_corpo.x - (int)cerca1.x) <= margemX && abs((int)chick_corpo.y - (int)cerca1.y) <= margemY) || (abs((int)chick_corpo.x - (int)cerca2.x) <= margemX && abs((int)chick_corpo.y - (int)cerca2.y) <= margemY)){
        colisao = 1;

        cerca1.incX = 0;
        cerca2.incX = 0;

        chick_corpo.incY = 0;
        chick_cara.incY = 0;
        chick_cabeca.incY = 0;
        gravidade = 0;

        if (addHighscore == 1) addNodeDesc(&head, score), addHighscore = 0;

        if (abs((int)chick_corpo.y - (int)cerca2.y) <= margemY){
          chick_corpo.y = cerca2.y-1;
          chick_cara.y = cerca2.y-2;
          chick_cabeca.y = cerca2.y-3;
        }
        else if (abs((int)chick_corpo.x - (int)cerca1.x) <= margemX){
          chick_corpo.x = cerca1.x-margemX;
          chick_cara.x = cerca1.x-margemX;
          chick_cabeca.x = cerca1.x-margemX;
        }
      }

      // GAME OVER
      if (colisao == 1){
        printObject(35, 12, "GAME OVER", 1);
      } 


      // Recomeçar e HIGH SCORE
      if (cerca1.incX == 0 && ch == 114){
        colisao = 0;
        ch = 0;
        score = 0;

        addHighscore = 1;

        cerca1.incX = -1.0;
        cerca2.incX = -1.0;

        chick_corpo.incY = 0;
        chick_cara.incY = 0;
        chick_cabeca.incY = 0;

        gravidade = 0.22;

        cerca1.x = 60;
        cerca2.x = 60;

        chick_corpo.y = MAXY-1;
        chick_cara.y = MAXY-2;
        chick_cabeca.y = MAXY-3;
      }

      // Prints
      printScore(score);
      printHighScore(head, score);

      //screenGotoxy(54, 4);
      //printf("%lf", cerca1.incX);

      printObject(chick_cabeca.x, chick_cabeca.y, " _/\\_ ", 6);
      printObject(chick_cara.x, chick_cara.y, "(  o )>", 6);
      printObject(chick_corpo.x, chick_corpo.y, "(  / )", 6);

      printObject(cerca1.x, cerca1.y, "|--|--|", 5);
      printObject(cerca2.x, cerca2.y, "|--|--|", 5);

      // Atualização da tela
      screenUpdate();
    }
  }

  keyboardDestroy();
  screenDestroy();
  timerDestroy();

  printf("Scores da partida (em ordem decrescente): ");
  printList(head);

  return 0;
}