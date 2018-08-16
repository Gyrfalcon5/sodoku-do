#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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


void printBoard(BOARD toPrint)
{
    printf("\n");
    for(int colIter = 0 ; colIter < 9 ; colIter++)
    {
        for(int rowIter = 0 ; rowIter < 9 ; rowIter++)
        {
            if(toPrint.squares[colIter][rowIter]->value)
                printf(" %d ", toPrint.squares[colIter][rowIter]->value);
            else
                printf("   ");

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

// TODO also make this return if it changed anything
void eliminateRows(BOARD toElim)
{
    for(int rowIter = 0 ; rowIter < 9 ; rowIter++)
    {
        BOOL possible[9];
        for(int idx = 0 ; idx < 9 ; idx++)
            possible[idx] = TRUE;

        
        for(int colIter = 0 ; colIter < 9 ; colIter++)
        {
            if(toElim.squares[colIter][rowIter]->value)
            {
                possible[toElim.squares[colIter][rowIter]->value - 1] = FALSE;
            }
        }

        for(int colIter = 0 ; colIter < 9 ; colIter++)
        {
            if(!toElim.squares[colIter][rowIter]->value)
            {
                for(int idx = 0 ; idx < 9 ; idx++)
                {
                    toElim.squares[colIter][rowIter]->possible[idx] = toElim.squares[colIter][rowIter]->possible[idx] * possible[idx];
                }
            }
        }
    }
}

// TODO also make this return if it changed anything
void eliminateCols(BOARD toElim)
{
    for(int colIter = 0 ; colIter < 9 ; colIter++)
    {
        BOOL possible[9];
        for(int idx = 0 ; idx < 9 ; idx++)
            possible[idx] = TRUE;

        
        for(int rowIter = 0 ; rowIter < 9 ; rowIter++)
        {
            if(toElim.squares[colIter][rowIter]->value)
            {
                possible[toElim.squares[colIter][rowIter]->value - 1] = FALSE;
            }
        }

        for(int rowIter = 0 ; rowIter < 9 ; rowIter++)
        {
            if(!toElim.squares[colIter][rowIter]->value)
            {
                for(int idx = 0 ; idx < 9 ; idx++)
                {
                    toElim.squares[colIter][rowIter]->possible[idx] = toElim.squares[colIter][rowIter]->possible[idx] * possible[idx];
                }
            }
        }
    }
}

void printPossible(BOARD toPrint)
{
    printf("\n");
    for(int colIter = 0 ; colIter < 9 ; colIter++)
    {
        for(int rowIter = 0 ; rowIter < 9 ; rowIter++)
        {
            int sum = 0;
            for(int idx = 0 ; idx < 9 ; idx++)
                sum += toPrint.squares[colIter][rowIter]->possible[idx];

            if(toPrint.squares[colIter][rowIter]->value)
                printf(" 1 ");
            else
                printf(" %d ", sum);
            
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

// TODO make it report if it changed anything so we can know if we can solve it or not
void eliminateSectors(BOARD toElim)
{
    for(int sectorNum = 0 ; sectorNum < 9 ; sectorNum++)
    {
        BOOL possible[9];
        for(int idx = 0 ; idx < 9 ; idx++)
            possible[idx] = TRUE;

        for(int colIter = 0 ; colIter < 9 ; colIter++)
        {
            for(int rowIter = 0 ; rowIter < 9 ; rowIter++)
            {
                if((toElim.squares[colIter][rowIter]->sector == sectorNum) && toElim.squares[colIter][rowIter]->value)
                    possible[toElim.squares[colIter][rowIter]->value - 1] = FALSE;
            }
        }

        for(int colIter = 0 ; colIter < 9 ; colIter++)
        {
            for(int rowIter = 0 ; rowIter < 9 ; rowIter++)
            {
                if((toElim.squares[colIter][rowIter]->sector == sectorNum) && !toElim.squares[colIter][rowIter]->value)
                    for(int idx = 0 ; idx < 9 ; idx++)
                    {
                        toElim.squares[colIter][rowIter]->possible[idx] = toElim.squares[colIter][rowIter]->possible[idx] * possible[idx];
                    }
            }
        }
    }
}

int checkIfSolved(BOARD toCheck)
{
    for(int colIter = 0 ; colIter < 9 ; colIter++)
    {
        for(int rowIter = 0 ; rowIter < 9 ; rowIter++)
        {
            if(!toCheck.squares[colIter][rowIter]->value)
                return 0;
        }
    }
    return 1;
}




#endif
