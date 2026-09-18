#ifndef CUBE_H
#define CUBE_H

#include "Move.h"
#include "MoveFactory.h"
#include <array>
#include <map>
#include <string>
#include <vector>
using namespace std;

enum Face
{
    U = 0,
    D = 1,
    F = 2,
    B = 3,
    L = 4,
    R = 5,
    FACE_COUNT = 6
};

struct StickerPos
{
    int face;
    int row;
    int col;
};

class Cube
{
protected:
    int n;
    array<vector<vector<int>>, FACE_COUNT> stickers;
    vector<string> moves;
    MoveFactory *factory;

    void rotateFace(int face, bool prime);
    void cycleSides(int face, bool prime);
    array<vector<StickerPos>, 4> adjacentStrips(int face) const;
    int faceFromChar(char c) const;

public:
    Cube(int n);
    Cube(const Cube *cube);
    virtual ~Cube() = default;

    Cube *clone() const;
    void applyMove(string moveName);
    void showState();
    string getKey();
    bool isGoal();
    map<Move *, Cube *> succesor();
    std::string chooseRandomMove(string lastMove);
    int NumMisplacedPieces();
    int numPiecesInFace();
    int size() const;
    int getSticker(int face, int row, int col) const;
    Move *getMove(const string &moveName);
};

#endif
