#include "Move.h"
#include <string>
#include <vector>
using namespace std;

Move::Move(vector<int> cornerMask, vector<int> cornerOriDiff, vector<int> edgeMask, vector<int> edgeOriDiff, std::string name)
{
    this->cornerMask = cornerMask;
    this->cornerOriDiff = cornerOriDiff;
    this->edgeMask = edgeMask;
    this->edgeOriDiff = edgeOriDiff;
    this->name = name;
}

std::string Move::getName()
{
    return name;
}

vector<int> Move::getCornerMask()
{
    return cornerMask;
}
vector<int> Move::getCornerOriDiff()
{
    return cornerOriDiff;
}
vector<int> Move::getEdgeMask()
{
    return edgeMask;
}
vector<int> Move::getEdgeOriDiff()
{
    return edgeOriDiff;
}