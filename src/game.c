#include <stdlib.h>

#include "math.h"
#include "game.h"

//Move ball and collide with objects.
static void move_ball(struct PongGame *game);

struct PongGame *init_game(void) {
    struct PongGame *game;
    game = malloc(sizeof (struct PongGame));
    game->state = GameStateIntro;
    game->ball = init_ball();
    return game;
}

void render_game(struct PongGame *game) {
    Uint32 color_bg = SDL_MapRGB(game->window->format, 0, 0, 0);
    struct PongBall ball = game->ball;

    //Fill the window with background.
    SDL_FillRect(game->window, NULL, color_bg);
    //Draw sprites.
    draw_image(ball.sprite, game->window, ball.x, ball.y);
    SDL_Flip(game->window);
}

void game_tick(struct PongGame *game) {
    move_ball(game);
}

void move_ball(struct PongGame *game){
    struct PongBall *ball = &(game->ball);
    SDL_Surface *window = game->window;

    ball->x = ball->x + ball->velocity * cosf(ball->heading);
    ball->y = ball->y - ball->velocity * sinf(ball->heading);
}
