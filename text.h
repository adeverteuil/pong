// File text.h

#ifndef TEXT_H
#define TEXT_H

#include <SDL_ttf.h>

struct ScoreBoard {
    TTF_Font *font;
    SDL_Color color;
    int player1;
    int player2;
    SDL_Surface *surface;
};

struct IdleTimeText {
    TTF_Font *font;
    SDL_Color color;
    int framerate;
    int lastframe;
    int now;
    SDL_Surface *surface;
};

struct ScoreBoard init_scoreboard();
struct IdleTimeText init_idletimetext();

//If player1 + player2 == 0, reset score. Otherwise, these are values to increment.
void update_scoreboard(struct ScoreBoard *board, int player1, int player2);

void update_idletimetext(struct IdleTimeText *text, int interval, int start, int now, long framecount);

#endif /* TEXT_H */
