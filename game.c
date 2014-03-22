// File game.c

#include <stdlib.h>

#include "math.h"
#include "game.h"

//Move ball and collide with objects.
static void do_ball_dynamics(struct PongGame *game);

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
    game->ball = new_ball();
    game->paddle_r = new_paddle();
    game->paddle_l = new_paddle();
    game->options.crt_effect = 0;
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
        /*
         * This commented out code rebounds the ball off the side wall.
         * Left here in case I want to leave this available as an option later.
        ball->x = -ball->x;
        if (ball->heading > M_TAU / 2) {
            ball->heading = M_TAU - (ball->heading - M_TAU / 2);
        } else {
            ball->heading = M_TAU - (ball->heading + M_TAU / 2);
        }
        */
        center_ball(&(game->ball), game->window);
        update_scoreboard(&(game->scoreboard), 0, 1);
    }
    if (ball->x >= window->w) {
        //Right wall collision.
        /*
         * This commented out code rebounds the ball off the side wall.
         * Left here in case I want to leave this available as an option later.
        ball->x = window->w - (ball->x - window->w);
        if (ball->heading > M_TAU * 3 / 4) {
            ball->heading = M_TAU / 2 + (M_TAU - ball->heading);
        } else {
            ball->heading = M_TAU / 2 - ball->heading;
        }
        */
        center_ball(&(game->ball), game->window);
        update_scoreboard(&(game->scoreboard), 1, 0);
    }
    /*
     * TODO remove this part.
    if (collision(ball->box, game->paddle_l.box) ||
        collision(ball->box, game->paddle_r.box)) {
        printf("Collision!\n");
    }
    */
    if (collision(ball->box, game->paddle_l.box)) {
        //Left paddle collision.
        ball->x = game->paddle_l.box.max_x + ball->sprite->w / 2;
        if (ball->heading > M_TAU / 2) {
            ball->heading = M_TAU - (ball->heading - M_TAU / 2);
        } else {
            ball->heading = M_TAU - (ball->heading + M_TAU / 2);
        }
    }
    if (collision(ball->box, game->paddle_r.box)) {
        //Right paddle collision.
        ball->x = game->paddle_r.box.min_x - ball->sprite->w / 2;
        if (ball->heading > M_TAU * 3 / 4) {
            ball->heading = M_TAU / 2 + (M_TAU - ball->heading);
        } else {
            ball->heading = M_TAU / 2 - ball->heading;
        }
    }
}

void computer_move(struct PongGame *game) {
    struct PongPaddle *paddle_l = &(game->paddle_l);

    //Match the y position with that of the ball's.
    set_paddle_pos(paddle_l, game->ball.y, game->window);
}

void start_game(struct PongGame *game) {
    center_ball(&(game->ball), game->window);
    game->ball.heading = M_TAU * 9 / 16;

    game->paddle_r.x = game->window->w - game->paddle_r.sprite->w * 2;
    set_paddle_pos(&(game->paddle_r), game->window->h / 2, game->window);

    game->paddle_l.x = game->paddle_l.sprite->w * 2;
    set_paddle_pos(&(game->paddle_l), game->window->h / 2, game->window);

    update_scoreboard(&(game->scoreboard), 0, 0);

    game->state = GameStatePlaying;
}
