#include "Move.h"
#include <string>

Move::Move(int *mask, int *diff, std::string name) : name(name)
{
    this->mask = new int[8];
    this->diff = new int[8];
    for (int i = 0; i < 8; i++)
    {
        this->mask[i] = mask[i];
        this->diff[i] = diff[i];
    }
}
int *Move::getMask()
{
    return this->mask;
}
int *Move::getDiff()
{
    return this->diff;
}

std::string Move::getName()
{
    return name;
}