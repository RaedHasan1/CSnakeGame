#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/////////////////////////////////////////////////////////////////////////////
// CONSTANTS
#define BOARDSIZE 500
#define UP 8
#define DOWN 2
#define LEFT 4
#define RIGHT 6

/////////////////////////////////////////////////////////////////////////////
// FUNCTIONS
void BoardCreat(int boardSize, char board[BOARDSIZE][BOARDSIZE], int snakeX[],
                int snakeY[], int *foodX, int *foodY);
void BoardPrint(int boardSize, char board[BOARDSIZE][BOARDSIZE]);
void BoardUpdate(char board[BOARDSIZE][BOARDSIZE], int boardSize, int snakeX[],
                 int snakeY[], int *snakeSize, int *foodX, int *foodY);
int Move(char board[BOARDSIZE][BOARDSIZE], int snakeX[], int snakeY[],
         int *snakeSize, int move, int boardSize, int *foodX, int *foodY);
int foodUpdate(char board[BOARDSIZE][BOARDSIZE], int boardSize, int *foodX,
               int *foodY);

/////////////////////////////////////////////////////////////////////////////
// MAIN: DECLARE BOARD SIZE AND START THE GAME
int main() {

  int boardSize;
  char board[BOARDSIZE][BOARDSIZE];
  int move;
  int *foodX = malloc(sizeof(int));
  int *foodY = malloc(sizeof(int));
  int limits = 0;
  int *snakeSize = malloc(sizeof(int));
  int snakeX[BOARDSIZE];
  int snakeY[BOARDSIZE];
  int check = 0;
  *snakeSize = 1;

  printf("Please Insert Board Size:\n");
  scanf(" %d", &boardSize);
  BoardCreat(boardSize, board, snakeX, snakeY, foodX, foodY);
  BoardPrint(boardSize, board);

  while (limits == 0) {
    while (move != UP && move != DOWN && move != RIGHT && move != LEFT) {
      printf("ENTER YOUR MOVE: UP=8, DOWN=2, LEFT=4, RIGHT=6\n");
      scanf(" %d", &move);
    }
    limits =
        Move(board, snakeX, snakeY, snakeSize, move, boardSize, foodX, foodY);
    BoardPrint(boardSize, board);
    move = -1;
  }
  if (limits == 1) {
    printf("WELL DONE! BOARD IS FULL");
  }
  if (limits == 2) {
    printf("GAME OVER! WRONG MOVE");
  }

  return 0;
}

