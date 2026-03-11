#ifndef ASTARSOLVER_H
#define ASTARSOLVER_H

#include "Cube.h"
#include "Move.h"
#include <vector>

class AStarSolver
{
private:
public:
    vector<Move*> solve(Cube *cube);
    int heuristic(Cube *cube);
};

#endif