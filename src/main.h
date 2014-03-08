#include <math.h>

/* http://tauday.com/ */
#define M_TAU (M_PI * 2)  /* No, really, pi is wrong... */

enum GameState {
    GameStateIntro,
    GameStatePlaying
};

struct PongGame {
    enum GameState state;
    SDL_Surface *window;
};
