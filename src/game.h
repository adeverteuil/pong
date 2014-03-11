#include <SDL.h>

#include "ball.h"
#include "paddle.h"

enum GameState {
    GameStateIntro,
    GameStatePlaying,
    GameStatePaused,
};

struct PongGame {
    enum GameState state;
    SDL_Surface *window;
    struct PongBall ball;
    struct PongPaddle paddle_r;
};

//Initialize game state.
struct PongGame *init_game(void);

//Draw a frame of the game.
void render_game(struct PongGame *game);

//Compute game logic.
void game_tick(struct PongGame *game);
