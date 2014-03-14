struct PongPaddle {
    float x;
    float y;
    SDL_Surface *sprite;
};

//Initialize paddle structure.
struct PongPaddle init_paddle(void);
