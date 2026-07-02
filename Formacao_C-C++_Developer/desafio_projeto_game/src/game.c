#include "game.h"

static const int WIN_LINES[8][3] = {
    {0, 1, 2},
    {3, 4, 5},
    {6, 7, 8},
    {0, 3, 6},
    {1, 4, 7},
    {2, 5, 8},
    {0, 4, 8},
    {2, 4, 6}
};

void board_reset(Board *board)
{
    int i;

    for (i = 0; i < BOARD_SIZE; i++) {
        board->cells[i] = CELL_EMPTY;
    }
}

int board_is_full(const Board *board)
{
    int i;

    for (i = 0; i < BOARD_SIZE; i++) {
        if (board->cells[i] == CELL_EMPTY) {
            return 0;
        }
    }

    return 1;
}

int board_mark(Board *board, int position, Cell cell)
{
    if (position < 0 || position >= BOARD_SIZE) {
        return 0;
    }

    if (board->cells[position] != CELL_EMPTY) {
        return 0;
    }

    board->cells[position] = cell;
    return 1;
}

GameResult game_result(const Board *board)
{
    int i;

    for (i = 0; i < 8; i++) {
        Cell a = board->cells[WIN_LINES[i][0]];
        Cell b = board->cells[WIN_LINES[i][1]];
        Cell c = board->cells[WIN_LINES[i][2]];

        if (a != CELL_EMPTY && a == b && b == c) {
            return a == CELL_PLAYER ? GAME_PLAYER_WIN : GAME_COMPUTER_WIN;
        }
    }

    if (board_is_full(board)) {
        return GAME_DRAW;
    }

    return GAME_RUNNING;
}
