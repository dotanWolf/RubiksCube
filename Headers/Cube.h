#ifndef CUBE_H
#define CUBE_H

#include "Corner.h"
#include <array>
#include <map>
#include <string>
#include "Move.h"
#include "Edge.h"
#include "MoveFactory.h"
#include <string>
#include <vector>
using namespace std;

class Cube
{
private:
    array<Corner, 8> corners;
    array<Edge, 12> edges;
    vector<string> moves;
    MoveFactory* factory;
    map<string, Move *> moveMap;


public:
    Cube(array<Corner,8 > corners, array<Edge, 12> edges, map<string, Move *> moveMap);
    Cube();
    Cube(Cube* cube);
    void applyMove(string moveName);
    void showState();
    map<string, Move *> getMoveMap();
    string getKey();
    bool isGoal();
    map<Move*, Cube*> succesor();
    array<Corner, 8> getCorners();
    std::string chooseRandomMove();
    int NumMisplacedPieces();
    int numPiecesInFace();
};

#endif