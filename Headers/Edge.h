#ifndef EDGE_H
#define EDGE_H

#include "Piece.h"

class Edge : public Piece
{
public:
    Edge(int index, int orientation);
    Edge();
};

#endif