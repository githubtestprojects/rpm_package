#include <vector>
#include "board_state.h"

using namespace std;


/**
 * The class AStarFrontier represents a data structure based on a priority queue
 * which contains BoardStates.
 * The priority of any BoardState is dependent on the heuristic function which is 
 * the Manhattan distance of each board. The lower the Manhattan distance of a board,
 * the higher its priority. This class is used as a structure to store explored and
 * unexplored BoardStates when applying an A* search for a solution.
*/
class AStarFrontier
{
private:
    // A vector of BoardStates to store
    vector<BoardState *> states;

public:
    void print();
    void push(BoardState *board);
    BoardState *pop();
    int heuristic(BoardState *board);
    bool isEmpty();
    bool contains(BoardState *board);
};