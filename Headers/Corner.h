#ifndef CORNER_H
#define CORNER_H

class Corner
{
private:
    int index;
    int orientation;

public:
    Corner(int orientation, int index);
    Corner();
    void setIndex(int index);
    int getIndex();
    void setOrientation(int orientation);
    int getOrientation();
};

#endif