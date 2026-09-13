#ifndef MOVE_H
#define MOVE_H

#include <string>

class Move
{
private:
    std::string name;

public:
    Move(std::string name);
    std::string getName();
};

#endif
