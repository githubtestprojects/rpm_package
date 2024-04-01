#include <iostream>

#include "board_state.h"

using namespace std;


/**
 * This is the initializer for the BoardState class.
 * It takes in a 4x4 array of ints to fill the state with as well as
 * the parent state and parent move of the current state.
*/
BoardState::BoardState(int b[4][4], BoardState *prev_s, move_t prev_m)
{
    int i, j;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            board[i][j] = b[i][j];
            if (b[i][j] == -1)
            {
                blank_pos_r = i;
                blank_pos_c = j;
            }
        }
    }
    prev_state = prev_s;
    prev_move = prev_m;
}


/**
 * This is a utility function that prints the tiles of the current
 * state. Used mainly for debug purposes.
*/
void BoardState::print()
{
    int i, j;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            printf("%3d", this->get(i, j));
        }
        printf("\n");
    }
}


/**
 * This function gets the number of inversions in a board of 15-puzzle.
 * If we flatten out our 15-puzzle board into a 1D array of 15 numbers (ignoring the -1),
 * then for each pair of indices i and j, it is an inversion if i < j and board[i] > board[j].
 * This function counts all such inversions in the board. This number is used to check the 
 * solvability of the 15-puzzle
*/
int BoardState::getNumInversions()
{
    int count = 0;
    int flattenedBoard[15];
    int i, j, idx = 0;

    // Flatten out the board into the 1D array
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if (this->get(i, j) > 0)
            {
                flattenedBoard[idx] = this->get(i, j);
                idx++;
            }
        }
    }

    // Count the inversions
    for (i = 0; i < 15; i++)
    {
        for (j = i + 1; j < 15; j++)
        {
            if (flattenedBoard[i] > flattenedBoard[j])
                count++;
        }
    }

    return count;
}


/**
 * This function checks whether the given board is solvable or not.
 * The check for solvability of a 15-puzzle is as follows:
 * 1- If the blank space is on the first or third row (row index 0 or 2) and the number of
 *    inversions is odd, the puzzle is solvable
 * 2- If the blank space is on the second or fourth row (row index 1 or 3) and the number of
 *    inversions is even, the puzzle is solvable
 * 3- Otherwise, the puzzle is insolvable
*/
bool BoardState::isSolvable()
{
    int numInversions = getNumInversions();
    if (blank_pos_r % 2 == 0)
        return (numInversions % 2 == 1);
    else
        return (numInversions % 2 == 0);
}


/**
 * This function checks whether the current board is in the solved
 * state.
*/
bool BoardState::isSolved()
{
    int i, j;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            // The correct number to be in row i and column j is i*4+j+1
            // If the correct number if not in the correct position, return false
            if (this->get(i, j) != -1 && this->get(i, j) != i * 4 + j + 1)
                return false;
        }
    }
    return true;
}


/**
 * Getter for the values in the board
*/
int BoardState::get(int x, int y)
{
    return board[x][y];
}


/**
 * Setter for the values in the board
*/
void BoardState::set(int x, int y, int num)
{
    board[x][y] = num;
}


/**
 * This function applies a given move on the current board and returns
 * a new BoardState representing the resulting position. The result has the
 * current board and the move applied as its parents.
*/
BoardState *BoardState::applyMove(move_t move)
{   
    // Create a new BoardState in the same position as the current one
    BoardState *new_board;
    new_board = new BoardState(board, this, move);

    switch (move)
    {
    case UP:
        // Move the number below the -1 into the position of -1
        new_board->set(blank_pos_r, blank_pos_c, new_board->get(blank_pos_r + 1, blank_pos_c));
        // Move the -1 to the position of moved tile
        new_board->set(blank_pos_r + 1, blank_pos_c, -1);
        // Update the position of -1
        new_board->blank_pos_r++;
        break;

    case DOWN:
        // Move the number above the -1 into the position of -1
        new_board->set(blank_pos_r, blank_pos_c, new_board->get(blank_pos_r - 1, blank_pos_c));
        // Move the -1 to the position of moved tile
        new_board->set(blank_pos_r - 1, blank_pos_c, -1);
        // Update the position of -1
        new_board->blank_pos_r--;
        break;

    case LEFT:
        // Move the number to the right of the -1 into the position of -1
        new_board->set(blank_pos_r, blank_pos_c, new_board->get(blank_pos_r, blank_pos_c + 1));
        // Move the -1 to the position of moved tile
        new_board->set(blank_pos_r, blank_pos_c + 1, -1);
        // Update the position of -1
        new_board->blank_pos_c++;
        break;

    case RIGHT:
        // Move the number to the left of the -1 into the position of -1
        new_board->set(blank_pos_r, blank_pos_c, new_board->get(blank_pos_r, blank_pos_c - 1));
        // Move the -1 to the position of moved tile
        new_board->set(blank_pos_r, blank_pos_c - 1, -1);
        // Update the position of -1
        new_board->blank_pos_c--;
        break;

    default:
        break;
    }

    return new_board;
}


/**
 * This function returns a boolean array of size 4, representing which of
 * the move directions are valid.
 * The return type is a bool array `valid` of size 4 with valid[UP], valid[DOWN],
 * valid[LEFT] and valid[RIGHT] representing the validity of each direction
*/
bool *BoardState::validMoves()
{
    static bool valid[4];
    valid[UP] = (blank_pos_r < 3);
    valid[DOWN] = (blank_pos_r > 0);
    valid[LEFT] = (blank_pos_c < 3);
    valid[RIGHT] = (blank_pos_c > 0);
    return valid;
}


/**
 * This function calculates the Manhattan distance of the current BoardState from
 * a solved BoardState.
 * The Manhattan distance of a tile is defined as the sum of the absolute horizontal 
 * distance and absolute vertical distance of a tile from its correct position.
 * The sum of the Manhattan distances of each tile of the board (except the -1 since
 * it is an empty space) is the Manhattan distance of the board.
*/
int BoardState::manhattan()
{
    int i, j, num;
    int correct_r, correct_c;
    int manhattan_distance = 0;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            num = this->get(i, j);

            // The -1 is to be ignored
            if (num == -1)
                continue;

            // Calculate the correct position (row and column) of the number in a solved board
            correct_r = (num - 1) / 4;
            correct_c = (num - 1) % 4;

            // Add the absolute horizontal and vertical distances into the overall Manhattan distance
            manhattan_distance += (correct_r < i) ? (i - correct_r) : (correct_r - i);
            manhattan_distance += (correct_c < j) ? (j - correct_c) : (correct_c - j);
        }
    }
    return manhattan_distance;
}


/**
 * This function checks whether the current board is the same in position as another BoardState
 * Two BoardStates are deemed to be same if the numbers in their boards are exactly in the same
 * positions.
*/
bool BoardState::isSame(BoardState *b)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (this->get(i, j) != b->get(i, j))
                return false;
        }
    }
    return true;
}