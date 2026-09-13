#include "Cube.h"
#include <iostream>
#include <random>

using namespace std;

static const char FACE_LETTERS[] = {'U', 'D', 'F', 'B', 'L', 'R'};

Cube::Cube(int n)
{
    this->n = n;
    for (int face = 0; face < FACE_COUNT; face++)
    {
        stickers[face].assign(n, vector<int>(n, face));
    }
    moves = {"U", "U2", "U'", "D", "D2", "D'", "F", "F2", "F'", "B", "B2", "B'", "R", "R2", "R'", "L", "L2", "L'"};
    factory = new MoveFactory();
}

int Cube::numPiecesInFace()
{
    return this->n * this->n;
}

Cube *Cube::clone() const
{
    return new Cube(this);
}

Cube::Cube(const Cube *cube)
{
    this->n = cube->n;
    this->stickers = cube->stickers;
    this->factory = cube->factory;
    this->moves = cube->moves;
}

int Cube::faceFromChar(char c) const
{
    switch (c)
    {
    case 'U':
        return U;
    case 'D':
        return D;
    case 'F':
        return F;
    case 'B':
        return B;
    case 'L':
        return L;
    case 'R':
        return R;
    default:
        return U;
    }
}

void Cube::rotateFace(int face, bool prime)
{
    vector<vector<int>> old = stickers[face];
    for (int r = 0; r < n; r++)
    {
        for (int c = 0; c < n; c++)
        {
            if (!prime)
            {
                stickers[face][c][n - 1 - r] = old[r][c];
            }
            else
            {
                stickers[face][n - 1 - c][r] = old[r][c];
            }
        }
    }
}

array<vector<StickerPos>, 4> Cube::adjacentStrips(int face) const
{
    array<vector<StickerPos>, 4> strips;
    auto add = [&](int strip, int f, int row, int col)
    {
        strips[strip].push_back({f, row, col});
    };

    switch (face)
    {
    case U:
        for (int i = 0; i < n; i++)
        {
            add(0, F, 0, i);
            add(1, L, 0, i);
            add(2, B, 0, i);
            add(3, R, 0, i);
        }
        break;
    case D:
        for (int i = 0; i < n; i++)
        {
            add(0, F, n - 1, i);
            add(1, R, n - 1, i);
            add(2, B, n - 1, i);
            add(3, L, n - 1, i);
        }
        break;
    case F:
        for (int i = 0; i < n; i++)
        {
            add(0, U, n - 1, i);
            add(1, R, i, 0);
            add(2, D, 0, n - 1 - i);
            add(3, L, n - 1 - i, n - 1);
        }
        break;
    case B:
        for (int i = 0; i < n; i++)
        {
            add(0, U, 0, n - 1 - i);
            add(1, L, i, 0);
            add(2, D, n - 1, i);
            add(3, R, n - 1 - i, n - 1);
        }
        break;
    case R:
        for (int i = 0; i < n; i++)
        {
            add(0, U, n - 1 - i, n - 1);
            add(1, B, i, 0);
            add(2, D, n - 1 - i, n - 1);
            add(3, F, n - 1 - i, n - 1);
        }
        break;
    case L:
        for (int i = 0; i < n; i++)
        {
            add(0, U, i, 0);
            add(1, F, i, 0);
            add(2, D, i, 0);
            add(3, B, n - 1 - i, n - 1);
        }
        break;
    }
    return strips;
}

void Cube::cycleSides(int face, bool prime)
{
    array<vector<StickerPos>, 4> strips = adjacentStrips(face);
    array<vector<int>, 4> values;
    for (int s = 0; s < 4; s++)
    {
        values[s].resize(n);
        for (int i = 0; i < n; i++)
        {
            StickerPos p = strips[s][i];
            values[s][i] = stickers[p.face][p.row][p.col];
        }
    }

    for (int s = 0; s < 4; s++)
    {
        int from = prime ? (s + 1) % 4 : (s + 3) % 4;
        for (int i = 0; i < n; i++)
        {
            StickerPos p = strips[s][i];
            stickers[p.face][p.row][p.col] = values[from][i];
        }
    }
}

void Cube::applyMove(string moveName)
{
    int face = faceFromChar(moveName[0]);
    int turns = 1;
    if (moveName.size() > 1)
    {
        if (moveName[1] == '\'')
        {
            turns = 3;
        }
        else if (moveName[1] == '2')
        {
            turns = 2;
        }
    }
    for (int t = 0; t < turns; t++)
    {
        rotateFace(face, false);
        cycleSides(face, false);
    }
}

int Cube::size() const
{
    return n;
}

int Cube::getSticker(int face, int row, int col) const
{
    return stickers[face][row][col];
}

Move *Cube::getMove(const string &moveName)
{
    return factory->getMove(moveName);
}

void Cube::showState()
{
    auto printRow = [&](int face, int row, bool trailingSpace)
    {
        for (int c = 0; c < n; c++)
        {
            cout << FACE_LETTERS[stickers[face][row][c]] << ' ';
        }
        if (trailingSpace)
        {
            cout << "  ";
        }
    };

    for (int r = 0; r < n; r++)
    {
        for (int s = 0; s < n * 2 + 2; s++)
        {
            cout << " ";
        }
        printRow(U, r, false);
        cout << endl;
    }
    cout << endl;
    for (int r = 0; r < n; r++)
    {
        printRow(L, r, true);
        printRow(F, r, true);
        printRow(R, r, true);
        printRow(B, r, false);
        cout << endl;
    }
    cout << endl;
    for (int r = 0; r < n; r++)
    {
        for (int s = 0; s < n * 2 + 2; s++)
        {
            cout << " ";
        }
        printRow(D, r, false);
        cout << endl;
    }
}

string Cube::getKey()
{
    string key = "";
    for (int face = 0; face < FACE_COUNT; face++)
    {
        for (int r = 0; r < n; r++)
        {
            for (int c = 0; c < n; c++)
            {
                key += to_string(stickers[face][r][c]);
            }
        }
    }
    return key;
}

bool Cube::isGoal()
{
    for (int face = 0; face < FACE_COUNT; face++)
    {
        for (int r = 0; r < n; r++)
        {
            for (int c = 0; c < n; c++)
            {
                if (stickers[face][r][c] != face)
                {
                    return false;
                }
            }
        }
    }
    return true;
}

map<Move *, Cube *> Cube::succesor()
{
    map<Move *, Cube *> succesorMap;
    for (auto &moveName : moves)
    {
        Cube *newCube = this->clone();
        Move *move = factory->getMove(moveName);
        newCube->applyMove(moveName);
        succesorMap[move] = newCube;
    }
    return succesorMap;
}

int Cube::NumMisplacedPieces()
{
    int counter = 0;
    for (int face = 0; face < FACE_COUNT; face++)
    {
        for (int r = 0; r < n; r++)
        {
            for (int c = 0; c < n; c++)
            {
                if (stickers[face][r][c] != face)
                {
                    counter++;
                }
            }
        }
    }
    return counter;
}

std::string Cube::chooseRandomMove()
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, moves.size() - 1);
    return moves[dis(gen)];
}
