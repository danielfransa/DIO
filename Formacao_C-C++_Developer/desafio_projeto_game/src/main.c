#include "ai.h"
#include "game.h"
#include "input.h"
#include "render.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static int move_cursor(int cursor, Key key)
{
    switch (key) {
        case KEY_UP:
            return (cursor + 6) % BOARD_SIZE;
        case KEY_DOWN:
            return (cursor + 3) % BOARD_SIZE;
        case KEY_LEFT:
            return cursor % 3 == 0 ? cursor + 2 : cursor - 1;
        case KEY_RIGHT:
            return cursor % 3 == 2 ? cursor - 2 : cursor + 1;
        default:
            return cursor;
    }
}

static void apply_score(Score *score, GameResult result)
{
    if (result == GAME_PLAYER_WIN) {
        score->player_wins++;
    } else if (result == GAME_COMPUTER_WIN) {
        score->computer_wins++;
    } else if (result == GAME_DRAW) {
        score->draws++;
    }
}

int main(void)
{
    Board board;
    Score score = {0, 0, 0};
    GameResult result = GAME_RUNNING;
    AiDifficulty difficulty;
    int cursor = 0;
    int game_number = 1;

    if (!input_enable_raw_mode()) {
        fprintf(stderr, "Nao foi possivel configurar o terminal.\n");
        return EXIT_FAILURE;
    }

    atexit(input_disable_raw_mode);
    srand((unsigned int) time(NULL));
    board_reset(&board);
    difficulty = ai_difficulty_for_game(game_number);
    render_game(&board, cursor, &score, result);

    for (;;) {
        Key key = input_read_key();

        if (key == KEY_CTRL_C) {
            break;
        }

        if (result != GAME_RUNNING) {
            if (key == KEY_ENTER) {
                board_reset(&board);
                cursor = 0;
                game_number++;
                difficulty = ai_difficulty_for_game(game_number);
                result = GAME_RUNNING;
                render_game(&board, cursor, &score, result);
            }
            continue;
        }

        cursor = move_cursor(cursor, key);

        if (key == KEY_SPACE && board_mark(&board, cursor, CELL_PLAYER)) {
            result = game_result(&board);

            if (result == GAME_RUNNING) {
                int pc_move = ai_choose_move(&board, difficulty);

                if (pc_move >= 0) {
                    board_mark(&board, pc_move, CELL_COMPUTER);
                }

                result = game_result(&board);
            }

            if (result != GAME_RUNNING) {
                apply_score(&score, result);
            }
        }

        render_game(&board, cursor, &score, result);
    }

    input_disable_raw_mode();
    printf("\033[2J\033[H");
    printf("Obrigado por jogar!\n");
    return EXIT_SUCCESS;
}
