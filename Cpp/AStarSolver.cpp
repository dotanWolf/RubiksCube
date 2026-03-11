#include "Move.h"
#include "AStarSolver.h"
#include "Cube.h"
#include <stdlib.h>
#include "Node.h"
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <iostream>

struct CompareNode
{
    bool operator()(Node *a, Node *b)
    {
        return a->getGValue() + a->getHValue() > b->getGValue() + b->getHValue();
    }
};

vector<Move *> AStarSolver::solve(Cube *cube)
{
    int counter = 0;
    priority_queue<Node *, vector<Node *>, CompareNode> open;
    open.push(new Node(cube, NULL, NULL, 0, heuristic(cube)));
    set<string> closed;
    map<string, int> distance;

    while (!open.empty())
    {
        counter++;
        Node *currentNode = open.top();
        Cube *currentState = currentNode->getState();
        string currentKey = currentState->getKey();
        open.pop();
        // std::cout << counter << std::endl;
        if (closed.find(currentKey) == closed.end() || currentNode->getGValue() < distance[currentKey])
        {
            closed.insert(currentKey);


            distance[currentKey] = currentNode->getGValue();


            if (currentState->isGoal())
            {

                return currentNode->extractSolution();
            }
            for (auto &[move, newState] : currentState->succesor())
            {
                Node *newNode = new Node(newState, currentNode, move, currentNode->getGValue() + 1, heuristic(newState));
                open.push(newNode);
            }
        }
    }
    std::cout << "returned nothing" << std::endl;
    return {};
}

int AStarSolver::heuristic(Cube *cube)
{
    return 0;
}