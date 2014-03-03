#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_gfxPrimitives.h>

int main(int argc, char *argv[]) {

    if (SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "SDL error : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    if (TTF_Init()) {
        fprintf(stderr, "TTF_Init error\n");
        exit(EXIT_FAILURE);
    }

    SDL_Surface *fenetre, *balle, *palette_d, *palette_g;
    fenetre = SDL_SetVideoMode(500, 500, 32, SDL_HWSURFACE);
    balle = SDL_CreateRGBSurface(SDL_HWSURFACE, 10, 10, 32, 0, 0, 0, 0);
    palette_g = SDL_CreateRGBSurface(SDL_HWSURFACE, 10, 50, 32, 0, 0, 0, 0);
    palette_d = SDL_CreateRGBSurface(SDL_HWSURFACE, 10, 50, 32, 0, 0, 0, 0);

    Uint32 color_bg, color_fg;
    color_bg = SDL_MapRGB(fenetre->format, 0, 0, 0);
    color_fg = SDL_MapRGB(fenetre->format, 255, 255, 255);

    SDL_FillRect(fenetre, NULL, color_bg);
    SDL_FillRect(balle, NULL, color_fg);
    SDL_FillRect(palette_d, NULL, color_fg);
    SDL_FillRect(palette_g, NULL, color_fg);

    SDL_Rect pos_balle, pos_palette_g, pos_palette_d;
    pos_balle.x = (fenetre->w / 2) - (balle->w / 2);
    pos_balle.y = (fenetre->h / 2) - (balle->h / 2);
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
                        case SDLK_DOWN:
                            personnage = IMG_Load("pacman_down.jpg");
                            personnage_position.y += 50;
                            break;
                        case SDLK_UP:
                            personnage = IMG_Load("pacman_up.jpg");
                            personnage_position.y -= 50;
                            break;
                        */
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
        /* Sreen refresh */
        SDL_FillRect(fenetre, NULL, color_bg);
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
