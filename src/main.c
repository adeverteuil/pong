#include <stdio.h>
#include <math.h>
#include <SDL.h>

#include "game.h"
#include "main.h"
#include "window.h"

//Initialize all resources.
static void init_resources(struct PongGame *game);

//Free all resources.
static void free_resources(struct PongGame *game);

//Event handler.
static void handle_events(void);

//Keydown event handler.
static void handle_keydown_event(SDLKey keysym);

//Main game loop.
static void main_loop(struct PongGame *game);

static int game_running = 1;


int main(int argc, char *argv[]) {
    //Game is in dynamic memory.
    struct PongGame *game;

    printf("Program started.\n");

    game = init_game();
    init_resources(game);
    main_loop(game);
    free_resources(game);
    exit(EXIT_SUCCESS);
}

void main_loop(struct PongGame *game) {
    extern int game_running;
    SDL_Event event;
    int now = 0, before = 0, interval = 1000 / 10;

    while (game_running) {
        now = SDL_GetTicks();

        handle_events();

        /* TODO do game logic and updates */
        game_tick(game);

        /* TODO do rendering */
        render_game(game);

        // Frame rate control.
        if (now - before < interval) {
            SDL_Delay(interval - (now - before));
        }
        before = now;
    }
}

void init_resources(struct PongGame *game) {
    game->window = init_window();
}

void free_resources(struct PongGame *game) {
    SDL_Quit();
    SDL_FreeSurface(game->ball.sprite);
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
