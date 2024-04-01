#ifndef PUZZLE_SOLVER
#define PUZZLE_SOLVER

#include <fstream>
#include "frontier.h"

// A function to solve the 15-puzzle from an initial board state
vector<BoardState *> solve(BoardState *initial_board);

#endif