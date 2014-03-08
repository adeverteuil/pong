#include <math.h>

/* http://tauday.com/ */
#define M_TAU (M_PI * 2)  /* No, really, pi is wrong... */

struct PongBall {
    float x;
    float y;
    float heading;
    float velocity;
    SDL_Surface *sprite;
};

void draw_image(SDL_Surface *src, SDL_Surface *dst, int x, int y);

struct PongBall init_ball(void);
