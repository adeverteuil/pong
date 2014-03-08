#include <SDL.h>

#include "ball.h"

enum GameState {
    GameStateIntro,
    GameStatePlaying,
    GameStatePaused,
};

struct PongGame {
    enum GameState state;
    SDL_Surface *window;
    struct PongBall ball;
};

//Initialize game state.
struct PongGame *init_game(void);

//Draw a frame of the game.
void render_game(struct PongGame *game);
