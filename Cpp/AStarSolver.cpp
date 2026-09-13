#include "AStarSolver.h"
#include "CubieCube.h"
#include "Node.h"
#include <algorithm>
#include <iostream>
#include <queue>
#include <set>

using namespace std;

namespace
{
const int TWIST_N = 2187;
const int FLIP_N = 2048;
const int SLICE_N = 495;
const int FLIPSLICE_N = FLIP_N * SLICE_N;
const int CORNER_N = 40320;
const int EDGE8_N = 40320;
const int SLICEPERM_N = 24;
const int EDGESLICE_N = EDGE8_N * SLICEPERM_N;
const int INF = 1000;

bool allowedMove(int move, int lastMove)
{
    if (lastMove < 0)
    {
        return true;
    }
    int face = move / 3;
    int lastFace = lastMove / 3;
    if (face == lastFace)
    {
        return false;
    }
    if (face / 2 == lastFace / 2 && face < lastFace)
    {
        return false;
    }
    return true;
}
} // namespace

void initilizeDb(map<string, int> &Db)
{
    queue<Cube *> nodeQueue;
    Cube *solvedCube = new Cube(2);
    nodeQueue.push(solvedCube);
    Db[solvedCube->getKey()] = 0;
    int distance = 0;

    while (!nodeQueue.empty())
    {
        int layerSize = nodeQueue.size();
        for (int i = 0; i < layerSize; i++)
        {
            Cube *currentCube = nodeQueue.front();
            nodeQueue.pop();
            for (auto &[move, newState] : currentCube->succesor())
            {
                if (Db.find(newState->getKey()) == Db.end())
                {
                    Db[newState->getKey()] = distance + 1;
                    nodeQueue.push(newState);
                }
            }
        }
        cout << "Finished depth " << distance << " db size: " << Db.size() << endl;
        distance++;
    }
}

AStarSolver::AStarSolver() {}

bool AStarSolver::allowed(int move, int lastMove)
{
    return allowedMove(move, lastMove);
}

void AStarSolver::buildTables()
{
    if (tablesReady)
    {
        return;
    }
    CubieCube::initMoveTables();

    twistPrune.assign(TWIST_N, -1);
    flipSlicePrune.assign(FLIPSLICE_N, -1);
    cornerPrune.assign(CORNER_N, -1);
    edgeSlicePrune.assign(EDGESLICE_N, -1);

    {
        queue<CubieCube> q;
        CubieCube start;
        start.identity();
        twistPrune[start.twist()] = 0;
        q.push(start);
        while (!q.empty())
        {
            CubieCube cur = q.front();
            q.pop();
            int d = twistPrune[cur.twist()];
            for (int m = 0; m < 18; m++)
            {
                CubieCube nxt = cur;
                nxt.move(m);
                int coord = nxt.twist();
                if (twistPrune[coord] < 0)
                {
                    twistPrune[coord] = (int8_t)(d + 1);
                    q.push(nxt);
                }
            }
        }
    }

    {
        queue<CubieCube> q;
        CubieCube start;
        start.identity();
        int startCoord = start.flip() * SLICE_N + start.slice();
        flipSlicePrune[startCoord] = 0;
        q.push(start);
        while (!q.empty())
        {
            CubieCube cur = q.front();
            q.pop();
            int d = flipSlicePrune[cur.flip() * SLICE_N + cur.slice()];
            for (int m = 0; m < 18; m++)
            {
                CubieCube nxt = cur;
                nxt.move(m);
                int coord = nxt.flip() * SLICE_N + nxt.slice();
                if (flipSlicePrune[coord] < 0)
                {
                    flipSlicePrune[coord] = (int8_t)(d + 1);
                    q.push(nxt);
                }
            }
        }
    }

    {
        queue<CubieCube> q;
        CubieCube start;
        start.identity();
        cornerPrune[start.cornerPerm()] = 0;
        q.push(start);
        while (!q.empty())
        {
            CubieCube cur = q.front();
            q.pop();
            int d = cornerPrune[cur.cornerPerm()];
            for (int mi = 0; mi < 10; mi++)
            {
                int m = CubieCube::PHASE2_MOVES[mi];
                CubieCube nxt = cur;
                nxt.move(m);
                int coord = nxt.cornerPerm();
                if (cornerPrune[coord] < 0)
                {
                    cornerPrune[coord] = (int8_t)(d + 1);
                    q.push(nxt);
                }
            }
        }
    }

    {
        queue<CubieCube> q;
        CubieCube start;
        start.identity();
        int startCoord = start.udEdgePerm() * SLICEPERM_N + start.slicePerm();
        edgeSlicePrune[startCoord] = 0;
        q.push(start);
        while (!q.empty())
        {
            CubieCube cur = q.front();
            q.pop();
            int d = edgeSlicePrune[cur.udEdgePerm() * SLICEPERM_N + cur.slicePerm()];
            for (int mi = 0; mi < 10; mi++)
            {
                int m = CubieCube::PHASE2_MOVES[mi];
                CubieCube nxt = cur;
                nxt.move(m);
                int coord = nxt.udEdgePerm() * SLICEPERM_N + nxt.slicePerm();
                if (edgeSlicePrune[coord] < 0)
                {
                    edgeSlicePrune[coord] = (int8_t)(d + 1);
                    q.push(nxt);
                }
            }
        }
    }

    tablesReady = true;
}

