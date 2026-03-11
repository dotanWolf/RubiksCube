#include "Node.h"
#include <vector>
#include <iostream>

Node::Node(Cube *state, Node *parent, Move *action, int gValue, int hValue)
{
    this->state = state;
    this->parent = parent;
    this->action = action;
    this->gValue = gValue;
    this->hValue = hValue;
}

vector<Move *> Node::extractSolution()
{
    vector<Move *> solution;
    Node *currentNode = this;
    while (currentNode->getParent() != NULL)
    {
        solution.insert(solution.begin(), currentNode->getAction());
        currentNode = currentNode->getParent();
    }
    return solution;
}

int Node::getGValue()
{
    return gValue;
}

Node *Node::getParent()
{
    return parent;
}

Move *Node::getAction()
{
    return action;
}

Cube *Node::getState()
{
    return state;
}

int Node::getHValue() {
    return hValue;
}
