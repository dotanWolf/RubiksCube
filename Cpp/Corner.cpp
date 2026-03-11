#include "Corner.h"
Corner::Corner(int index, int orientation) : orientation(orientation), index(index) {}
Corner::Corner() {}
void Corner::setIndex(int index)
{
    this->index = index;
}
int Corner::getIndex()
{
    return this->index;
}
void Corner::setOrientation(int orientation)
{
    this->orientation = orientation;
}
int Corner::getOrientation()
{
    return this->orientation;
}
