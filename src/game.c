#include <stdlib.h>

#include "math.h"
#include "game.h"

//Move ball and collide with objects.
static void move_ball(struct PongGame *game);

//Serve ball.
static void start_game(struct PongGame *game);

struct PongGame *init_game(void) {
    struct PongGame *game;
    game = malloc(sizeof (struct PongGame));
    if (!game) {
        fprintf(stderr, "Couldn't allocate memory for game.\n");
        exit(EXIT_FAILURE);
    }
    game->state = GameStateIntro;
    game->ball = init_ball();
    game->paddle_r = init_paddle();
    return game;
}

void render_game(struct PongGame *game) {
    Uint32 color_bg = SDL_MapRGB(game->window->format, 0, 0, 0);
    struct PongBall ball = game->ball;
    struct PongPaddle paddle_r = game->paddle_r;

    //Fill the window with background.
    SDL_FillRect(game->window, NULL, color_bg);
    //Draw sprites.
    draw_image(ball.sprite, game->window, ball.x, ball.y);
    draw_image(paddle_r.sprite, game->window, paddle_r.x, paddle_r.y);
    SDL_Flip(game->window);
}

void game_tick(struct PongGame *game) {
    switch (game->state) {
        case GameStateIntro:
            //TODO I guess the intro screen will appear here until a key is pressed.
            start_game(game);
            break;
        case GameStatePlaying:
            move_ball(game);
            break;
    }
}

void move_ball(struct PongGame *game){
    struct PongBall *ball = &(game->ball);
    SDL_Surface *window = game->window;

    ball->x = ball->x + ball->velocity * cosf(ball->heading);
    ball->y = ball->y - ball->velocity * sinf(ball->heading);

    //TODO Take into account the size of the ball.
    if (ball->y <= 0) {
        //Top wall collision.
        ball->y = -ball->y;
        ball->heading = M_TAU - ball->heading;
    }
    if (ball->y >= window->h) {
        //Bottom wall collision.
        ball->y = window->h - (ball->y - window->h);
        ball->heading = M_TAU - ball->heading;
    }
    if (ball->x <= 0) {
        //Left wall collision.
        ball->x = -ball->x;
        if (ball->heading > M_TAU / 2) {
            ball->heading = M_TAU - (ball->heading - M_TAU / 2);
        } else {
            ball->heading = M_TAU - (ball->heading + M_TAU / 2);
        }
    }
    if (ball->x >= window->w) {
        //Right wall collision.
        ball->x = window->w - (ball->x - window->w);
        if (ball->heading > M_TAU * 3 / 4) {
            ball->heading = M_TAU / 2 + (M_TAU - ball->heading);
        } else {
            ball->heading = M_TAU / 2 - ball->heading;
        }
    }
}

void start_game(struct PongGame *game) {
    game->ball.x = game->window->w / 2;
    game->ball.y = game->window->h / 2;
    game->ball.heading = M_TAU * 1 / 16;

    game->paddle_r.x = game->window->w - game->paddle_r.sprite->w * 2;
    game->paddle_r.y = game->window->h / 2;

    game->state = GameStatePlaying;
}