//////////////////////////////////////////////////////////////////////////////
// BULDING THE BOARD!!
void BoardCreat(int boardSize, char board[BOARDSIZE][BOARDSIZE], int snakeX[],
                int snakeY[], int *foodX, int *foodY) {

  int x, y;
  bool checkF = false;
  bool checkS = false;

  for (int i = 0; i <= boardSize + 1; i++) {
    for (int j = 0; j <= boardSize + 1; j++) {
      board[i][j] = ' ';
    }
  }

  for (int i = 0; i <= boardSize + 1; i++) {
    for (int j = 0; j <= boardSize + 1; j++) {
      if (j == 0 || j == boardSize + 1) {
        board[i][j] = '|';
      }
      if (i == 0 || i == boardSize + 1) {
        board[i][j] = '-';
      }
    }
  }

  while (checkF == false) {

    *foodX = rand() % boardSize;
    *foodY = rand() % boardSize;

    if (board[*foodX][*foodY] == ' ') {
      board[*foodX][*foodY] = '@';
      checkF = true;
    } else {
      checkF = false;
    }
  }

  while (checkS == false) {

    x = rand() % boardSize + 1;
    y = rand() % boardSize + 1;

    if (board[x][y] == ' ') {
      snakeX[0] = x;
      snakeY[0] = y;
      board[snakeX[0]][snakeY[0]] = '*';
      checkS = true;
    }

    else {
      checkS = false;
    }
  }
}
////////////////////////////////////////////////////////////////////////////
// UPDATING SNAKE AFTER MOVE FROM USER!!
int Move(char board[BOARDSIZE][BOARDSIZE], int snakeX[], int snakeY[],
         int *snakeSize, int move, int boardSize, int *foodX, int *foodY) {

  int t;
  int tmpSnakeX[BOARDSIZE];
  int tmpSnakeY[BOARDSIZE];
  int upDown = 0;
  int leftRight = 0;

  if (move == UP) {
    upDown = -1;
    leftRight = 0;
  }
  if (move == DOWN) {
    upDown = 1;
    leftRight = 0;
  }
  if (move == LEFT) {
    upDown = 0;
    leftRight = -1;
  }
  if (move == RIGHT) {
    upDown = 0;
    leftRight = 1;
  }

  for (int i = 0; i < *snakeSize; i++) {
    tmpSnakeX[i] = snakeX[i];
    tmpSnakeY[i] = snakeY[i];
  }

  if (board[snakeX[0] + upDown][snakeY[0] + leftRight] == '@') {

    *snakeSize = *snakeSize + 1;

    for (int i = 1; i < *snakeSize; i++) {
      snakeX[i] = tmpSnakeX[i - 1];
      snakeY[i] = tmpSnakeY[i - 1];
    }

    snakeX[0] = *foodX;
    snakeY[0] = *foodY;
    t = foodUpdate(board, boardSize, foodX, foodY);
    BoardUpdate(board, boardSize, snakeX, snakeY, snakeSize, foodX, foodY);
    return t;
  }

  else if (board[snakeX[0] + upDown][snakeY[0] + leftRight] == ' ') {
    for (int i = 1; i < *snakeSize; i++) {
      snakeX[i] = tmpSnakeX[i - 1];
      snakeY[i] = tmpSnakeY[i - 1];
    }
    snakeX[0] = snakeX[0] + upDown;
    snakeY[0] = snakeY[0] + leftRight;
    BoardUpdate(board, boardSize, snakeX, snakeY, snakeSize, foodX, foodY);
    return 0;
  }

  else {
    return 2;
  }
}

/////////////////////////////////////////////////////////////////////////////////////////
// UPDATING FOOD + CHECK IF BOARD FULL!!
int foodUpdate(char board[BOARDSIZE][BOARDSIZE], int boardSize, int *foodX,
               int *foodY) {

  bool check = false;
  bool full = false;

  for (int i = 1; i <= boardSize; i++) {
    for (int k = 1; k <= boardSize; k++) {
      if (board[i][k] == ' ') {
        full = true;
      }
    }
  }
  if (full == false) {
    return 1; // 1 = BOARD IS FULL!
  }

  while (check == false) {

    *foodX = rand() % boardSize + 1;
    *foodY = rand() % boardSize + 1;

    if (board[*foodX][*foodY] == ' ') {
      board[*foodX][*foodY] = '@';
      check = true;
    } else {
      check = false;
    }
  }
  return 0; // 0 = OK
}

///////////////////////////////////////////////////////////////////////////////
// UPDATING BOARD!!
void BoardUpdate(char board[BOARDSIZE][BOARDSIZE], int boardSize, int snakeX[],
                 int snakeY[], int *snakeSize, int *foodX, int *foodY) {

  for (int x = 1; x <= boardSize; x++)
    for (int i = 1; i <= boardSize; i++)
      board[x][i] = ' ';

  for (int k = 0; k < *snakeSize; k++)
    board[snakeX[k]][snakeY[k]] = '*';

  board[*foodX][*foodY] = '@';
}

//////////////////////////////////////////////////////////////////////////////
// PRINTING BOARD!!
void BoardPrint(int boardSize, char board[BOARDSIZE][BOARDSIZE]) {

  for (int i = 0; i <= boardSize + 1; i++) {
    for (int k = 0; k <= boardSize + 1; k++) {
      printf("%c", board[i][k]);
    }
    printf("\n");
  }
}
