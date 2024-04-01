#include <iostream>
#include "frontier.h"

using namespace std;


/**
 * This function is a print utitlity function mostly used for debugging.
*/
void AStarFrontier::print()
{
    int c = 0;
    cout << "================================================" << endl;
    cout << "A* FRONTIER" << endl;
    cout << "================================================" << endl;
    for (auto it = states.begin(); it != states.end(); ++it)
    {
        cout << "State " << (c + 1) << ": ";
        cout << "manhattan=" << (*it)->manhattan() << endl;
        (*it)->print();
        cout << endl;
        c++;
    }
    cout << "================================================" << endl;
}


/**
 * This function pushes a BoardState into the frontier
*/
void AStarFrontier::push(BoardState *board)
{
    states.push_back(board);
}


/**
 * This function calculates the heuristic for deciding priority of BoardStates.
 * The heuristic is just the Manhattan distance of the board.
*/
int AStarFrontier::heuristic(BoardState *board)
{
    return board->manhattan();
}


/**
 * This function pops a BoardState out of the vector based on priority. The 
 * state with the highest priority (least Manhattan distance) is popped out.
*/
BoardState *AStarFrontier::pop()
{
    if (states.empty())
        return NULL;

    int min_heuristic;
    vector<BoardState *>::iterator it, astar_idx;
    BoardState *astar_board;

    it = states.begin(); // For iteration
    astar_idx = states.begin(); // For storing the state with highest priority
    min_heuristic = heuristic(*it);

    for (it = states.begin(); it != states.end(); it++)
    {
        if (heuristic(*it) < min_heuristic)
        {
            min_heuristic = heuristic(*it);
            astar_idx = it;
        }
    }

    astar_board = *astar_idx; // Extract the BoardState to pop
    states.erase(astar_idx); // Erase it from the frontier
    return astar_board;
}


/**
 * This function checks whether the frontier is empty
*/
bool AStarFrontier::isEmpty()
{
    return states.empty();
}


/**
 * This function checks whether the frontier contains a BoardState already
 * or not. If the board state is found it returns true.
*/
bool AStarFrontier::contains(BoardState *board)
{
    vector<BoardState *>::iterator it;

    for (it = states.begin(); it != states.end(); it++)
    {
        if ((*it)->isSame(board))
            return true;
    }
    return false;
}
