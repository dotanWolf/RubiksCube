#include "Cube.h"
#include <stdio.h>
#include <iostream>
#include <iterator>
#include <random>
#include <map>
#include "Move.h"
#include <array>

Cube::Cube()
{
    for (int i = 0; i < 8; i++)
    {
        corners[i] = Corner(i, 0);
    }

    int f_mask[] = {1, 5, 2, 3, 0, 4, 6, 7};
    int f_diff[] = {2, 1, 0, 0, 1, 2, 0, 0};
    moveMap["F"] = new Move(f_mask, f_diff, "F");

    int u_mask[] = {3, 0, 1, 2, 4, 5, 6, 7};
    int u_diff[] = {0, 0, 0, 0, 0, 0, 0, 0};
    moveMap["U"] = new Move(u_mask, u_diff, "U");

    int d_mask[] = {0, 1, 2, 3, 5, 6, 7, 4};
    int d_diff[] = {0, 0, 0, 0, 0, 0, 0, 0};
    moveMap["D"] = new Move(d_mask, d_diff, "D");

    int b_mask[] = {1, 5, 2, 3, 0, 4, 6, 7};
    int b_diff[] = {0, 0, 1, 2, 0, 0, 2, 1};
    moveMap["B"] = new Move(b_mask, b_diff, "B");

    int r_mask[] = {4, 1, 2, 0, 7, 5, 6, 3};
    int r_diff[] = {2, 0, 0, 1, 1, 0, 0, 2};
    moveMap["R"] = new Move(r_mask, r_diff, "R");

    int l_mask[] = {0, 2, 6, 3, 4, 1, 5, 7};
    int l_diff[] = {0, 1, 2, 0, 0, 2, 1, 0};
    moveMap["L"] = new Move(l_mask, l_diff, "L");
}

Cube::Cube(array<Corner, 8> corners, map<string, Move *> moveMap)
{
    this->corners = corners;
    this->moveMap = moveMap;
}

Cube::Cube(Cube *cube)
{
    this->corners = cube->corners;
    this->moveMap = cube->moveMap;
}

void Cube::applyMove(int mask[], int ori_diff[])
{
    array<Corner, 8> newCorners;

    for (int i = 0; i < 8; i++)
    {
        newCorners[i].setIndex(corners[mask[i]].getIndex());
        newCorners[i].setOrientation((corners[mask[i]].getOrientation() + ori_diff[i]) % 3);
    }
    for (int i = 0; i < 8; i++)
    {
        corners[i] = newCorners[i];
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
        key += corner.getIndex();
        key += corner.getOrientation();
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
    return true;
}

map<Move *, Cube *> Cube::succesor()
{
    map<Move *, Cube *> succesorMap;
    for (auto &[moveName, move] : moveMap)
    {
        Cube *newCube = new Cube(this);
        newCube->applyMove(move->getMask(), move->getDiff());
        succesorMap[move] = newCube;
    }
    // std::cout << succesorMap.size() << std::endl;
    return succesorMap;
}

map<string, Move *> Cube::getMoveMap()
{
    return moveMap;
}
