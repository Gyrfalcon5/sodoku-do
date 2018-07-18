#ifndef SUDOKU_METHODS
#define SUDOKU_METHODS

#define TRUE 1
#define FALSE 0
typedef int BOOL;

typedef struct _square
{

  int value;
  int row;
  int column;
  int sector;
  BOOL possible[9];


} SQUARE;

SQUARE *newSquare(int value, int row, int column, int sector);

typedef struct _board
{

  SQUARE *squares[9][9];

} BOARD;

BOARD newBoard();
void printBoard(BOARD toPrint);

#endif
