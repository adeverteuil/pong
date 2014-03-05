#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_gfxPrimitives.h>

/* http://tauday.com/ */
#define M_TAU (M_PI * 2)  /* No, really, pi is wrong... */

int main(int argc, char *argv[]) {

    if (SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "SDL error : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    if (TTF_Init()) {
        fprintf(stderr, "TTF_Init error\n");
        exit(EXIT_FAILURE);
    }

    SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
    float ball_heading = M_TAU * 1 / 6;
    float ball_velocity = 10;

    SDL_Surface *window, *ball, *paddle_r, *paddle_l;
    window = SDL_SetVideoMode(500, 500, 32, SDL_HWSURFACE);
    ball = SDL_CreateRGBSurface(SDL_HWSURFACE, 1, 1, 32, 0, 0, 0, 0);
    paddle_l = SDL_CreateRGBSurface(SDL_HWSURFACE, 10, 50, 32, 0, 0, 0, 0);
    paddle_r = SDL_CreateRGBSurface(SDL_HWSURFACE, 10, 50, 32, 0, 0, 0, 0);

    Uint32 color_bg, color_fg;
    color_bg = SDL_MapRGB(window->format, 0, 0, 0);
    color_fg = SDL_MapRGB(window->format, 255, 255, 255);

    SDL_FillRect(window, NULL, color_bg);
    SDL_FillRect(ball, NULL, color_fg);
    SDL_FillRect(paddle_r, NULL, color_fg);
    SDL_FillRect(paddle_l, NULL, color_fg);

    struct SDL_Rect_f {
        float x, y;
    };
    SDL_Rect pos_ball, pos_paddle_l, pos_paddle_r;
    struct SDL_Rect_f pos_ball_f;
    pos_ball_f.x = (window->w / 2) - (ball->w / 2);
    pos_ball_f.y = (window->h / 2) - (ball->h / 2);
    pos_paddle_l.x = 10;
    pos_paddle_l.y = (window->h / 2) - (paddle_l->h / 2);
    pos_paddle_r.x = window->w - paddle_r->w - 10;
    pos_paddle_r.y = (window->h / 2) - (paddle_r->h / 2);
    printf("x = %d, y = %d\n", pos_paddle_l.x, pos_paddle_l.y);
    printf("x = %d, y = %d\n", pos_paddle_r.x, pos_paddle_r.y);

    TTF_Font *font_verdana;
    font_verdana = TTF_OpenFont("verdana.ttf", 24);

    /*
    SDL_Surface *chrono;
    char chrono_text[20];
    sprintf(chrono_text, "%d", SDL_GetTicks());
    chrono = TTF_RenderText_Blended(font_verdana, chrono_text, font_color);
    SDL_Rect chrono_position;
    chrono_position.x = 20;
    chrono_position.y = window->h - chrono->h;

    SDL_Surface *mouse_coords;
    char mouse_coords_text[20];
    int mouse_x = 0;
    int mouse_y = 0;
    mouse_coords = TTF_RenderText_Blended(font_verdana, "0, 0", font_color);
    SDL_Rect mouse_coords_position;
    mouse_coords_position.x = window->w - mouse_coords->w;
    mouse_coords_position.y = window->h - mouse_coords->h;
    */

    SDL_Event event;
    int now = 0, before = 0, interval = 50;
    int quit = 0;
    int paused = 0;
    while (! quit) {
        now = SDL_GetTicks();
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    printf("Quit event.\n");
                    quit = 1;
                    break;
                case SDL_KEYDOWN:
                    printf("KeyDown event.\n");
                    switch (event.key.keysym.sym) {
                        case SDLK_ESCAPE:
                        case SDLK_q:
                            quit = 1;
                            break;
                        /*
                        case SDLK_RIGHT:
                            personnage = IMG_Load("pacman.jpg");
                            personnage_position.x += 50;
                            break;
                        case SDLK_LEFT:
                            personnage = IMG_Load("pacman_left.jpg");
                            personnage_position.x -= 50;
                            break;
                        */
                        case SDLK_DOWN:
                            pos_paddle_r.y = fmin(
                                window->h - paddle_r->h,
                                pos_paddle_r.y + paddle_r->h / 4
                                );
                            break;
                        case SDLK_UP:
                            pos_paddle_r.y = fmax(
                                0,
                                pos_paddle_r.y - paddle_r->h / 4
                                );
                            break;
                        case SDLK_SPACE:
                            paused = !paused;
                            break;
                    }
                    break;
                case SDL_MOUSEMOTION:
                    /*
                    printf("MouseMotion event.\n");
                    sprintf(mouse_coords_text, "%d, %d",
                            event.motion.x, event.motion.y);
                    mouse_coords = TTF_RenderText_Blended(font_verdana,
                                                          mouse_coords_text,
                                                          font_color);
                    mouse_coords_position.x = window->w - mouse_coords->w;
                    mouse_coords_position.y = window->h - mouse_coords->h;
                    mouse_x = event.motion.x;
                    mouse_y = event.motion.y;
                    */
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    /*
                    printf("MouseButtonDown event.\n");
                    switch (event.button.button) {
                        case SDL_BUTTON_LEFT:
                            quit = 1;
                            break;
                    }
                    */
                    break;
                default:
                    printf("Unhandled Event!\n");
                    break;
            }
        }
        if (now - before < interval) {
            SDL_Delay(interval - (now - before));
        }

        if (!paused) {
            /* Ball's physics */
            /* Advance ball. */
            pos_ball_f.x = pos_ball_f.x + ball_velocity * cosf(ball_heading);
            pos_ball_f.y = pos_ball_f.y - ball_velocity * sinf(ball_heading);
            if (pos_ball_f.y <= 0) {
                /* Top wall collision */
                pos_ball_f.y = -pos_ball_f.y;
                ball_heading = M_TAU - ball_heading;
                vlineRGBA(window,
                          pos_ball_f.x + ball->w / 2, 0, window->h / 4,
                          255, 0, 0, 255);
                printf("Direction : %f\n", ball_heading / M_TAU);
            }
            if (pos_ball_f.y >= window->h - ball->h) {
                /* Bottom wall collision */
                pos_ball_f.y = window->h
                              - (pos_ball_f.y + ball->h - window->h)
                              - ball->h;
                ball_heading = M_TAU - ball_heading;
                vlineRGBA(window,
                          pos_ball_f.x + ball->w / 2, window->h * 3 / 4, window->h,
                          255, 0, 0, 255);
                printf("Direction : %f\n", ball_heading / M_TAU);
            }
            if (pos_ball_f.x <= 0) {
                /* Left wall collision */
                pos_ball_f.x = -pos_ball_f.x;
                if (ball_heading > M_TAU / 2) {
                    ball_heading = M_TAU - (ball_heading - M_TAU / 2);
                } else {
                    ball_heading = M_TAU - (ball_heading + M_TAU / 2);
                }
                hlineRGBA(window,
                          0, window->w / 4, pos_ball_f.y + ball->h / 2,
                          255, 0, 0, 255);
                printf("Direction : %f\n", ball_heading / M_TAU);
            }
            if (pos_ball_f.x >= window->w - ball->w) {
                /* Right wall collision */
                pos_ball_f.x = window->w
                              - (pos_ball_f.x + ball->w - window->w)
                              - ball->w;
                if (ball_heading > M_TAU * 3 / 4) {
                    ball_heading = M_TAU / 2 + (M_TAU - ball_heading);
                } else {
                    ball_heading = M_TAU / 2 - ball_heading;
                }
                hlineRGBA(window,
                          window->w * 3 / 4, window->w,
                          pos_ball_f.y + ball->h / 2,
                          255, 0, 0, 255);
                printf("Direction : %f\n", ball_heading / M_TAU);
            }
            pos_ball.x = pos_ball_f.x;
            pos_ball.y = pos_ball_f.y;
        }

        /* Computer's move */

        /* Sreen refresh */
        //SDL_FillRect(window, NULL, color_bg);
        SDL_BlitSurface(ball, NULL, window, &pos_ball);
        SDL_BlitSurface(paddle_l, NULL, window, &pos_paddle_l);
        SDL_BlitSurface(paddle_r, NULL, window, &pos_paddle_r);
        /*
        vlineRGBA(window,
                  mouse_x, 0, window->h,
                  255, 0, 0, 255);
        hlineRGBA(window,
                  0, window->w, mouse_y,
                  255, 0, 0, 255);
        sprintf(chrono_text, "%d", now);
        chrono = TTF_RenderText_Blended(font_verdana, chrono_text, font_color);
        SDL_BlitSurface(chrono, NULL, window, &chrono_position);
        SDL_BlitSurface(mouse_coords, NULL, window, &mouse_coords_position);
        */
        SDL_Flip(window);
        before = now;
    }
    printf("Running time: %d\n", SDL_GetTicks());
    SDL_FreeSurface(window);
    SDL_FreeSurface(ball);
    SDL_FreeSurface(paddle_l);
    SDL_FreeSurface(paddle_r);
    TTF_CloseFont(font_verdana);
    SDL_Quit();
    TTF_Quit();
    return 0;
}
