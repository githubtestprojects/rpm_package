#include <iostream>
#include <fstream>
#include "puzzle_solver.h"

using namespace std;

int main()
{
    int r = 0, c = 0, num, puzzle_num = 1;
    int data[4][4];
    BoardState *board;
    vector<BoardState *> solution;
    move_t prev_m;
    BoardState *prev_s;

    ifstream input_file("15_puzzles.txt");
    ofstream output_file("output.txt");


    // Read from input file until no more data is found
    while (input_file >> num)
    {
        data[r][c] = num;

        // Increment c. If it reaches 4, reset it to 0 and increment r.
        // If r also reaches 4, it means we have read 16 numbers to fill the
        // 15-puzzle board with and so we try and solve it. We further reset r
        // and c to 0 to get more data.
        c++;
        if (c == 4)
        {
            c = 0;
            r++;
        }
        if (r == 4)
        {
            r = 0;

            cout << "Solving Puzzle # " << puzzle_num << "..." << endl;

            // Create a new initial board
            board = new BoardState(data, NULL, NONE);

            if (!board->isSolvable())
            {
                output_file << puzzle_num << ", not solvable";
                output_file << endl;
                output_file << endl;
            }
            else
            {
                output_file << puzzle_num << ", solvable, ";
                solution = solve(board);

                // If solution size is greater than 1000 moves
                // treat it as not solved.
                if (solution.size() >= 1000)
                {
                    output_file << "not solved, 1000";
                    output_file << endl;
                    output_file << endl;
                }
                else
                {
                    output_file << "solved, " << solution.size();
                    if (solution.size() > 0)
                        output_file << ":";
                    output_file << endl;

                    // Take out BoardStates from the solution and output the 
                    // moves made for reaching those states one by one
                    while (!solution.empty())
                    {
                        board = solution.back();
                        solution.pop_back();
                        prev_m = board->prev_move;
                        prev_s = board->prev_state;

                        switch (prev_m)
                        {
                        case UP:
                            output_file << prev_s->blank_pos_r + 1 << " " << prev_s->blank_pos_c << " U" << endl;
                            break;

                        case DOWN:
                            output_file << prev_s->blank_pos_r - 1 << " " << prev_s->blank_pos_c << " D" << endl;
                            break;

                        case LEFT:
                            output_file << prev_s->blank_pos_r << " " << prev_s->blank_pos_c + 1 << " L" << endl;
                            break;

                        case RIGHT:
                            output_file << prev_s->blank_pos_r << " " << prev_s->blank_pos_c - 1 << " R" << endl;
                            break;

                        default:
                            break;
                        }
                    }
                    output_file << endl;
                }
            }

            puzzle_num++;
        }
    }

    return 0;
}