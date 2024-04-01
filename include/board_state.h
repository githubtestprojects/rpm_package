#ifndef BOARDSTATE
#define BOARDSTATE

// This enum for the direction of a move. The actions corresponding to each value
// is as follows:
// UP:    The tile below -1 is moved UP to the position of -1
// DOWN:  The tile above -1 is moved DOWN to the position of -1
// LEFT:  The tile to the right of -1 is moved LEFT to the position of -1
// RIGHT: The tile to the left of -1 is moved RIGHT to the position of -1
// NONE:  A placeholder move to indicate a null move
enum move_t
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NONE
};


/**
 * The class BoardState represents the state of the 15-puzzle board at any position.
 * It stores the values of the tiles in the given state as well as the position of the
 * blank space. It also includes helper functions for the overall solver algorithm.
*/
class BoardState
{
private:

    // The values in the board represented by 4x4 array of ints
    // -1 represents the blank space
    int board[4][4];

public:

    // The position (row and column) of the blank space. These
    // are helpful in identifying the valid moves in a position
    // as well as make those moves
    int blank_pos_r;
    int blank_pos_c;

    // These variables are used to store the previous board position
    // and the move applied to reach this current position. These are
    // useful when a solution is reached and we have to backtrack through
    // the moves to list out all the moves made.
    BoardState *prev_state;
    move_t prev_move;

    // Methods: documentation alongside their definitions
    BoardState(int b[4][4], BoardState *prev_s, move_t prev_m);
    void print();
    int getNumInversions();
    bool isSolvable();
    bool isSolved();
    int get(int x, int y);
    void set(int x, int y, int num);
    BoardState *applyMove(move_t move);
    bool *validMoves();
    int manhattan();
    bool isSame(BoardState *b);
};

#endif