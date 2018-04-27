/*
 * Student ID: 2415020
 *
 * Additional Comments: This header file links the dfs.c and board.c together, as well as with the
 * main_pyramid function. Here I define some function prototypes that are used throughout the entire code.
 * I also included included standard c libraries to use booleans and do some validation.
 */
#ifndef V4COMPLETE_BOARD_H
#define V4COMPLETE_BOARD_H


#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>

#define ROWS 5 // Number of rows in the pyramid
#define PEGS (ROWS * (ROWS+1)) / 2 // Number of pegs in the pyramid; The formula is: Tn = (n*(n+1))/2
#define MAX_MOVES 6 // The number of maximum possible moves a peg can perform

//Structure definition
typedef struct board{
    int peg[PEGS]; // each board will represent its pegs by an array of integers
    int *row[ROWS]; // these rows will point at the peg array
    int pegRow, pegCol; // row and column of peg that jumped to get to this position
    struct board *previousPosition; //the board layout prior to this one
}Board;

typedef struct boardNode{ // Search will be depth-first, using a list of Nodes
    Board *board; //the current board structure
    struct boardNode *next; //the node layout proceeding this one
}Node;

/*
 * Function prototypes
 */
// board.c functions //
void print_boards(Board *first);
void row_fill(Board *newBoard);
void board_fill(int *boardArray, Board *newBoard);
int solve(int board[]);
Board *fill_new_Board(int *boardArray);
Board *copy_board(Board *oldBoard);
Board *reverse_order(Board *first);
void board_enqueue(Board *currentBoard, Node **first);
void release(Node *node);
// dfs.c //
bool can_jump(Board *parent, int row, int col, int rowOffset, int columnOffset);
Board *jump(Board *parent , int row , int col , int rowOffset , int colOffset);
Board * jump_North_East(Board *parent, int row, int col);
Board * jump_North_West(Board *parent, int row, int col);
Board * jump_South_East(Board *parent, int row, int col);
Board * jump_South_West(Board *parent, int row, int col);
Board * jump_East(Board *parent, int row, int col);
Board * jump_West(Board *parent, int row, int col);
void dfs(Node **queue, Node **visited);

#endif //V4COMPLETE_BOARD_H
