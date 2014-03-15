#include <stdlib.h>

#include "math.h"
#include "game.h"

//Move ball and collide with objects.
static void do_ball_dynamics(struct PongGame *game);

//Serve ball.
static void start_game(struct PongGame *game);

//Computer's move.
static void computer_move(struct PongGame *game);

struct PongGame* create_game(void) {
    struct PongGame *game;
    game = malloc(sizeof (struct PongGame));
    if (!game) {
        fprintf(stderr, "Couldn't allocate memory for game.\n");
        exit(EXIT_FAILURE);
    }
    return game;
}

void init_game(struct PongGame *game) {
    game->state = GameStateIntro;
    game->ball = init_ball();
    game->paddle_r = init_paddle();
    game->paddle_l = init_paddle();
}

void render_game(struct PongGame *game) {
    Uint32 color_bg = SDL_MapRGB(game->window->format, 0, 0, 0);
    struct PongBall ball = game->ball;
    struct PongPaddle paddle_r = game->paddle_r;
    struct PongPaddle paddle_l = game->paddle_l;

    //Fill the window with background.
    SDL_FillRect(game->window, NULL, color_bg);
    //Draw sprites.
    draw_image(ball.sprite, game->window, ball.x, ball.y);
    draw_image(paddle_r.sprite, game->window, paddle_r.x, paddle_r.y);
    draw_image(paddle_l.sprite, game->window, paddle_l.x, paddle_l.y);
    SDL_Flip(game->window);
}

void game_tick(struct PongGame *game) {
    switch (game->state) {
        case GameStateIntro:
            //TODO I guess the intro screen will appear here until a key is pressed.
            start_game(game);
            break;
        case GameStatePlaying:
            do_ball_dynamics(game);
            computer_move(game);
            break;
    }
}

void do_ball_dynamics(struct PongGame *game){
    struct PongBall *ball = &(game->ball);
    SDL_Surface *window = game->window;

    move_ball(ball);

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
    if (collision(ball->box, game->paddle_l.box) ||
        collision(ball->box, game->paddle_r.box)) {
        printf("Collision!\n");
    }
}

void computer_move(struct PongGame *game) {
    struct PongPaddle *paddle_l = &(game->paddle_l);

    //Match the y position with that of the ball's.
    set_paddle_pos(paddle_l, game->ball.y, game->window);
}

void start_game(struct PongGame *game) {
    game->ball.x = game->window->w / 2;
    game->ball.y = game->window->h / 2;
    game->ball.heading = M_TAU * 1 / 16;

    game->paddle_r.x = game->window->w - game->paddle_r.sprite->w * 2;
    game->paddle_r.y = game->window->h / 2;

    game->paddle_l.x = game->paddle_l.sprite->w * 2;
    game->paddle_l.y = game->window->h / 2;

    game->state = GameStatePlaying;
}
