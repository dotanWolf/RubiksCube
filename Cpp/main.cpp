#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include "Corner.h"
#include <array>
#include "Cube.h"
#include <vector>
#include "AStarSolver.h"
#include "App.h"

using namespace std;

int main(int argc, char *argv[])
{
    AStarSolver *solver = new AStarSolver();
    App app(solver);

    app.scramble();

    app.solve();
    // app.getCube()->showState();

    return 0;
}