//File text.c

#include "text.h"

static TTF_Font *init_font(int size);

TTF_Font *init_font(int size) {
    TTF_Font *font;
    font=TTF_OpenFont("fonts/FreeMono.ttf", size);
    if(!font) {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    return font;
}

struct ScoreBoard init_scoreboard(void) {
    struct ScoreBoard board;
    board.font = init_font(32);
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

struct IdleTimeText init_idletimetext(void) {
    struct IdleTimeText text;
    text.font = init_font(12);
    text.surface = NULL;
    text.color.r = 255;
    text.color.g = 255;
    text.color.b = 255;
    update_idletimetext(&text, 0, 0, 0, 0);
    return text;
}

void update_idletimetext(struct IdleTimeText *text, int interval, int start, int now, long framecount) {
    if (framecount % 20) return;  //Only update every 20 frames.
    char string[] = "idle: 100.00%";  //Max text length.
    float idle;

    if (interval == 0) {
        idle = 0;
    } else {
        idle = ((float)(interval - (now - start)) / interval) * 100;
    }
    if (text->surface) {
        SDL_FreeSurface(text->surface);
    }
    sprintf(string, "idle: %.2f%%", idle);
    text->surface = TTF_RenderText_Solid(text->font, string, text->color);
}
