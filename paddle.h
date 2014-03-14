// File paddle.h

#ifndef PADDLE_H
#define PADDLE_H

struct PongPaddle {
    float x;
    float y;
    SDL_Surface *sprite;
};

//Initialize paddle structure.
struct PongPaddle init_paddle(void);

#endif /* PADDLE_H */
