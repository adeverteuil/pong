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

//TODO move this in a .c file that will take care of all drawing functions.
void draw_image(SDL_Surface *src, SDL_Surface *dst, int x, int y);

//Return new ball structure, including a new SDL_Surface.
struct PongBall new_ball(void);

//Initialize ball structure.
void init_ball(struct PongBall *ball);

//Compute new ball position from heading and velocity.
void move_ball(struct PongBall *ball);

#endif /* BALL_H */
