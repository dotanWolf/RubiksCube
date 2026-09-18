#include "App.h"
#include "AStarSolver.h"
#include <random>
#include "Cube.h"
#include <iostream>

App::App(AStarSolver *solver, Cube *cube)
{
    this->solver = solver;
    this->cube = cube;
    this->solution = {};
}

std::string App::scramble()
{
    std::string lastMove = "";
    std::string scramble = "";
    for (int i = 0; i < 20; i++)
    {
        std::string name = cube->chooseRandomMove(lastMove);
        scramble += name;
        scramble += " ";
        cube->applyMove(name);
        lastMove = name;
    }
    return scramble;
}

std::string App::solve()
{
    std::string solutionString = "";

    solution = solver->solve(cube);
    // std::cout << "Solution is" << std::endl;
    int numOfMoves = solution.size();
    for (auto &move : solution)
    {
        solutionString += move->getName();
        solutionString += " ";
        cube->applyMove(move->getName());

        // std::cout << move->getName() << " ";
    }
    // std::cout << "this is the number of moves: " << numOfMoves << std::endl;
    return solutionString;
}

Cube *App::getCube()
{
    return cube;
}
