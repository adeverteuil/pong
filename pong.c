//File pong.c

#include <stdio.h>
#include <math.h>
#include <SDL.h>
#include <SDL_ttf.h>

#include "game.h"
#include "paddle.h"
#include "pong.h"
#include "window.h"

//Initialize all resources.
static void init_resources(struct PongGame *game);

//Free all resources.
static void free_resources(struct PongGame *game);

//Event handler.
static void handle_events(struct PongGame *game);

//Keydown event handler.
static void handle_keydown_event(SDLKey keysym, struct PongGame *game);

//Keydown event handler for development phase.
static void handle_keydown_hack(SDLKey keysym, struct PongGame *game);

//Mouse motion event handler.
static void handle_mouse_motion_event(SDL_MouseMotionEvent event, struct PongGame *game);

//Main game loop.
static void main_loop(struct PongGame *game);

static int game_running = 1;


int main(int argc, char *argv[]) {
    //Game is in dynamic memory.
    struct PongGame *game;

    printf("Program started.\n");

    game = create_game();
    init_resources(game);  //SDL stuff.
    init_game(game);  //Game variables initial values.
    main_loop(game);
    free_resources(game);
    exit(EXIT_SUCCESS);
}

void main_loop(struct PongGame *game) {
    extern int game_running;
    SDL_Event event;
    int now = 0, before = 0, interval = 1000 / 10;
    long framecount = 0;

    while (game_running) {
        framecount++;
        handle_events(game);
        game_tick(game);
        update_idletimetext(&(game->idletimetext), interval, before, SDL_GetTicks(), framecount);
        render_game(game);

        // Frame rate control.
        now = SDL_GetTicks();
        if (now - before < interval) {
            SDL_Delay(interval - (now - before));
        }
        before = now;
    }
}

void init_resources(struct PongGame *game) {
    if (SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "SDL error : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    if (TTF_Init() == -1) {
        printf("TTF_Init: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    //SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
    SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_INTERVAL, SDL_DEFAULT_REPEAT_INTERVAL);

    game->window = init_window();
    game->scoreboard = init_scoreboard();
    game->idletimetext = init_idletimetext();
}

void free_resources(struct PongGame *game) {
    SDL_FreeSurface(game->ball.sprite);
    SDL_FreeSurface(game->paddle_r.sprite);
    SDL_FreeSurface(game->paddle_l.sprite);
    SDL_FreeSurface(game->scoreboard.surface);
    TTF_CloseFont(game->scoreboard.font);
    TTF_Quit();
    SDL_Quit();
    free(game);
}

void handle_events(struct PongGame *game) {
    SDL_Event event;

    while(SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                printf("Quit event.\n");
                game_running = 0;
                break;
            case SDL_KEYDOWN:
                handle_keydown_event(event.key.keysym.sym, game);
                handle_keydown_hack(event.key.keysym.sym, game);
                break;
            case SDL_MOUSEMOTION:
                handle_mouse_motion_event(event.motion, game);
        }
    }
}

void handle_keydown_event(SDLKey keysym, struct PongGame *game) {
    switch (keysym) {
        case SDLK_ESCAPE:
        case SDLK_q:
            game_running = 0;
            break;
        case SDLK_DOWN:
            move_paddle(&(game->paddle_r), 10, game->window);
            break;
        case SDLK_UP:
            move_paddle(&(game->paddle_r), -10, game->window);
            break;
        case SDLK_c:
            game->options.crt_effect = !game->options.crt_effect;
            printf("crt_effect %s.\n", game->options.crt_effect ? "on" : "off");
            break;
    }
}

void handle_keydown_hack(SDLKey keysym, struct PongGame *game) {
    switch (keysym) {
        case SDLK_r:
            start_game(game);
            break;
    }
}

void handle_mouse_motion_event(SDL_MouseMotionEvent event, struct PongGame *game) {
    set_paddle_pos(&(game->paddle_r), event.y, game->window);
}
