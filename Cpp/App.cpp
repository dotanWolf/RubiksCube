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

App::App(AStarSolver *solver, Cube* cube)
{
    this->solver = solver;
    this->cube = cube;
    this->solution = {};
}

void App::scramble()
{
    std::cout << "Scramble is" << std::endl;
    for (int i = 0; i < 20; i++)
    {
        std::string name = cube->chooseRandomMove();
        std::cout << name << " ";

        cube->applyMove(name);
    }
    std::cout << std::endl;
    cube->showState();
}

void App::solve()
{

    solution = solver->solve(cube);
    std::cout << "Solution is" << std::endl;
    numOfMoves = solution.size();
    for (auto &move : solution)
    {
        std::cout << move->getName() << " ";
        std::cout << "this is the number of moves: " << numOfMoves << std::endl;
    }
}

Cube *App::getCube()
{
    return cube;
}
