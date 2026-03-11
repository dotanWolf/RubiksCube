#include "Move.h"

Move::Move(int *mask, int *diff) : mask(mask), diff(diff) {}

int* Move::getMask() {
    return this->mask;
}
int* Move::getDiff() {
    return this->diff;
}