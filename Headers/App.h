#ifndef APP_H
#define APP_H

#include "Cube.h"
#include "AStarSolver.h"
#include "Move.h"
#include <vector>

class App {
    private:
        AStarSolver* solver;
        Cube* cube;
        vector<Move*> solution;
    public:
        App(AStarSolver* solver, Cube* cube);
        void scramble();
        void solve();
        Cube* getCube();
};

#endif