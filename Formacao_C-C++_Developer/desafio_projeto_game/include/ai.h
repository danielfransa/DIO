#ifndef AI_H
#define AI_H

#include "game.h"

typedef enum {
    AI_EASY,
    AI_RANDOM,
    AI_NORMAL
} AiDifficulty;

AiDifficulty ai_difficulty_for_game(int game_number);
int ai_choose_move(const Board *board, AiDifficulty difficulty);

#endif
