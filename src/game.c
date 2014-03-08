#include <stdlib.h>

#include "game.h"

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

    SDL_FillRect(game->window, NULL, color_bg);
    draw_image(ball.sprite, game->window, ball.x, ball.y);
}
