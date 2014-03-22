#include <SDL.h>

#include "renderer.h"

#include "ball.h"
#include "game.h"

static void fade_surface(SDL_Surface *surface);

void render_game(struct PongGame *game) {
    Uint32 color_bg = SDL_MapRGB(game->window->format, 8, 8, 8);
    struct PongBall ball = game->ball;
    struct PongPaddle paddle_r = game->paddle_r;
    struct PongPaddle paddle_l = game->paddle_l;

    if (game->options.crt_effect) {
        fade_surface(game->window);
    } else {
        //Fill the window with background.
        SDL_FillRect(game->window, NULL, color_bg);
    }
    //Draw sprites.
    draw_image(ball.sprite, game->window, ball.x, ball.y);
    draw_image(paddle_r.sprite, game->window, paddle_r.x, paddle_r.y);
    draw_image(paddle_l.sprite, game->window, paddle_l.x, paddle_l.y);
    draw_image(game->scoreboard.surface, game->window, game->window->w / 2, 30);
    SDL_Flip(game->window);
}

void fade_surface(SDL_Surface *surface) {
    int i;
    SDL_PixelFormat *fmt = surface->format;
    //32 bit pixel format support is hard coded here.
    if (fmt->BitsPerPixel != 32) {
        fprintf(stderr, "Pixel format not supported.\n");
        exit(EXIT_FAILURE);
    }
    Uint32 temp, *pixel;
    SDL_LockSurface(surface);
    pixel = (Uint32*)surface->pixels;
    for (i=0; i<(surface->w*surface->h); i++) {
        temp = pixel[i] & fmt->Rmask; /* Isolate green component */
        temp = temp >> fmt->Rshift; /* Shift it down to 8 bits */
        temp = temp << fmt->Rloss; /* Expand to a full 8 bit number */

        //Fade the color value.
        temp /= 2;

        //Write the new pixel value;
        temp = temp >> fmt->Rloss;
        temp = temp << fmt->Rshift;

        pixel[i] = temp;
    }
    SDL_UnlockSurface(surface);
}
