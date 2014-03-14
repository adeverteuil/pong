#include "window.h"

#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 500
#define WINDOW_FLAGS SDL_HWSURFACE|SDL_DOUBLEBUF

SDL_Surface *init_window(void) {
    SDL_Surface *window;

    if (SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "SDL error : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
    window = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32, WINDOW_FLAGS);
    if (window == NULL) {
        fprintf(stderr, "SDL error : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    return window;
}
