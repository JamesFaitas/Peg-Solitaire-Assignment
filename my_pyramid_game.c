/*
 * Student ID: 2415020
 *
 * Additional Comments: First of all, after researching how to use solve the peg-solitaire game,
 * I realised that using a global 3-tuple isn't the most effective way to solve this puzzle.
 * The must popular and effective algorithm that can be used instead of "hard-coding", is the Depth-First Search or DFS
 * for short. Therefore, I mainly based my implementation on the following academic report: https://cs.uwaterloo.ca/journals/JIS/VOL11/Bell/bell2.pdf
 * as well as other relevant internet sources. Also I decided, to organize my code in different .c files that are linked together
 * and with the main_pyramid function by a header file.
 */

#include "board.h"
#include "pyramid_helpers.h"

/**
 * Begins with a start position and adds it to the search queue. Then, it loops:
 * Is first element of queue a winning position (has only one peg)? If so, break --
 * solution found; if not, remove it, generate all boards that can be formed by
 * any single legal jump, and add them to the queue.
 * @return
 */
int main_pyramid() {

    int board[15]; //declaration and init of the board array

    pyramid_input(board); //asks the user to create a board

    Board *first, *solution; //declaration of first board and solved board list
    Node *queue;    //List of to-be-examined nodes, "queue" points to the first one
    Node *visited;  // list of already examined nodes

    first = fill_new_Board(board); //fill the first board with the initial board array that was created by the user
    first->previousPosition = NULL; //sets previous board to null since this is the first board that was created
    queue = malloc(sizeof(Node)); //allocates the memory that the node struct takes up
    queue->board = first; //adds the first board to the beginning of the queue
    queue->next = NULL; //and sets the next node to null; second element of the queue
    visited = malloc(sizeof(Node)); //allocates the memory that the node struct takes up
    visited->board = NULL; //sets the board member to null, since none elements of the queue have been visited at the init
    visited->next = NULL;

    while( queue != NULL ) { //iterates through the queue until it's empty
        if (solve(queue->board->peg)) //if board has only one peg left then break
            break;

        dfs(&queue, &visited); //removes first and enqueues the possible moves
    }

    if (!queue) //if the board is unsolvable; queue is null
        printf("The board you entered doesn't have a solution.\n"); //outputs an appropriate message
    else { //otherwise
        printf("Here is the board you entered:\n");
        pyramid_print(board); //outputs the initial board the user entered
        printf("\nSolution:\n");
        solution = reverse_order(queue->board); //stores the list of boards that occur to a win in the solution board struct, in reverse order
        print_boards(solution); //prints the solution steps board-by-board
    }

    release(queue); //frees the memory that was allocated by the queue
    release(visited); //frees the memory that was allocated by the examined nodes queue

    return 0;
}