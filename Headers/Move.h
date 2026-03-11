#ifndef MOVE_H
#define MOVE_H

#include <string>

class Move {
    private:
        int* mask;
        int* diff;
        std::string name;
    public:
        Move(int* mask, int* diff, std::string name);
        int* getMask();
        int* getDiff();
        std::string getName();
};

#endif