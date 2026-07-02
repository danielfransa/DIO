#include "ai.h"

#include <stdlib.h>

static const int PREFERRED_MOVES[BOARD_SIZE] = {4, 0, 2, 6, 8, 1, 3, 5, 7};

static int find_winning_move(const Board *board, Cell cell)
{
    int i;

    for (i = 0; i < BOARD_SIZE; i++) {
        Board test = *board;

        if (test.cells[i] != CELL_EMPTY) {
            continue;
        }

        test.cells[i] = cell;
        if ((cell == CELL_COMPUTER && game_result(&test) == GAME_COMPUTER_WIN) ||
            (cell == CELL_PLAYER && game_result(&test) == GAME_PLAYER_WIN)) {
            return i;
        }
    }

    return -1;
}

static int choose_random_move(const Board *board)
{
    int empty_cells[BOARD_SIZE];
    int total = 0;
    int i;

    for (i = 0; i < BOARD_SIZE; i++) {
        if (board->cells[i] == CELL_EMPTY) {
            empty_cells[total] = i;
            total++;
        }
    }

    if (total == 0) {
        return -1;
    }

    return empty_cells[rand() % total];
}

AiDifficulty ai_difficulty_for_game(int game_number)
{
    int cycle_position = (game_number - 1) % 10 + 1;

    if (cycle_position == 10) {
        return AI_EASY;
    }

    if (cycle_position % 3 == 0) {
        return AI_RANDOM;
    }

    return AI_NORMAL;
}

int ai_choose_move(const Board *board, AiDifficulty difficulty)
{
    int i;
    int move;

    if (difficulty == AI_RANDOM) {
        return choose_random_move(board);
    }

    if (difficulty == AI_EASY && rand() % 100 < 75) {
        return choose_random_move(board);
    }

    move = find_winning_move(board, CELL_COMPUTER);

    if (move >= 0) {
        return move;
    }

    move = find_winning_move(board, CELL_PLAYER);
    if (move >= 0) {
        return move;
    }

    for (i = 0; i < BOARD_SIZE; i++) {
        move = PREFERRED_MOVES[i];
        if (board->cells[move] == CELL_EMPTY) {
            return move;
        }
    }

    return -1;
}
