# Explicação do arquivo `src/game.c`

## Papel do arquivo

O arquivo `game.c` implementa as regras do jogo da velha.

Ele não cuida de teclado, tela ou IA. Seu trabalho é manipular o tabuleiro e responder o estado da partida.

## Include de `game.h`

```c
#include "game.h"
```

O arquivo inclui seu próprio contrato para usar os tipos `Board`, `Cell`, `Score` e `GameResult`.

## Tabela `WIN_LINES`

```c
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
```

Essa tabela guarda todas as combinações vencedoras.

O tabuleiro é linear:

```text
0 | 1 | 2
3 | 4 | 5
6 | 7 | 8
```

Cada linha da tabela representa três posições que formam vitória.

## Função `board_reset`

```c
void board_reset(Board *board)
```

Percorre todas as casas do tabuleiro e coloca `CELL_EMPTY`.

Essa função é usada:

- no início do programa;
- quando o usuário inicia uma nova partida.

## Função `board_is_full`

```c
int board_is_full(const Board *board)
```

Verifica se ainda existe alguma casa vazia.

Retorna:

- `0` se encontrou pelo menos uma casa vazia;
- `1` se todas as casas estão preenchidas.

Ela é usada por `game_result` para detectar empate.

## Função `board_mark`

```c
int board_mark(Board *board, int position, Cell cell)
```

Tenta marcar uma casa.

Antes de alterar o tabuleiro, a função valida:

1. se a posição está entre `0` e `8`;
2. se a casa está vazia.

Se qualquer validação falhar, retorna `0`.

Essa proteção impede sobrescrever jogadas existentes.

## Função `game_result`

```c
GameResult game_result(const Board *board)
```

Essa função calcula o estado da partida.

Primeiro, percorre `WIN_LINES`. Para cada combinação:

1. pega as três células;
2. verifica se não estão vazias;
3. verifica se são iguais.

Se encontrar três iguais, retorna vitória do jogador ou do computador.

Se ninguém venceu, chama `board_is_full`. Se o tabuleiro estiver cheio, retorna empate.

Caso contrário, retorna `GAME_RUNNING`.

## Decisão arquitetural

`game.c` é o núcleo das regras. Ele é independente de interface e pode ser testado sem terminal.
