#include "Piece.h"

Piece::Piece(int orientation, int index)
{
    this->orientation = orientation;
    this->index = index;
}

Piece::Piece(){}

void Piece::setIndex(int index)
{
    this->index = index;
}
int Piece::getIndex()
{
    return this->index;
}
void Piece::setOrientation(int orientation)
{
    this->orientation = orientation;
}
int Piece::getOrientation()
{
    return this->orientation;
}