// File ball.h

#ifndef BALL_H
#define BALL_H

#include "physics.h"

struct PongBall {
    float x;
    float y;
    float heading;
    float velocity;
    struct BoundingBox box;
    SDL_Surface *sprite;
};

//Return new ball structure, including a new SDL_Surface.
struct PongBall new_ball(void);

//Initialize ball structure.
void init_ball(struct PongBall *ball);

//Compute new ball position from heading and velocity.
void move_ball(struct PongBall *ball);

//Set ball position to center of window.
void center_ball(struct PongBall *ball, SDL_Surface *window);

#endif /* BALL_H */
