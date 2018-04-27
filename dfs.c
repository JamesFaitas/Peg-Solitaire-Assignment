/*
 * Student ID: 2415020
 */
#include "board.h"

/**
 * Determines if a peg can perform a jump or not by checking where it's going to land,
 * if the position that is landing is empty
 * and if there's a peg to jump over.
 * @param parent
 * @param row
 * @param col
 * @param rowOffset
 * @param columnOffset
 * @return true or false
 */
bool can_jump(Board *parent, int row, int col, int rowOffset, int columnOffset){
    if ( row+rowOffset >= 0 // landing row is not off the top of the board
         && row+rowOffset < ROWS // landing row is not off bottom of board
         && col+columnOffset >= 0 // landing column is not off left side of the board
         && col+columnOffset <= row+rowOffset // landing column is not off right of the board
         && *(parent->row[row+rowOffset] + (col+columnOffset)) == 0 // landing space is empty
         && *(parent->row[row+(rowOffset/2)] + (col+(columnOffset/2))) == 1 // there's a peg to jump over
            )
        return true;
    else return false;
}
/**
 * Helper function for all the jump functions.
 * Takes a board pointer, the row/col of peg in question,
 * and the offset -- rowOffset and colOffset -- describing how the peg jumps.
 * rowOffset and colOffset can be -2, 0, or 2.
 * After checking if a jump is legal by calling the can_jump function, it proceeds on making the jump
 * by filling the landing position (sets that position of the board to 1) and setting the position
 * that a peg jumped from to 0. Furthermore, the peg that was "in-between" is removed, set to 0
 * @param parent
 * @param row
 * @param col
 * @param rowOffset
 * @param colOffset
 * @return
 */
Board *jump(Board *parent , int row , int col , int rowOffset , int colOffset){
    Board *newBoard = NULL; //declaration and init of a new board

    if(can_jump(parent, row, col, rowOffset, colOffset)){ //checks if the move in question is legal and can be achieved
        newBoard = copy_board(parent); //if so, copy the board that was passed in, to the newBoard
        newBoard->previousPosition = parent; //set the passed board as the parent/previous board of the new board
        newBoard->pegRow = row; //row of the peg that is to perform the jump/move
        newBoard->pegCol = col; //column of the peg that is to perform the jump/move
        *(newBoard->row[row+rowOffset] + (col+colOffset)) = 1; // landing space is filled in
        *(newBoard->row[row+(rowOffset/2)] + (col+(colOffset/2))) = 0; // jumped peg is removed
        *(newBoard->row[row] + col) = 0; // jumped-from position is now empty

        return newBoard; //returns the newBoard where a jump was performed
    }
    else return NULL; //if the move is invalid then it returns NULL
}
/*
 * These functions each check if a given peg on a given board can
 * make a certain type of jump. They return a pointer to the resulting board
 * if so, and NULL otherwise.
 */
/**
 * Checks if the peg can perform a jump at the up-right diagonal
 * @param parent
 * @param row
 * @param col
 * @return newBoard, returns a pointer to the resulting board, either filled, by performing the jump or null otherwise
 */
Board * jump_North_East(Board *parent, int row, int col){
    Board *newBoard = NULL;
    newBoard = jump(parent,row,col,-2,0);
    return newBoard;
}
/**
 * Checks if the peg can perform a jump right horizontally
 * @param parent
 * @param row
 * @param col
 * @return newBoard, returns a pointer to the resulting board, either filled, by performing the jump or null otherwise
 */
Board * jump_East(Board *parent, int row, int col){
    Board *newBoard = NULL;
    newBoard = jump(parent,row,col,0,2);
    return newBoard;
}
/**
 * Checks if the peg can perform a jump at the down-right diagonal
 * @param parent
 * @param row
 * @param col
 * @return newBoard, returns a pointer to the resulting board, either filled, by performing the jump or null otherwise
 */
Board * jump_South_East(Board *parent, int row, int col){
    Board *newBoard = NULL;
    newBoard = jump(parent,row,col,2,2);
    return newBoard;
}
/**
 * Checks if the peg can perform a jump at the down-left diagonal
 * @param parent
 * @param row
 * @param col
 * @return newBoard, returns a pointer to the resulting board, either filled, by performing the jump or null otherwise
 */
Board * jump_South_West(Board *parent, int row, int col){
    Board *newBoard = NULL;
    newBoard = jump(parent,row,col,2,0);
    return newBoard;
}
/**
 * Checks if the peg can perform a jump left horizontally
 * @param parent
 * @param row
 * @param col
 * @return newBoard, returns a pointer to the resulting board, either filled, by performing the jump or null otherwise
 */
Board * jump_West(Board *parent, int row, int col){
    Board *newBoard = NULL;
    newBoard = jump(parent,row,col,0,-2);
    return newBoard;
}
/**
 * Checks if the peg can perform a jump at the up-left diagonal
 * @param parent
 * @param row
 * @param col
 * @return newBoard, returns a pointer to the resulting board, either filled, by performing the jump or null otherwise
 */
Board * jump_North_West(Board *parent, int row, int col){
    Board *newBoard = NULL;
    newBoard = jump(parent,row,col,-2,-2);
    return newBoard;
}

// DFS - Depth-First Search Algorithm //
/**
 * Removes the first node and enqueues the possible moves, by performing a depth-first search
 * using a list of Nodes.
 * @param queue
 * @param visited
 */
void dfs(Node **queue, Node **visited){
    // An array of pointers to the above functions
    Board *(*jumpFunctions[])(Board*,int,int) = {jump_North_West, jump_North_East, jump_West, jump_East, jump_South_West, jump_South_East};

    int row, column, function; //counters to the function array

    Board *parentBoard, *newBoard;
    Node *newNodeList = NULL; // This will be a list of the generated boards
    Node *oldQueue, *oldVisited;

    parentBoard = (*queue)->board; //assigns the board from the queue node as the parentBoard by casting it as a Board
    // Generate new possible boards, and add to newNodeList
    for(row=0; row<ROWS; row++) { // for each row:
        for(column=0; column<row+1; column++) { // for each column in a row:
            if (*(parentBoard->row[row]+column) == 1) { // If this position has a peg
                for(function=0; function<MAX_MOVES; function++) { // Try all 6 possible jumps, iterates through the array of functions
                    if ((newBoard = (*jumpFunctions[function])(parentBoard, row, column))) { //if a jump is legal
                        board_enqueue(newBoard, &newNodeList); //it enqueues the new board where the legal jump was performed
                    }
                }
            }
        }
    }


    oldVisited = *visited; //adds the now-examined board to the visited list
    oldQueue = *queue;


    if (newNodeList) {
        *queue = newNodeList; // Add newNodeList to front of queue
        while (newNodeList->next) // until it reaches the end of the list
            newNodeList = newNodeList->next; //assigns the rest of the nodes; next nodes

        newNodeList->next = oldQueue->next;
    } else {
        *queue = (*queue)->next;
    }

    *visited = oldQueue; // Add queue to the front of the visited list
    oldQueue->next = oldVisited;

}