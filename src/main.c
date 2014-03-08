#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL.h>

#include "main.h"
#include "window.h"

//Initialize all resources.
static void init_resources(struct PongGame *game);

//Initialize game state.
static struct PongGame *init_game(void);

//Free all resources.
static void free_resources(struct PongGame *game);

//Event handler.
static void handle_events(void);

//Keydown event handler.
static void handle_keydown_event(SDLKey keysym);

//Main game loop.
static void main_loop(void);

static int game_running = 1;


int main(int argc, char *argv[]) {
    struct PongGame *game;

    printf("Program started.\n");

    game = init_game();
    init_resources(game);
    main_loop();
    free_resources(game);
    exit(EXIT_SUCCESS);
}

void main_loop(void) {
    extern int game_running;
    SDL_Event event;
    int now = 0, before = 0, interval = 1000 / 60;

    while (game_running) {
        now = SDL_GetTicks();

        handle_events();

        /* TODO do game logic and updates */

        /* TODO do rendering */

        // Frame rate control.
        if (now - before < interval) {
            SDL_Delay(interval - (now - before));
        }
    }
}

void init_resources(struct PongGame *game) {
    game->window = init_window();
}

struct PongGame *init_game(void) {
    struct PongGame *game;
    game = malloc(sizeof (struct PongGame));
    game->state = GameStateIntro;
    return game;
}

void free_resources(struct PongGame *game) {
    SDL_Quit();
    free(game);
}

void handle_events(void) {
    SDL_Event event;

    while(SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                printf("Quit event.\n");
                game_running = 0;
                break;
            case SDL_KEYDOWN:
                handle_keydown_event(event.key.keysym.sym);
                break;
        }
    }
}

void handle_keydown_event(SDLKey keysym) {
    switch (keysym) {
        case SDLK_ESCAPE:
        case SDLK_q:
            game_running = 0;
            break;
    }
}
