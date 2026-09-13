#include "CubieCube.h"
#include "Cube.h"

const char *CubieCube::MOVE_NAMES[18] = {
    "U", "U2", "U'", "D", "D2", "D'", "F", "F2", "F'",
    "B", "B2", "B'", "L", "L2", "L'", "R", "R2", "R'"};

const int CubieCube::PHASE2_MOVES[10] = {0, 1, 2, 3, 4, 5, 7, 10, 13, 16};

static CubieCube moveTable[18];
static bool tablesReady = false;

static const StickerPos CORNER_FACELETS[8][3] = {
    {{U, 2, 2}, {R, 0, 0}, {F, 0, 2}},
    {{U, 2, 0}, {F, 0, 0}, {L, 0, 2}},
    {{U, 0, 0}, {L, 0, 0}, {B, 0, 2}},
    {{U, 0, 2}, {B, 0, 0}, {R, 0, 2}},
    {{D, 0, 2}, {F, 2, 2}, {R, 2, 0}},
    {{D, 0, 0}, {L, 2, 2}, {F, 2, 0}},
    {{D, 2, 0}, {B, 2, 2}, {L, 2, 0}},
    {{D, 2, 2}, {R, 2, 2}, {B, 2, 0}}};

static const StickerPos EDGE_FACELETS[12][2] = {
    {{U, 1, 2}, {R, 0, 1}},
    {{U, 2, 1}, {F, 0, 1}},
    {{U, 1, 0}, {L, 0, 1}},
    {{U, 0, 1}, {B, 0, 1}},
    {{D, 1, 2}, {R, 2, 1}},
    {{D, 0, 1}, {F, 2, 1}},
    {{D, 1, 0}, {L, 2, 1}},
    {{D, 2, 1}, {B, 2, 1}},
    {{F, 1, 2}, {R, 1, 0}},
    {{F, 1, 0}, {L, 1, 2}},
    {{B, 1, 2}, {L, 1, 0}},
    {{B, 1, 0}, {R, 1, 2}}};

static int cornerId[64];
static int edgeId[64];

static int colorMask(int a, int b, int c = -1)
{
    int mask = (1 << a) | (1 << b);
    if (c >= 0)
    {
        mask |= (1 << c);
    }
    return mask;
}

void CubieCube::identity()
{
    for (int i = 0; i < 8; i++)
    {
        cp[i] = i;
        co[i] = 0;
    }
    for (int i = 0; i < 12; i++)
    {
        ep[i] = i;
        eo[i] = 0;
    }
}

int CubieCube::nCr(int n, int k)
{
    if (k < 0 || k > n)
    {
        return 0;
    }
    long r = 1;
    for (int i = 1; i <= k; i++)
    {
        r = r * (n - k + i) / i;
    }
    return (int)r;
}

int CubieCube::permIndex(const uint8_t *src, int n)
{
    int idx = 0;
    for (int i = 0; i < n; i++)
    {
        int k = src[i];
        for (int j = 0; j < i; j++)
        {
            if (src[j] < src[i])
            {
                k--;
            }
        }
        idx = idx * (n - i) + k;
    }
    return idx;
}

int CubieCube::inverse(int move)
{
    int face = move / 3;
    int turn = move % 3;
    return face * 3 + (2 - turn);
}

