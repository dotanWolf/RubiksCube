#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include "Corner.h"
#include <array>
#include "Cube.h"
#include <vector>
using namespace std;

int main(int argc, char *argv[])
{
    map<string, Move*> moveMap;

    int f_mask[] = {1, 5, 2, 3, 0, 4, 6, 7};
    int f_diff[] = {2, 1, 0, 0, 1, 2, 0, 0};
    Move* FMove = new Move(f_mask, f_diff);
    moveMap["F"] = FMove;

    int u_mask[] = {3, 0, 1, 2, 4, 5, 6, 7};
    int u_diff[] = {0, 0, 0, 0, 0, 0, 0, 0};
    Move* UMove = new Move(u_mask, u_diff);
    moveMap["U"] = UMove;

    int d_mask[] = {0, 1, 2, 3, 5, 6, 7, 4};
    int d_diff[] = {0, 0, 0, 0, 0, 0, 0, 0};
    Move* DMove = new Move(d_mask, d_diff);
    moveMap["D"] = DMove;

    int b_mask[] = {1, 5, 2, 3, 0, 4, 6, 7};
    int b_diff[] = {0, 0, 1, 2, 0, 0, 2, 1};
    Move* BMove = new Move(b_mask, b_diff);
    moveMap["B"] = BMove;

    int r_mask[] = {4, 1, 2, 0, 7, 5, 6, 3};
    int r_diff[] = {2, 0, 0, 1, 1, 0, 0, 2};
    Move* RMove = new Move(r_mask, r_diff);
    moveMap["R"] = RMove;

    int l_mask[] = {0, 2, 6, 3, 4, 1, 5, 7};
    int l_diff[] = {0, 1, 2, 0, 0, 2, 1, 0};
    Move* LMove = new Move(l_mask, l_diff);
    moveMap["L"] = LMove;

    Cube cube(moveMap);
    cube.scramble();
    
    return 0;
}

vector<Move> A_Star(Cube cube) {
    
}