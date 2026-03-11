#include "Cube.h"
#include <stdio.h>
#include <iostream>
#include <iterator>
#include <random>
#include <map>

Cube::Cube(map<string, Move *> moveMap)
{
    for (int i = 0; i < 8; i++)
    {
        corners[i] = Corner(i, 0);
    }
    this->moveMap = moveMap;
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

void Cube::scramble()
{
    for (int i = 0; i < 50; i++)
    {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, this->moveMap.size() - 1);
        int randomIndex = dis(gen);
        auto it = std::next(this->moveMap.begin(), randomIndex);
        this->applyMove(it->second->getMask(), it->second->getDiff());
    }
}