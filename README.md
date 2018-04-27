# Peg Solitaire Assignment
Peg solitaire game implementation in C. 
The peg board consists of 15 pegs. 
The user is asked to insert pegs on an empty board. 
Once the board is set up, a Depth-First search algorithm finds a possible solution. 
The set of moves performed that resulted to a solution, are displayed to the user, step-by-step.

Rules
-------------------------------------------------------------------------------------------------
This game is a version of peg-solitaire, with 15 ‘holes’ spaced and indexed as follows.
                                             __
                                            | 0|
                                            |__|
                                          __   __
                                         | 1| | 2|
                                         |__| |__|
                                         __      __
                                        | 3|  4 | 5|
                                        |__|    |__|
                                     __   __   __   __
                                    | 6| | 7| | 8| | 9|
                                    |__| |__| |__| |__|
                                   __   __   __   __   __
                                  |10| |11| |12| |13| |14|
                                  |__| |__| |__| |__| |__|
                                  
The game starts with one empty hole. A hole that contains a peg is represented by a box. Thus,
in the board above, hole 4 is empty.
Moves consist of ‘jumps’ that are made much as jumps in checkers: One peg can jump over an
adjacent peg to the empty hole, causing the adjacent peg to be removed from the board.
Unlike checkers, however, a jump may be horizontal or diagonal, but not vertical.
Consider the board initially configured as above. Peg 13, for example, can jump over peg 8 to
land in space 4. This move (or jump) causes peg 8 to be removed, leaving the following board.
                                           __
                                          | 0|
                                          |__|
                                         __   __
                                        | 1| | 2|
                                        |__| |__|
                                       __   __   __
                                      | 3| |4 | | 5|
                                      |__| |__| |__|
                                     __   __       __
                                    | 6| | 7|  8  | 9|
                                    |__| |__|     |__|
                                   __   __   __      __
                                  |10| |11| |12| 13 |14|
                                  |__| |__| |__|    |__|

The next move could be any of 1-over-4-to-8, 6-over-7-to-8, or 11-over-12-to-13. After every
move there is one fewer peg. The longest possible game consists of thirteen moves. A ‘win’
occurs when there is only one peg left on the board. (Aside: Despite our ‘human’
inclinations to finish with a peg in 4, a win will always finish with the final peg in 12!)
A ‘legal’ move depends on the board, so the set of all possible moves consists of moves that
are in legal any conceivable peg arrangement, eg. 2-over-7-to-12 is neither legal, nor possible.
