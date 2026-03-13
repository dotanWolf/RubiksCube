#ifndef MOVE_H
#define MOVE_H

#include <string>
#include <vector>
using namespace std;
class Move
{
private:
    vector<int> cornerMask;
    vector<int> cornerOriDiff;
    vector<int> edgeMask;
    vector<int> edgeOriDiff;
    std::string name;

public:
    Move(vector<int> cornerMask, vector<int> cornerOriDiff, vector<int> edgeMask, vector<int> edgeOriDiff, std::string name);
    vector<int> getCornerMask();
    vector<int> getCornerOriDiff();
    vector<int> getEdgeMask();
    vector<int> getEdgeOriDiff();
    std::string getName();
};

#endif