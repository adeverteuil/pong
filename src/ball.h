struct PongBall {
    float x;
    float y;
    float heading;
    float velocity;
    SDL_Surface *sprite;
};

void draw_image(SDL_Surface *src, SDL_Surface *dst, int x, int y);

//Initialize ball structure.
struct PongBall init_ball(void);
