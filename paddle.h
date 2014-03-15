// File paddle.h

#ifndef PADDLE_H
#define PADDLE_H

#include "physics.h"

struct PongPaddle {
    float x;
    float y;
    struct BoundingBox box;
    SDL_Surface *sprite;
};

//Initialize paddle structure.
struct PongPaddle init_paddle(void);

//Center paddle on pixel y from the top.
void set_paddle_pos(struct PongPaddle *paddle, int pos_y, SDL_Surface *window);

//Move paddle down by dist pixels (up if negative).
void move_paddle(struct PongPaddle *paddle, int dist, SDL_Surface *window);

#endif /* PADDLE_H */
