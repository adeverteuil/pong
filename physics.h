// File physics.h

#ifndef PHYSICS_H
#define PHYSICS_H

#include <SDL.h>

struct BoundingBox {
    float min_x;
    float max_x;
    float min_y;
    float max_y;
};

//Return 1 if a intersects b.
int collision(struct BoundingBox a, struct BoundingBox b);

//Sets bounding box of a sprite given its position.
void set_bounding_box(struct BoundingBox *box, SDL_Surface *sprite, int x, int y);

#endif /* PHYSICS_H */
