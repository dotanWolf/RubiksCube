#include "SearchNode.h"
#include "Cube.h"
#include "Move.h"
#include <vector>
#include <iostream>

using namespace std;

SearchNode::SearchNode(Cube *state, SearchNode *parent, Move *action, int gValue, int hValue)
{
    this->state = state;
    this->parent = parent;
    this->action = action;
    this->gValue = gValue;
    this->hValue = hValue;
}

vector<Move *> SearchNode::extractSolution()
{
    vector<Move *> solution;
    SearchNode *currentSearchNode = this;
    while (currentSearchNode->getParent() != nullptr)
    {
        solution.insert(solution.begin(), currentSearchNode->getAction());
        currentSearchNode = currentSearchNode->getParent();
    }
    return solution;
}

int SearchNode::getGValue()
{
    return gValue;
}

SearchNode *SearchNode::getParent()
{
    return parent;
}

Move *SearchNode::getAction()
{
    return action;
}

Cube *SearchNode::getState()
{
    return state;
}

int SearchNode::getHValue()
{
    return hValue;
}

void SearchNode::setState(Cube *state)
{
    this->state = state;
}

void SearchNode::setParent(SearchNode *parent)
{
    this->parent = parent;
}

void SearchNode::setAction(Move *action)
{
    this->action = action;
}

void SearchNode::setGValue(int gValue)
{
    this->gValue = gValue;
}

void SearchNode::setHValue(int hValue)
{
    this->hValue = hValue;
}