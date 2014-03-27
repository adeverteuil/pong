// File ai.h

#ifndef AI_H
#define AI_H

enum ComputerBehavior {
    AITheWall,
    AIDelay,
};

#include "game.h"
#include "paddle.h"

//Play computer's move.
void computer_move(struct PongGame *game);

#endif /* not AI_H */
