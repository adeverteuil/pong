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
    float balle_direction = M_TAU * 1 / 6;
    float balle_velocite = 10;

    SDL_Surface *fenetre, *balle, *palette_d, *palette_g;
    fenetre = SDL_SetVideoMode(500, 500, 32, SDL_HWSURFACE);
    balle = SDL_CreateRGBSurface(SDL_HWSURFACE, 1, 1, 32, 0, 0, 0, 0);
    palette_g = SDL_CreateRGBSurface(SDL_HWSURFACE, 10, 50, 32, 0, 0, 0, 0);
    palette_d = SDL_CreateRGBSurface(SDL_HWSURFACE, 10, 50, 32, 0, 0, 0, 0);

    Uint32 color_bg, color_fg;
    color_bg = SDL_MapRGB(fenetre->format, 0, 0, 0);
    color_fg = SDL_MapRGB(fenetre->format, 255, 255, 255);

    SDL_FillRect(fenetre, NULL, color_bg);
    SDL_FillRect(balle, NULL, color_fg);
    SDL_FillRect(palette_d, NULL, color_fg);
    SDL_FillRect(palette_g, NULL, color_fg);

    struct SDL_Rect_f {
        float x, y;
    };
    SDL_Rect pos_balle, pos_palette_g, pos_palette_d;
    struct SDL_Rect_f pos_balle_f;
    pos_balle_f.x = (fenetre->w / 2) - (balle->w / 2);
    pos_balle_f.y = (fenetre->h / 2) - (balle->h / 2);
    pos_palette_g.x = 10;
    pos_palette_g.y = (fenetre->h / 2) - (palette_g->h / 2);
    pos_palette_d.x = fenetre->w - palette_d->w - 10;
    pos_palette_d.y = (fenetre->h / 2) - (palette_d->h / 2);
    printf("x = %d, y = %d\n", pos_palette_g.x, pos_palette_g.y);
    printf("x = %d, y = %d\n", pos_palette_d.x, pos_palette_d.y);

    TTF_Font *font_verdana;
    font_verdana = TTF_OpenFont("verdana.ttf", 24);

    /*
    SDL_Surface *chrono;
    char chrono_text[20];
    sprintf(chrono_text, "%d", SDL_GetTicks());
    chrono = TTF_RenderText_Blended(font_verdana, chrono_text, font_color);
    SDL_Rect chrono_position;
    chrono_position.x = 20;
    chrono_position.y = fenetre->h - chrono->h;

    SDL_Surface *mouse_coords;
    char mouse_coords_text[20];
    int mouse_x = 0;
    int mouse_y = 0;
    mouse_coords = TTF_RenderText_Blended(font_verdana, "0, 0", font_color);
    SDL_Rect mouse_coords_position;
    mouse_coords_position.x = fenetre->w - mouse_coords->w;
    mouse_coords_position.y = fenetre->h - mouse_coords->h;
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
                            pos_palette_d.y = fmin(
                                fenetre->h - palette_d->h,
                                pos_palette_d.y + palette_d->h / 4
                                );
                            break;
                        case SDLK_UP:
                            pos_palette_d.y = fmax(
                                0,
                                pos_palette_d.y - palette_d->h / 4
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
                    mouse_coords_position.x = fenetre->w - mouse_coords->w;
                    mouse_coords_position.y = fenetre->h - mouse_coords->h;
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
            pos_balle_f.x = pos_balle_f.x + balle_velocite * cosf(balle_direction);
            pos_balle_f.y = pos_balle_f.y - balle_velocite * sinf(balle_direction);
            if (pos_balle_f.y <= 0) {
                /* Top wall collision */
                pos_balle_f.y = -pos_balle_f.y;
                balle_direction = M_TAU - balle_direction;
                vlineRGBA(fenetre,
                          pos_balle_f.x + balle->w / 2, 0, fenetre->h / 4,
                          255, 0, 0, 255);
                printf("Direction : %f\n", balle_direction / M_TAU);
            }
            if (pos_balle_f.y >= fenetre->h - balle->h) {
                /* Bottom wall collision */
                pos_balle_f.y = fenetre->h
                              - (pos_balle_f.y + balle->h - fenetre->h)
                              - balle->h;
                balle_direction = M_TAU - balle_direction;
                vlineRGBA(fenetre,
                          pos_balle_f.x + balle->w / 2, fenetre->h * 3 / 4, fenetre->h,
                          255, 0, 0, 255);
                printf("Direction : %f\n", balle_direction / M_TAU);
            }
            if (pos_balle_f.x <= 0) {
                /* Left wall collision */
                pos_balle_f.x = -pos_balle_f.x;
                if (balle_direction > M_TAU / 2) {
                    balle_direction = M_TAU - (balle_direction - M_TAU / 2);
                } else {
                    balle_direction = M_TAU - (balle_direction + M_TAU / 2);
                }
                hlineRGBA(fenetre,
                          0, fenetre->w / 4, pos_balle_f.y + balle->h / 2,
                          255, 0, 0, 255);
                printf("Direction : %f\n", balle_direction / M_TAU);
            }
            if (pos_balle_f.x >= fenetre->w - balle->w) {
                /* Right wall collision */
                pos_balle_f.x = fenetre->w
                              - (pos_balle_f.x + balle->w - fenetre->w)
                              - balle->w;
                if (balle_direction > M_TAU * 3 / 4) {
                    balle_direction = M_TAU / 2 + (M_TAU - balle_direction);
                } else {
                    balle_direction = M_TAU / 2 - balle_direction;
                }
                hlineRGBA(fenetre,
                          fenetre->w * 3 / 4, fenetre->w,
                          pos_balle_f.y + balle->h / 2,
                          255, 0, 0, 255);
                printf("Direction : %f\n", balle_direction / M_TAU);
            }
            pos_balle.x = pos_balle_f.x;
            pos_balle.y = pos_balle_f.y;
        }

        /* Computer's move */

        /* Sreen refresh */
        //SDL_FillRect(fenetre, NULL, color_bg);
        SDL_BlitSurface(balle, NULL, fenetre, &pos_balle);
        SDL_BlitSurface(palette_g, NULL, fenetre, &pos_palette_g);
        SDL_BlitSurface(palette_d, NULL, fenetre, &pos_palette_d);
        /*
        vlineRGBA(fenetre,
                  mouse_x, 0, fenetre->h,
                  255, 0, 0, 255);
        hlineRGBA(fenetre,
                  0, fenetre->w, mouse_y,
                  255, 0, 0, 255);
        sprintf(chrono_text, "%d", now);
        chrono = TTF_RenderText_Blended(font_verdana, chrono_text, font_color);
        SDL_BlitSurface(chrono, NULL, fenetre, &chrono_position);
        SDL_BlitSurface(mouse_coords, NULL, fenetre, &mouse_coords_position);
        */
        SDL_Flip(fenetre);
        before = now;
    }
    printf("Running time: %d\n", SDL_GetTicks());
    SDL_FreeSurface(fenetre);
    SDL_FreeSurface(balle);
    SDL_FreeSurface(palette_g);
    SDL_FreeSurface(palette_d);
    TTF_CloseFont(font_verdana);
    SDL_Quit();
    TTF_Quit();
    return 0;
}
