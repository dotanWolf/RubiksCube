#ifndef ASTARSOLVER_H
#define ASTARSOLVER_H

#include "Cube.h"
#include "CubieCube.h"
#include "Move.h"
#include <cstdint>
#include <vector>
#include <map>
#include <string>

class AStarSolver
{
private:
    map<string, int> cornerPatternDb;
    vector<int8_t> twistPrune;
    vector<int8_t> flipSlicePrune;
    vector<int8_t> cornerPrune;
    vector<int8_t> edgeSlicePrune;
    bool tablesReady = false;

    void buildTables();
    int phase1Heuristic(const CubieCube &cube) const;
    int phase2Heuristic(const CubieCube &cube) const;
    int searchPhase1(CubieCube &cube, int g, int bound, int lastMove, std::vector<int> &path);
    int searchPhase2(CubieCube &cube, int g, int bound, int lastMove, std::vector<int> &path);
    std::vector<Move *> solve3x3(Cube *cube);
    std::vector<Move *> solve2x2(Cube *cube);
    static bool allowed(int move, int lastMove);

public:
    AStarSolver();
    vector<Move *> solve(Cube *cube);
    int heuristic(Cube *cube);
};

#endif
