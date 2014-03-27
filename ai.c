#include "ai.h"

void computer_move(struct PongGame *game) {
    struct PongPaddle *paddle_l = &(game->paddle_l);

    //Match the y position with that of the ball's.
    set_paddle_pos(paddle_l, game->ball.y, game->window);
}
