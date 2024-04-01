#include <iostream>
#include "puzzle_solver.h"

using namespace std;

/**
 * This function uses A* search algorithm to solve a 15-puzzle with 
 * a given initial position.
*/
vector<BoardState *> solve(BoardState *initial_board)
{
    AStarFrontier frontier; // A frontier to store the unexplored states
    AStarFrontier explored; // A frontier to store already explored states

    BoardState *board_to_check, *new_board;

    bool *valid_moves;

    // A vector to store the full solution if found. This vector will contain all 
    // the board states to pass through to reach the solved state from the initial
    // state. The initial state is not included in this vector
    vector<BoardState *> solution;

    // If the board is unsolvable, return an empty solution
    if (!initial_board->isSolvable())
    {
        return solution;
    }

    // Start with the initial board
    frontier.push(initial_board);

    // We keep on exploring states from the frontier until we have no state to check
    // On each iteration, one BoardState is checked and its children BoardStates (made by applying
    // valid moves) are added to the frontier
    while (!frontier.isEmpty())
    {
        // Bring out the board state with least Manhattan distance and add it to
        // the explored frontier
        board_to_check = frontier.pop();
        explored.push(board_to_check);

        // If the board is solved, we fill the solution vector and return it
        if (board_to_check->isSolved())
        {
            // Backtrack using the prev_state member from the solved state back to
            // the initial state. Every state in between is added to the solution
            while (!board_to_check->isSame(initial_board))
            {
                solution.push_back(board_to_check);
                board_to_check = board_to_check->prev_state;
            }
            return solution;
        }

        // If the board to check is not solved one, find its valid moves, apply them to
        // create new board states to explore and add them to the frontier. However,
        // if a board state is already explored or is already in the frontier and yet
        // to be explored, we do not add it again.
        valid_moves = board_to_check->validMoves();
        if (valid_moves[UP])
        {
            new_board = board_to_check->applyMove(UP);
            if (!explored.contains(new_board) && !frontier.contains(new_board))
                frontier.push(new_board);
        }
        if (valid_moves[DOWN])
        {
            new_board = board_to_check->applyMove(DOWN);
            if (!explored.contains(new_board) && !frontier.contains(new_board))
                frontier.push(new_board);
        }
        if (valid_moves[LEFT])
        {
            new_board = board_to_check->applyMove(LEFT);
            if (!explored.contains(new_board) && !frontier.contains(new_board))
                frontier.push(new_board);
        }
        if (valid_moves[RIGHT])
        {
            new_board = board_to_check->applyMove(RIGHT);
            if (!explored.contains(new_board) && !frontier.contains(new_board))
                frontier.push(new_board);
        }
    }

    return solution;
}