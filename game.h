// File game.h

#ifndef GAME_H
#define GAME_H

#include <SDL.h>

#include "ai.h"
#include "ball.h"
#include "options.h"
#include "paddle.h"
#include "text.h"

enum GameState {
    GameStateIntro,
    GameStatePlaying,
    GameStatePaused,
};

struct PongGame {
    enum GameState state;
    enum ComputerBehavior computer_behavior;
    SDL_Surface *window;
    struct PongBall ball;
    struct PongPaddle paddle_r;
    struct PongPaddle paddle_l;
    struct ScoreBoard scoreboard;
    struct IdleTimeText idletimetext;
    struct GameOptions options;
};

//Allocate memory for game state holder and return it's pointer.
struct PongGame *create_game(void);

//Initialize game state.
void init_game(struct PongGame *game);

//Serve ball.
void start_game(struct PongGame *game);

//Compute game logic.
void game_tick(struct PongGame *game);

#endif /* GAME_H */
