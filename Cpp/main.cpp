#include "AStarSolver.h"
#include "App.h"
#include "Cube.h"

int main(int argc, char *argv[])
{
    AStarSolver *solver = new AStarSolver();
    Cube *cube = new Cube(3);
    App app(solver, cube);

    app.scramble();
    // cube->applyMove("L");
    // cube->showState();
    app.solve();
    // app.getCube()->showState();

    return 0;
}