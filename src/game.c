#include <stdlib.h>

#include "game.h"

struct PongGame *init_game(void) {
    struct PongGame *game;
    game = malloc(sizeof (struct PongGame));
    game->state = GameStateIntro;
    game->ball = init_ball();
    return game;
}
