#include <iostream>
#include <sstream>
#include <iomanip>
#include <map>
#include <cmath>
#include <cstdlib>
#include <stdexcept>
#include <algorithm>
#include "board.h"
#include "puzzle_move.h"
#include "puzzle_heur.h"

using namespace std;

//find manhattan h for specific tile
int calcH(const Board& b, int tile_idx)
{
    int h;
    int correctrow = b[tile_idx]/b.dim();
    int correctcol = b[tile_idx]%b.dim();
    int curr_row = tile_idx/b.dim();
    int curr_col = tile_idx%b.dim();
    h = abs(correctrow-curr_row) + abs(correctcol-curr_col);
    return h;
}

//sum h for manhattan 
int PuzzleManhattanHeuristic::compute(const Board& b)
{
    int total_h = 0;
    for(int i = 0; i<b.size(); i++)
    {
        if(b[i] != 0)
        {
            total_h += calcH(b, i);
        }
    }
    return total_h;
}

//sum h for out of place
int PuzzleOutOfPlaceHeuristic::compute(const Board& b)
{
    int total_h = 0;
    for(int i = 0; i<b.size(); i++)
    {
        if(b[i] != i && b[i] != 0)
        {
            total_h++;
        }
    }
    return total_h;
}

//sum h for BFS
int PuzzleBFSHeuristic::compute(const Board& b)
{
    return 0;
}
