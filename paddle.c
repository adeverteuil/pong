#include <SDL.h>

#include "paddle.h"
#include "game.h"
#include "physics.h"

struct PongPaddle init_paddle(void) {
    struct PongPaddle paddle;
    Uint32 color_fg;

    paddle.sprite = SDL_CreateRGBSurface(SDL_HWSURFACE, 10, 50, 32, 0, 0, 0, 0);
    paddle.x = 0;
    paddle.y = 0;
    color_fg = SDL_MapRGB(paddle.sprite->format, 255, 255, 255);
    SDL_FillRect(paddle.sprite, NULL, color_fg);

    return paddle;
}

void set_paddle_pos(struct PongPaddle *paddle, int pos_y, SDL_Surface *window) {
    paddle->y = pos_y;
    if (paddle->y > (window->h - paddle->sprite->h / 2)) {
        paddle->y = window->h - paddle->sprite->h / 2;
    } else if (paddle->y < paddle->sprite->h / 2) {
        paddle->y = paddle->sprite->h / 2;
    }
    set_bounding_box(&(paddle->box), paddle->sprite, paddle->x, paddle->y);
}

void move_paddle(struct PongPaddle *paddle, int dist, SDL_Surface *window) {
    paddle->y += dist;
    if (paddle->y > (window->h - paddle->sprite->h / 2)) {
        paddle->y = window->h - paddle->sprite->h / 2;
    } else if (paddle->y < paddle->sprite->h / 2) {
        paddle->y = paddle->sprite->h / 2;
    }
    set_bounding_box(&(paddle->box), paddle->sprite, paddle->x, paddle->y);
}
