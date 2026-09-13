#ifndef MOVEFACTORY_H
#define MOVEFACTORY_H

#include "Move.h"
#include <map>
#include <string>
using namespace std;

class MoveFactory
{
private:
    map<string, Move *> nameToMove;

public:
    MoveFactory();
    Move *getMove(string moveName);
};

#endif
