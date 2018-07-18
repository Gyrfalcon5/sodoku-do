#include "sudoku.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char const *argv[])
{
  BOARD gameBoard = newBoard();

  // TODO prompt for file name instead
  FILE *fp = fopen("testboard.txt", "r");


  while(!feof(fp))
  {
    int value, row, column, sector;
    fscanf(fp, "%d,%d,%d,%d", &sector,&column,&row,&value);
    free(gameBoard.squares[column][row]);
    gameBoard.squares[column][row] = newSquare(value, row, column, sector);
  }

  printBoard(gameBoard);

  return 0;
}

SQUARE *newSquare(int value, int row, int column, int sector)
{
  SQUARE *newSq;
  newSq = (SQUARE *) malloc(sizeof(SQUARE));
  newSq->value = value;
  newSq->row = row;
  newSq->column = column;
  newSq->sector = sector;
  // For some reason it won't take batch initialization?
  for(int i = 0; i < 9 ; i++)
  {
    newSq->possible[i] = TRUE;
  }
  return newSq;

}

BOARD newBoard()
{
  BOARD newB;
  for(int rowIter = 0 ; rowIter < 9 ; rowIter++)
  {
    for(int colIter = 0 ; colIter < 9 ; colIter++)
    {
      int sector;
      if(colIter < 3)
      {
        if(rowIter <3)
          sector = 0;
        else if(rowIter < 6)
          sector = 3;
        else
          sector = 6;
      }
      else if(colIter < 6)
      {
        if(rowIter <3)
          sector = 1;
        else if(rowIter < 6)
          sector = 4;
        else
          sector = 7;
      }
      else
      {
        if(rowIter <3)
          sector = 2;
        else if(rowIter < 6)
          sector = 5;
        else
          sector = 8;
      }
      newB.squares[colIter][rowIter] = newSquare(0, rowIter, colIter, sector);
    }
  }
  return newB;
}

void printBoard(BOARD toPrint)
{
  printf("\n");
  for(int colIter = 0 ; colIter < 9 ; colIter++)
  {
    for(int rowIter = 0 ; rowIter < 9 ; rowIter++)
    {
      printf(" %d ", toPrint.squares[colIter][rowIter]->value);
      if((((rowIter + 1) % 3) == 0) && (rowIter != 8))
        printf("| ");
    }
    if((((colIter + 1) % 3) == 0) && (colIter != 8))
      printf("\n------------------------------\n");
    else
      printf("\n");
  }
  printf("\n");
}