int AStarSolver::phase1Heuristic(const CubieCube &cube) const
{
    int a = twistPrune[cube.twist()];
    int b = flipSlicePrune[cube.flip() * SLICE_N + cube.slice()];
    return max(a, b);
}

int AStarSolver::phase2Heuristic(const CubieCube &cube) const
{
    int a = cornerPrune[cube.cornerPerm()];
    int b = edgeSlicePrune[cube.udEdgePerm() * SLICEPERM_N + cube.slicePerm()];
    return max(a, b);
}

int AStarSolver::searchPhase1(CubieCube &cube, int g, int bound, int lastMove, vector<int> &path)
{
    int h = phase1Heuristic(cube);
    int f = g + h;
    if (f > bound)
    {
        return f;
    }
    if (h == 0)
    {
        return -1;
    }
    int minOver = INF;
    for (int m = 0; m < 18; m++)
    {
        if (!allowed(m, lastMove))
        {
            continue;
        }
        cube.move(m);
        path.push_back(m);
        int t = searchPhase1(cube, g + 1, bound, m, path);
        if (t == -1)
        {
            return -1;
        }
        minOver = min(minOver, t);
        path.pop_back();
        cube.move(CubieCube::inverse(m));
    }
    return minOver;
}

int AStarSolver::searchPhase2(CubieCube &cube, int g, int bound, int lastMove, vector<int> &path)
{
    int h = phase2Heuristic(cube);
    int f = g + h;
    if (f > bound)
    {
        return f;
    }
    if (h == 0)
    {
        return cube.isSolved() ? -1 : INF;
    }
    int minOver = INF;
    for (int mi = 0; mi < 10; mi++)
    {
        int m = CubieCube::PHASE2_MOVES[mi];
        if (!allowed(m, lastMove))
        {
            continue;
        }
        cube.move(m);
        path.push_back(m);
        int t = searchPhase2(cube, g + 1, bound, m, path);
        if (t == -1)
        {
            return -1;
        }
        minOver = min(minOver, t);
        path.pop_back();
        cube.move(CubieCube::inverse(m));
    }
    return minOver;
}

vector<Move *> AStarSolver::solve3x3(Cube *cube)
{
    buildTables();
    CubieCube state = CubieCube::fromCube(*cube);
    vector<int> phase1;
    int bound = phase1Heuristic(state);
    while (bound < INF)
    {
        int t = searchPhase1(state, 0, bound, -1, phase1);
        if (t == -1)
        {
            break;
        }
        bound = t;
    }

    CubieCube after = CubieCube::fromCube(*cube);
    for (int m : phase1)
    {
        after.move(m);
    }

    vector<int> phase2;
    int last = phase1.empty() ? -1 : phase1.back();
    bound = phase2Heuristic(after);
    while (bound < INF)
    {
        int t = searchPhase2(after, 0, bound, last, phase2);
        if (t == -1)
        {
            break;
        }
        if (t == bound)
        {
            bound++;
        }
        else
        {
            bound = t;
        }
    }

    CubieCube check = CubieCube::fromCube(*cube);
    for (int m : phase1)
    {
        check.move(m);
    }
    for (int m : phase2)
    {
        check.move(m);
    }
    if (!check.isSolved())
    {
        std::cout << "solver failed to reach solved cubies" << std::endl;
    }

    vector<Move *> solution;
    for (int m : phase1)
    {
        solution.push_back(cube->getMove(CubieCube::MOVE_NAMES[m]));
    }
    for (int m : phase2)
    {
        solution.push_back(cube->getMove(CubieCube::MOVE_NAMES[m]));
    }
    return solution;
}

struct CompareNode
{
    bool operator()(Node *a, Node *b)
    {
        return a->getGValue() + a->getHValue() > b->getGValue() + b->getHValue();
    }
};

vector<Move *> AStarSolver::solve2x2(Cube *cube)
{
    priority_queue<Node *, vector<Node *>, CompareNode> open;
    open.push(new Node(cube, NULL, NULL, 0, heuristic(cube)));
    set<string> closed;
    map<string, int> distance;

    while (!open.empty())
    {
        Node *currentNode = open.top();
        Cube *currentState = currentNode->getState();
        string currentKey = currentState->getKey();
        open.pop();
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

vector<Move *> AStarSolver::solve(Cube *cube)
{
    if (cube->size() == 3)
    {
        return solve3x3(cube);
    }
    return solve2x2(cube);
}

int AStarSolver::heuristic(Cube *cube)
{
    return cube->NumMisplacedPieces() / cube->numPiecesInFace();
}
