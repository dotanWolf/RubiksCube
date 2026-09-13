#include "Move.h"

Move::Move(std::string name)
{
    this->name = name;
}

std::string Move::getName()
{
    return name;
}
