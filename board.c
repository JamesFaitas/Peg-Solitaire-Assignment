/*
 * Student ID: 2415020
 *
 * Additional comments: At the board.h I've defined a Board structure as well as a Node structure.
 * Therefore, I have to use malloc, which allocates a block of memory to the heap, whenever I declare a
 * Board or Node struct. Because the contents of a struct are stored in contiguous memory, the sizeof
 * operator MUST be used to get the number of bytes needed to store a particular type of structs.
 */
#include "board.h"
#include "pyramid_helpers.h"

/**
 * It takes a Board structure and fills the row array member of that board. (first element of each row)
 * @param newBoard
 */
void row_fill(Board *newBoard){
    for(int i = 0, triangleOffset = 0; i<ROWS; i++){ //iterates through the row and peg array. sets an initial offset variable.
        newBoard->row[i] = newBoard->peg + triangleOffset; //fills each element of the row array with the content of the peg array at position+offset.
        triangleOffset += (i+1); //increments the triangle offset (1 then 3 then 6 then 10)
    }
}
/**
 * It takes the board array (1s and 0s) and copies it to the member: peg array of the Board structure
 * @param boardArray
 * @param newBoard
 */
void board_fill(int *boardArray, Board *newBoard){
    for(int i = 0; i <PEGS; i++) //iterates though the board array
        newBoard->peg[i] = boardArray[i]; //assigns its content to the peg array of the given board struct
}

/**
 * (Copied from 'my_pyramid_solver.h')
 *
 * THIS FUNCTION WILL BE CALLED DURING TEST ASSESSMENTS.
 *
 * solve: This is the game 'engine', in which the logic is based.
 *        It takes a board in any valid state, and determines
 *        if the game is solvable.
 *
 * Parameters:
 *        board - an integer array of size 15, with contents either 0 or 1.
 *
 * Returns:
 *        1  -  If the board is solvable;
 *        0  -  otherwise.
 *
 * @param board
 * @return 1 if the board is solvable or 0 if not
 */
int solve(int board[]){
    //the following validation is to prevent errors during the scripted testing
    for(int i =0; i<PEGS; i++) {//iterates through the board array to check if it consists of 0s and 1s
        if(isalnum(board[i]) || (board[i] != 0 && board[i] != 1)) { //if alphanumeric or not zero nor one then
            printf("The board is in an invalid state."); //outputs an appropriate message
            exit(0); //and terminates the program
        }
    }
    int pegCount = 0; //counter to check the number of pegs within the current board
    for(int i =0; i<PEGS; i++) //iterates through the array
        if(board[i] == 1) //if the array cell is equal to 1, meaning that there's a peg in that position
            pegCount++; //increment the peg counter

    return (pegCount == 1); //returns 1 or 0 if condition is true; the number of pegs in the board is one, meaning that the board has been solved or not
}
/**
 * It takes the board array, at it's current state and assigns its content to the peg array, member of
 * a new board structure.
 *
 * @param boardArray
 * @return newBoard , returns a new board that contains the content of the board[].
 */
Board *fill_new_Board(int *boardArray){
    Board *newBoard = NULL; //declares a new board struct and inits as null

    if((newBoard = malloc(sizeof(Board)))) { //checks if newBoard can be allocated to memory as a Board struct. Explained above.
        board_fill(boardArray, newBoard); //fills the peg array of the newBoard with the content of the board that was passed in.
        row_fill(newBoard); //fills the rows of the current newBoard
    }
    return newBoard;
}
/**
 * Takes the current board/old board and copies its content to a new board that get returned by the function
 * @param oldBoard
 * @return newBoard if content can be copied or null otherwise
 */
Board *copy_board(Board *oldBoard){
    Board *newBoard = NULL; //declaration of a new board that will be returned if it gets successfully copied or null otherwise.

    if((newBoard = malloc(sizeof(Board)))) { //checks if newBoard can be allocated to memory as a Board struct. Explained above.
        board_fill(oldBoard->peg, newBoard); //fills the peg array of the new board with the content of the peg array of the oldBoard.
        row_fill(newBoard); //fills the rows of the current newBoard
    }
    return newBoard;
}
/**
 * Takes a board structure and reverses the chain of "previousPosition"s
 * @param first
 * @return first, returns the new first board
 */
Board *reverse_order(Board *first) {
    Board *child, *parent; //declaration of two board structures, a child and a parent temporary board.
    //inits the child board to null, assigns the parent board to the "first" board after every iteration,
    // until it reaches the empty previousPosition of the original first board that was passed in.
    for(child = NULL; first->previousPosition; first = parent) {
        parent = first->previousPosition; //starting from the last board(winning board) it copies the previousPosition(previous board) to the parent board
        first->previousPosition = child;
        child = first; //assigns the modified first board to the child board.
    }
    first->previousPosition = child; //this is essentially the first board that the user constructed.
    return first;
}
/**
 * Takes current board and enqueues it (adds it to the front of the list).
 * @param currentBoard
 * @param first node of the queue
 */
void board_enqueue(Board *currentBoard, Node **first) {
    Node *newNode; //declaration of a new node

    newNode = malloc(sizeof(Node)); //allocates the required bytes of memory for the node struct
    newNode->board = currentBoard; //assigns current board that was passed in to the board element of the node struct
    newNode->next = *first; //assigns the node that was passed in to the next node member of the struct; moves it down the queue
    *first = newNode; //the newNode gets enqueued
}
/**
 * Gets a nodelist/queue and releases back to the heap all the memory allocated to the node pointer
 * @param node
 */
void release(Node *node) {
    Node *next;

    for ( ; node; node = next) { //iterate as long as node isn't null
        next = node->next; //get next node in the queue
        free(node->board); //releases the memory allocated to the pointer
        free(node);
    }
}
/**
 * This function takes the current board and prints it to the console by calling the pyramid print function.
 * At the end it assigns the previous board,or the next one when it gets reversed, to the first board, "iterating" in this way through all the boards.
 * @param first
 */
void print_boards(Board *first) {
    while (first) {
        pyramid_print(first->peg); //calls the pyramid_print function
        printf("\n=========================================\n"); //simple board separator
        first = first->previousPosition; //gets the previous/next board
    }
}
