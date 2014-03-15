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

//Initialize ball structure.
struct PongBall init_ball(void);

//Compute new ball position from heading and velocity.
void move_ball(struct PongBall *ball);

#endif /* BALL_H */
