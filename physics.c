#include "physics.h"

int collision(struct BoundingBox a, struct BoundingBox b) {
    if (a.min_x > b.max_x ||
        a.min_y > b.max_y ||
        b.min_x > a.max_x ||
        b.min_y > a.max_y) {
        return 0;
    } else {
        return 1;
    }
}

void set_bounding_box(struct BoundingBox *box, SDL_Surface *sprite, int x, int y) {
    box->min_x = x - sprite->w / 2;
    box->max_x = box->min_x + sprite->w;
    box->min_y = y - sprite->h / 2;
    box->max_y = box->min_y + sprite->h;
}
