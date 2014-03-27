#include "ai.h"

#include "math.h"

void computer_move(struct PongGame *game) {
    struct PongPaddle *paddle_l = &(game->paddle_l);
    float target;

    switch (game->computer_behavior) {
        case AITheWall:
            //Match the y position with that of the ball's.
            set_paddle_pos(paddle_l, game->ball.y, game->window);
            break;
        case AIDelay:
            if (game->ball.heading > M_TAU / 4 &&
                game->ball.heading < M_TAU * 3 / 4) {
                target = game->ball.y;
                if (paddle_l->y - game->ball.y > 20) {
                    //Paddle's center is more than 20 pixels lower than the ball's.
                    set_paddle_pos(paddle_l, paddle_l->y - 5, game->window);
                } else if (paddle_l->y - game->ball.y < -20) {
                    //Paddle's center is more than 20 pixels higher than the ball's.
                    set_paddle_pos(paddle_l, paddle_l->y + 5, game->window);
                }
            }
            break;
    }
}
