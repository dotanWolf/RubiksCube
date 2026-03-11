#ifndef CUBE_H
#define CUBE_H

#include "Corner.h"
#include <array>
#include <map>
#include <string>
#include "Move.h"
using namespace std;

class Cube
{
private:
    array<Corner, 8> corners;
    map<string, Move *> moveMap;

public:
    Cube(map<string, Move *> moveMap);
    void applyMove(int mask[], int ori_diff[]);
    void showState();
    void scramble();
};

#endif