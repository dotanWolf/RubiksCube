#ifndef MOVEFACTORY_H
#define MOVEFACTORY_H

#include <map>
#include <string>
#include <vector>
#include "Move.h"
using namespace std;

class MoveFactory {
    private:
        map<string,vector<vector<int>>> nameToMove;
    public:
        MoveFactory();
        Move* getMove(string moveName);
};

#endif