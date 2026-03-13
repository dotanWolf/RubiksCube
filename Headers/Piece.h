#ifndef PIECE_H
#define PIECE_H

class Piece
{
protected:
    int orientation;
    int index;

public:
    Piece(int orientation, int index);
    Piece();
    void setIndex(int index);
    int getIndex();
    void setOrientation(int orientation);
    int getOrientation();
};

#endif