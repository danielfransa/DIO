#ifndef GAME_H
#define GAME_H

#define BOARD_SIZE 9

typedef enum {
    CELL_EMPTY = ' ',
    CELL_PLAYER = 'X',
    CELL_COMPUTER = 'O'
} Cell;

typedef enum {
    GAME_RUNNING,
    GAME_PLAYER_WIN,
    GAME_COMPUTER_WIN,
    GAME_DRAW
} GameResult;

typedef struct {
    Cell cells[BOARD_SIZE];
} Board;

typedef struct {
    int player_wins;
    int computer_wins;
    int draws;
} Score;

void board_reset(Board *board);
int board_is_full(const Board *board);
int board_mark(Board *board, int position, Cell cell);
GameResult game_result(const Board *board);

#endif
