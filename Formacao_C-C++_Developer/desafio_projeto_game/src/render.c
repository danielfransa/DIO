#include "render.h"

#include <stdio.h>

static const char *result_text(GameResult result)
{
    switch (result) {
        case GAME_PLAYER_WIN:
            return "Voce venceu!";
        case GAME_COMPUTER_WIN:
            return "Computador venceu!";
        case GAME_DRAW:
            return "Empate!";
        case GAME_RUNNING:
        default:
            return "Sua vez: setas movem, espaco marca.";
    }
}

static void print_cell(const Board *board, int index, int cursor)
{
    char value = (char) board->cells[index];

    if (index == cursor) {
        printf("[%c]", value == ' ' ? '.' : value);
        return;
    }

    printf(" %c ", value == ' ' ? '.' : value);
}

void render_game(const Board *board, int cursor, const Score *score, GameResult result)
{
    int row;

    printf("\033[2J\033[H");
    printf("Jogo da Velha - Terminal\n");
    printf("Voce: X | PC: O\n\n");
    printf("Placar da sessao\n");
    printf("Voce %d  |  PC %d  |  Empates %d\n\n",
           score->player_wins,
           score->computer_wins,
           score->draws);

    for (row = 0; row < 3; row++) {
        int base = row * 3;

        printf("   ");
        print_cell(board, base, cursor);
        printf("|");
        print_cell(board, base + 1, cursor);
        printf("|");
        print_cell(board, base + 2, cursor);
        printf("\n");

        if (row < 2) {
            printf("   ---+---+---\n");
        }
    }

    printf("\n%s\n", result_text(result));

    if (result != GAME_RUNNING) {
        printf("Pressione Enter para jogar novamente ou Ctrl+C para sair.\n");
    }

    fflush(stdout);
}
