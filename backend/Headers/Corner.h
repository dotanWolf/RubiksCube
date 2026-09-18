#ifndef CORNER_H
#define CORNER_H

#include "Piece.h"

class Corner : public Piece
{

public:
    Corner(int orientation, int index);
    Corner();
};

#endif