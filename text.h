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

struct ScoreBoard init_scoreboard();

//If player1 + player2 == 0, reset score. Otherwise, these are values to increment.
void update_scoreboard(struct ScoreBoard *board, int player1, int player2);

#endif /* TEXT_H */
