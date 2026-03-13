#include "App.h"
#include "AStarSolver.h"
#include <random>
#include "Cube.h"
#include <iostream>

// void printMap(map<string, Move *> moveMap)
// {
//     for (auto &[name, move] : moveMap)
//     {
//         std::cout << move->getDiff()[0] << std::endl;
//     }
// }

App::App(AStarSolver *solver)
{
    this->solver = solver;
    this->cube = new Cube();
    this->solution = {};
}

void App::scramble()
{
    std::cout << "Scramble is" << std::endl;
    for (int i = 0; i < 8; i++)
    {
        std::string name = cube->chooseRandomMove();
        std::cout << name << " ";

        cube->applyMove(name);
        // cube->showState();
    }
    std::cout << std::endl;
}

void App::solve()
{

    solution = solver->solve(cube);
    std::cout << "Solution is" << std::endl;

    for (auto &move : solution)
    {
        std::cout << move->getName() << " ";
    }
    std::cout << std::endl;
}

Cube *App::getCube()
{
    return cube;
}
