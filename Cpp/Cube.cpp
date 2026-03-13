#include "Cube.h"
#include <stdio.h>
#include <iostream>
#include <iterator>
#include <random>
#include <map>
#include "Move.h"
#include <array>
#include <random>
#include "MoveFactory.h"

using namespace std;
Cube::Cube()
{
    for (int i = 0; i < 8; i++)
    {
        corners[i] = Corner(i, 0);
    }
    for (int i = 0; i < 12; i++)
    {
        edges[i] = Edge(i, 0);
    }
    moves = {"U", "U'", "D", "D'", "F", "F'", "B", "B'", "R", "R'", "L", "L'"};
    factory = new MoveFactory();
}

Cube::Cube(array<Corner, 8> corners, array<Edge, 12> edges, map<string, Move *> moveMap)
{
    this->corners = corners;
    this->moveMap = moveMap;
    this->edges = edges;
}

Cube::Cube(Cube *cube)
{
    this->corners = cube->corners;
    this->edges = cube->edges;
    this->factory = cube->factory;
    this->moves = cube->moves;
    this->moveMap = cube->moveMap;

}

void Cube::applyMove(string moveName)
{
    Move *move = factory->getMove(moveName);
    array<Corner, 8> newCorners;

    for (int i = 0; i < 8; i++)
    {
        newCorners[i].setIndex(corners[move->getCornerMask()[i]].getIndex());
        newCorners[i].setOrientation((corners[move->getCornerMask()[i]].getOrientation() + move->getCornerOriDiff()[i]) % 3);
    }
    array<Edge, 12> newEdges;
    for (int i = 0; i < 12; i++)
    {

        newEdges[i].setIndex(edges[move->getEdgeMask()[i]].getIndex());
        newEdges[i].setOrientation((edges[move->getEdgeMask()[i]].getOrientation() + move->getEdgeOriDiff()[i]) % 2);
    }

    for (int i = 0; i < 8; i++)
    {

        corners[i] = newCorners[i];
    }
    for (int i = 0; i < 12; i++)
    {

        edges[i] = newEdges[i];
    }
}

void Cube::showState()
{
    for (int i = 0; i < 8; i++)
    {
        cout << "Corner index " << corners[i].getIndex() << " " << "at spot " << i << endl;
        cout << "With Ori " << corners[i].getOrientation() << endl;
    }
}

string Cube::getKey()
{
    string key = "";
    for (auto &corner : corners)
    {
        key += to_string(corner.getIndex());
        key += to_string(corner.getOrientation());
    }
    for (auto &edge : edges)
    {
        key += to_string(edge.getIndex());
        key += to_string(edge.getOrientation());
    }
    return key;
}

bool Cube::isGoal()
{
    for (int i = 0; i < corners.size(); i++)
    {
        if (corners[i].getIndex() != i || corners[i].getOrientation() != 0)
        {

            return false;
        }
    }
    for (int i = 0; i < edges.size(); i++)
    {
        if (edges[i].getIndex() != i || edges[i].getOrientation() != 0)
        {

            return false;
        }
    }
    return true;
}

map<Move *, Cube *> Cube::succesor()
{

    map<Move *, Cube *> succesorMap;
    for (auto &moveName : moves)
    {

        Cube *newCube = new Cube(this);
        Move *move = factory->getMove(moveName);
        newCube->applyMove(moveName);
        succesorMap[move] = newCube;
    }
    // std::cout << succesorMap.size() << std::endl;
    return succesorMap;
}

map<string, Move *> Cube::getMoveMap()
{
    return moveMap;
}

array<Corner, 8> Cube::getCorners()
{
    return corners;
}

std::string Cube::chooseRandomMove()
{

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, moves.size() - 1);
    return moves[dis(gen)];
}

int Cube::NumMisplacedPieces()
{
    int counter = 0;
    for (int i = 0; i < corners.size(); i++)
    {
        if (corners[i].getIndex() != i || corners[i].getOrientation() != 0)
        {

            counter++;
        }
    }
    for (int i = 0; i < edges.size(); i++)
    {
        if (edges[i].getIndex() != i || edges[i].getOrientation() != 0)
        {

            counter++;
        }
    }
    return counter;
}
int Cube::numPiecesInFace()
{
    return 8;
}
