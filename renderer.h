// File renderer.h

#ifndef RENDERER_H
#define RENDERER_H

#include "game.h"

//Utility function to blit src to dst centered at position (x, y).
void draw_image(SDL_Surface *src, SDL_Surface *dst, int x, int y);

//Draw a frame of the game.
void render_game(struct PongGame *game);

#endif /* not RENDERER_H */
