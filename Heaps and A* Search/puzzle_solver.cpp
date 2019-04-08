#include <iostream>
#include <sstream>
#include <iomanip>
#include <map>
#include <cmath>
#include <cstdlib>
#include <stdexcept>
#include <algorithm>
#include <deque>
#include <set>
#include <vector>
#include "heap.h"
#include "board.h"
#include "puzzle_move.h"
#include "puzzle_heur.h"
#include "puzzle_solver.h"

using namespace std;

//constructor
PuzzleSolver::PuzzleSolver(const Board &b, PuzzleHeuristic* ph):
b_(b), ph_(ph){}

// Destructor
PuzzleSolver::~PuzzleSolver()
{

}

// Run the A* search and builds the solution and tracks
// the number of expansions
void PuzzleSolver::run()
{
    expansions_ = 0;
    PuzzleMoveScoreComp score_comp;
    PuzzleMoveBoardComp board_comp;
    PuzzleMoveSet closed_list(board_comp);
    Heap<PuzzleMove*, PuzzleMoveScoreComp> open_list(2, score_comp);
    PuzzleMove* initial = new PuzzleMove(&b_);
    (initial->h) = ph_->compute(*(initial->b));
    //now that heuristic is calculated on inital push
    open_list.push(initial);
    closed_list.insert(initial);
    //helps with memory management
    set<Board*> check_dup;
    //the open list is not empty
    while(!open_list.empty())
    {
        //grab top of heap
        PuzzleMove* temp = open_list.top();
        open_list.pop();
        //check if solved
        if(temp->b->solved())
        {
            //trace back
            while(temp->prev!=nullptr)
            {
                solution_.push_front(temp->tileMove);
                temp = temp->prev;
            }   
            break;
        }
        else
        {
            map<int, Board*> potentialmoves = temp->b->potentialMoves();
            map<int, Board*>::iterator it = potentialmoves.begin();
            //adding new moves
            for(; it != potentialmoves.end(); ++it)
            {
                check_dup.insert(it->second);
                PuzzleMove* temp_move = new PuzzleMove(it->first, it->second, temp);
                //if not in open or closed list
                if(closed_list.find(temp_move)  == closed_list.end())
                {
                    (temp_move->h) = ph_->compute(*(temp_move->b));
                    open_list.push(temp_move);
                    closed_list.insert(temp_move);
                    expansions_++;
                }
                //if not delete
                else
                {
                    delete temp_move;
                }
            }
        } 
    }
    //clean up memory
    set<Board*>::iterator it = check_dup.begin();
    for(; it!= check_dup.end(); ++it)
    {
        delete *it;
    }
    PuzzleMoveSet::iterator i = closed_list.begin();
    for(; i!=closed_list.end(); ++i)
    {
        delete *i;
    }
}

// Return the solution deque
std::deque<int> PuzzleSolver::getSolution()
{
    return solution_;
}

// Return how many expansions were performed in the search
int PuzzleSolver::getNumExpansions()
{
    return expansions_;
}