CubieCube CubieCube::fromCube(const Cube &cube)
{
    static bool idsReady = false;
    if (!idsReady)
    {
        for (int i = 0; i < 64; i++)
        {
            cornerId[i] = -1;
            edgeId[i] = -1;
        }
        Cube solved(3);
        for (int i = 0; i < 8; i++)
        {
            int a = solved.getSticker(CORNER_FACELETS[i][0].face, CORNER_FACELETS[i][0].row, CORNER_FACELETS[i][0].col);
            int b = solved.getSticker(CORNER_FACELETS[i][1].face, CORNER_FACELETS[i][1].row, CORNER_FACELETS[i][1].col);
            int c = solved.getSticker(CORNER_FACELETS[i][2].face, CORNER_FACELETS[i][2].row, CORNER_FACELETS[i][2].col);
            cornerId[colorMask(a, b, c)] = i;
        }
        for (int i = 0; i < 12; i++)
        {
            int a = solved.getSticker(EDGE_FACELETS[i][0].face, EDGE_FACELETS[i][0].row, EDGE_FACELETS[i][0].col);
            int b = solved.getSticker(EDGE_FACELETS[i][1].face, EDGE_FACELETS[i][1].row, EDGE_FACELETS[i][1].col);
            edgeId[colorMask(a, b)] = i;
        }
        idsReady = true;
    }

    CubieCube cubeState;
    for (int slot = 0; slot < 8; slot++)
    {
        int colors[3];
        for (int k = 0; k < 3; k++)
        {
            colors[k] = cube.getSticker(CORNER_FACELETS[slot][k].face, CORNER_FACELETS[slot][k].row, CORNER_FACELETS[slot][k].col);
        }
        cubeState.cp[slot] = (uint8_t)cornerId[colorMask(colors[0], colors[1], colors[2])];
        int ori = 0;
        while (colors[ori] != U && colors[ori] != D)
        {
            ori++;
        }
        cubeState.co[slot] = (uint8_t)ori;
    }
    for (int slot = 0; slot < 12; slot++)
    {
        int c0 = cube.getSticker(EDGE_FACELETS[slot][0].face, EDGE_FACELETS[slot][0].row, EDGE_FACELETS[slot][0].col);
        int c1 = cube.getSticker(EDGE_FACELETS[slot][1].face, EDGE_FACELETS[slot][1].row, EDGE_FACELETS[slot][1].col);
        int id = edgeId[colorMask(c0, c1)];
        cubeState.ep[slot] = (uint8_t)id;
        bool hasUD = ((1 << c0) | (1 << c1)) & ((1 << U) | (1 << D));
        bool good = hasUD ? (c0 == U || c0 == D) : (c0 == F || c0 == B);
        cubeState.eo[slot] = good ? 0 : 1;
    }
    return cubeState;
}

void CubieCube::initMoveTables()
{
    if (tablesReady)
    {
        return;
    }
    for (int m = 0; m < 18; m++)
    {
        Cube cube(3);
        cube.applyMove(MOVE_NAMES[m]);
        moveTable[m] = fromCube(cube);
    }
    tablesReady = true;
}

void CubieCube::move(int m)
{
    const CubieCube &mv = moveTable[m];
    uint8_t ncp[8], nco[8], nep[12], neo[12];
    for (int i = 0; i < 8; i++)
    {
        ncp[i] = cp[mv.cp[i]];
        nco[i] = (uint8_t)((co[mv.cp[i]] + mv.co[i]) % 3);
    }
    for (int i = 0; i < 12; i++)
    {
        nep[i] = ep[mv.ep[i]];
        neo[i] = (uint8_t)((eo[mv.ep[i]] + mv.eo[i]) % 2);
    }
    for (int i = 0; i < 8; i++)
    {
        cp[i] = ncp[i];
        co[i] = nco[i];
    }
    for (int i = 0; i < 12; i++)
    {
        ep[i] = nep[i];
        eo[i] = neo[i];
    }
}

bool CubieCube::isSolved() const
{
    for (int i = 0; i < 8; i++)
    {
        if (cp[i] != i || co[i] != 0)
        {
            return false;
        }
    }
    for (int i = 0; i < 12; i++)
    {
        if (ep[i] != i || eo[i] != 0)
        {
            return false;
        }
    }
    return true;
}

bool CubieCube::inG1() const
{
    return twist() == 0 && flip() == 0 && slice() == nCr(11, 4) + nCr(10, 3) + nCr(9, 2) + nCr(8, 1);
}

int CubieCube::twist() const
{
    int t = 0;
    for (int i = 0; i < 7; i++)
    {
        t = 3 * t + co[i];
    }
    return t;
}

int CubieCube::flip() const
{
    int t = 0;
    for (int i = 0; i < 11; i++)
    {
        t = 2 * t + eo[i];
    }
    return t;
}

int CubieCube::slice() const
{
    int pos[4];
    int k = 0;
    for (int i = 0; i < 12; i++)
    {
        if (ep[i] >= 8)
        {
            pos[k++] = i;
        }
    }
    return nCr(pos[3], 4) + nCr(pos[2], 3) + nCr(pos[1], 2) + nCr(pos[0], 1);
}

int CubieCube::cornerPerm() const
{
    return permIndex(cp, 8);
}

int CubieCube::udEdgePerm() const
{
    return permIndex(ep, 8);
}

int CubieCube::slicePerm() const
{
    uint8_t p[4];
    for (int i = 0; i < 4; i++)
    {
        p[i] = (uint8_t)(ep[8 + i] - 8);
    }
    return permIndex(p, 4);
}
