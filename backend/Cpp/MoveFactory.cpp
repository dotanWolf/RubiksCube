#include "MoveFactory.h"

MoveFactory::MoveFactory()
{
    const char *names[] = {
        "U", "U2", "U'", "D", "D2", "D'", "F", "F2", "F'",
        "B", "B2", "B'", "L", "L2", "L'", "R", "R2", "R'"};
    for (const char *name : names)
    {
        nameToMove[name] = new Move(name);
    }
}

Move *MoveFactory::getMove(string moveName)
{
    return nameToMove[moveName];
}
