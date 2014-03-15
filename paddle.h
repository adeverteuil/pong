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

//Return new paddle structure, including a new SDL_Surface.
struct PongPaddle new_paddle(void);
//Initialize paddle structure.
void init_paddle(struct PongPaddle *paddle);

//Center paddle on pixel y from the top.
void set_paddle_pos(struct PongPaddle *paddle, int pos_y, SDL_Surface *window);

//Move paddle down by dist pixels (up if negative).
void move_paddle(struct PongPaddle *paddle, int dist, SDL_Surface *window);

#endif /* PADDLE_H */
