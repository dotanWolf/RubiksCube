#ifndef SEARCH_NODE_H
#define SEARCH_NODE_H

#include <vector>

// Forward declarations break circular include chains
class Cube;
class Move;

class SearchNode
{
private:
    Cube *state;
    SearchNode *parent;
    Move *action;
    int gValue;
    int hValue;

public:
    SearchNode(Cube *state, SearchNode *parent, Move *action, int gValue, int hValue);

    Cube *getState();
    SearchNode *getParent();
    Move *getAction();
    int getGValue();
    int getHValue();

    void setState(Cube *state);
    void setParent(SearchNode *parent);
    void setAction(Move *action);
    void setGValue(int gValue);
    void setHValue(int hValue);

    std::vector<Move *> extractSolution();
};

#endif // SearchNode_H