#include "text.h"

static TTF_Font *init_font();

TTF_Font *init_font() {
    TTF_Font *font;
    font=TTF_OpenFont("fonts/FreeMono.ttf", 32);
    if(!font) {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    return font;
}

struct ScoreBoard init_scoreboard() {
    struct ScoreBoard board;
    board.font = init_font();
    board.surface = NULL;
    board.color.r = 255;
    board.color.g = 255;
    board.color.b = 255;
    update_scoreboard(&board, 0, 0);
    return board;
}

void update_scoreboard(struct ScoreBoard *board, int player1, int player2) {
    char text[13];
    if (player1 + player2 == 0) {
        board->player1 = 0;
        board->player2 = 0;
    } else {
        board->player1 = (board->player1 + player1) % 0x1000;
        board->player2 = (board->player2 + player2) % 0x1000;
    }
    if (board->surface) {
        SDL_FreeSurface(board->surface);
    }
    sprintf(text, "0x%03x  0x%03x", board->player1, board->player2);
    board->surface = TTF_RenderText_Solid(board->font, text, board->color);
}
