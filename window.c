#include "window.h"

#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 500
#define WINDOW_FLAGS SDL_HWSURFACE|SDL_DOUBLEBUF

SDL_Surface *init_window(void) {
    SDL_Surface *window;
    window = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32, WINDOW_FLAGS);
    if (window == NULL) {
        fprintf(stderr, "SDL error : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    return window;
}
