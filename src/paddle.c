#include <SDL.h>

#include "paddle.h"

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
