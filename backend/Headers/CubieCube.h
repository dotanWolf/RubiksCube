#ifndef CUBIECUBE_H
#define CUBIECUBE_H

#include <array>
#include <cstdint>
#include <string>
#include <vector>

class Cube;

struct CubieCube
{
    uint8_t cp[8];
    uint8_t co[8];
    uint8_t ep[12];
    uint8_t eo[12];

    static const char *MOVE_NAMES[18];
    static const int PHASE2_MOVES[10];

    static void initMoveTables();
    static CubieCube fromCube(const Cube &cube);
    static int inverse(int move);

    void identity();
    void move(int m);
    bool isSolved() const;
    bool inG1() const;

    int twist() const;
    int flip() const;
    int slice() const;
    int cornerPerm() const;
    int udEdgePerm() const;
    int slicePerm() const;

    static int nCr(int n, int k);
    static int permIndex(const uint8_t *src, int n);
};

#endif
