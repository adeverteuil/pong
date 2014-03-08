#include <math.h>

/* http://tauday.com/ */
#define M_TAU (M_PI * 2)  /* No, really, pi is wrong... */
#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 500
#define WINDOW_FLAGS SDL_HWSURFACE|SDL_DOUBLEBUF

enum GameState {
    GameStateIntro,
    GameStatePlaying
};

struct PongGame {
    enum GameState state;
    SDL_Surface *window;
};
