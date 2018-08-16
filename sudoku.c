#include "sudoku.h"

int main()
{
    
    printf("here");
    BOARD gameBoard;
    
    // TODO make it solve all the puzzles in the folder 
    FILE *fp = fopen("puzzles/testboard.txt", "r");
    int count = 0;
    while(!feof(fp) && count < 81)
    {
        int value;
        int row = count % 9;
        int column = count / 9;
        int sector;
        if(column < 3)
        {
            if(row <3)
                sector = 0;
            else if(row < 6)
                sector = 3;
            else
                sector = 6;
        }
        else if(column < 6)
        {
            if(row <3)
                sector = 1;
            else if(row < 6)
                sector = 4;
            else
                sector = 7;
        }
        else
        {
            if(row <3)
                sector = 2;
            else if(row < 6)
                sector = 5;
            else
                sector = 8;
        }
        fscanf(fp, "%d", &value);
        gameBoard.squares[column][row] = newSquare(value, row, column, sector);
        count++;
        
    }
    
    printBoard(gameBoard);
    // TODO make it solve the board
    while(!checkIfSolved(gameBoard))
    {
        eliminateRows(gameBoard);
        eliminateCols(gameBoard);
        eliminateSectors(gameBoard);
    }
    return 0;
}
