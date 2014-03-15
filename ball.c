#include <SDL.h>

#include "math.h"
#include "ball.h"
#include "physics.h"

void draw_image(SDL_Surface *src, SDL_Surface *dst, int x, int y) {
    SDL_Rect position;

    position.x = x - src->w / 2;
    position.y = y - src->h / 2;
    SDL_BlitSurface(src, NULL, dst, &position);
}

struct PongBall init_ball(void) {
    struct PongBall ball;
    Uint32 color_fg;

    ball.sprite = SDL_CreateRGBSurface(SDL_HWSURFACE, 10, 10, 32, 0, 0, 0, 0);
    ball.x = 0;
    ball.y = 0;
    ball.heading = 0;
    ball.velocity = 10;
    color_fg = SDL_MapRGB(ball.sprite->format, 255, 255, 255);
    SDL_FillRect(ball.sprite, NULL, color_fg);

    return ball;
}

void move_ball(struct PongBall *ball) {
    ball->x = ball->x + ball->velocity * cosf(ball->heading);
    ball->y = ball->y - ball->velocity * sinf(ball->heading);
    set_bounding_box(&(ball->box), ball->sprite, ball->x, ball->y);
}
