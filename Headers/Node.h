#ifndef NODE_H
#define NODE_H

#include "Cube.h"
#include <vector>

class Node
{
private:
    Cube *state;
    Node *parent;
    Move *action;
    int gValue;
    int hValue;

public:
    Node(Cube *state, Node *parent, Move *action, int gValue, int hValue);

    Cube *getState();
    Node *getParent();
    Move *getAction();
    int getGValue();
    int getHValue();

    void setState(Cube *state);
    void setParent(Cube *parent);
    void setAction(Move* action);
    void setGValue(int gValue);
    void setHValue(int hValue);

    std::vector<Move*> extractSolution();

};

#endif