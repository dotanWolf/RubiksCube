#include "AStarSolver.h"
#include "App.h"
#include "Cube.h"
#include <string>
#include <iostream>
int main(int argc, char *argv[])
{
    AStarSolver *solver = new AStarSolver();
    Cube *cube = new Cube(3);
    App app(solver, cube);

    std::string scramble = app.scramble();
    std::cout << scramble << std::endl;
    // cube->applyMove("L");
    // cube->showState();
    std::string solution =  app.solve();
    std::cout << solution << std::endl;
    // app.getCube()->showState();

    return 0;
}