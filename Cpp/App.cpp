#include "App.h"
#include "AStarSolver.h"
#include <random>
#include "Cube.h"
#include <iostream>

void printMap(map<string, Move *> moveMap)
{
    for (auto &[name, move] : moveMap)
    {
        std::cout << move->getDiff()[0] << std::endl;
    }
}

App::App(AStarSolver *solver)
{
    this->solver = solver;
    this->cube = new Cube();
    this->solution = {};
}

void App::scramble()
{
    map<string, Move *> moveMap = cube->getMoveMap();
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, cube->getMoveMap().size() - 1);
    for (int i = 0; i < 6; i++)
    {
        int randomIndex = dis(gen);
        auto it = std::next(cube->getMoveMap().begin(), randomIndex);
        int *mask = it->second->getMask();
        int *diff = it->second->getDiff();

        cube->applyMove(it->second->getMask(), it->second->getDiff());
    }
}

void App::solve()
{
    solution = solver->solve(cube);
    for (auto &move : solution)
    {
        std::cout << move->getName() << " " << std::endl;
    }
}

Cube *App::getCube()
{
    return cube;
}
