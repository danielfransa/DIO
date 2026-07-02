# Explicação do arquivo `src/ai.c`

## Papel do arquivo

O arquivo `ai.c` implementa a inteligência artificial do computador.

Ele decide em qual casa o PC deve jogar, respeitando a dificuldade definida para a partida.

## Include de `ai.h`

```c
#include "ai.h"
```

O `.c` inclui seu próprio `.h` para garantir que a implementação esteja de acordo com a interface pública.

## Include de `stdlib.h`

```c
#include <stdlib.h>
```

Esse include é necessário para usar `rand`, usado nas jogadas aleatórias.

## Vetor `PREFERRED_MOVES`

```c
static const int PREFERRED_MOVES[BOARD_SIZE] = {4, 0, 2, 6, 8, 1, 3, 5, 7};
```

Esse vetor define a prioridade de casas quando a IA normal não tem uma vitória imediata nem precisa bloquear o jogador.

A ordem é:

1. centro;
2. cantos;
3. laterais.

No jogo da velha, centro e cantos são posições fortes.

O uso de `static const` indica que esse vetor é privado do arquivo e não deve ser alterado.

## Função `find_winning_move`

```c
static int find_winning_move(const Board *board, Cell cell)
```

Essa função procura uma jogada que faça determinado símbolo vencer.

Ela é usada de duas formas:

- com `CELL_COMPUTER`, para a IA tentar vencer;
- com `CELL_PLAYER`, para a IA tentar bloquear o jogador.

### Lógica interna

Para cada casa vazia:

1. cria uma cópia do tabuleiro;
2. marca temporariamente aquela casa;
3. chama `game_result`;
4. verifica se a jogada geraria vitória.

Como o tabuleiro tem apenas 9 casas, copiar o `Board` é simples e barato.

## Função `choose_random_move`

```c
static int choose_random_move(const Board *board)
```

Essa função escolhe uma casa vazia aleatória.

Primeiro, ela monta uma lista com todas as casas vazias. Depois, sorteia um índice dessa lista:

```c
return empty_cells[rand() % total];
```

Se não houver casa vazia, retorna `-1`.

## Função `ai_difficulty_for_game`

```c
AiDifficulty ai_difficulty_for_game(int game_number)
```

Essa função aplica o ciclo de dificuldade.

```c
int cycle_position = (game_number - 1) % 10 + 1;
```

Esse cálculo transforma qualquer número de partida em uma posição de 1 a 10.

Regra:

- partida 10 do ciclo: `AI_EASY`;
- partidas múltiplas de 3 no ciclo: `AI_RANDOM`;
- demais partidas: `AI_NORMAL`.

## Função `ai_choose_move`

```c
int ai_choose_move(const Board *board, AiDifficulty difficulty)
```

Essa é a função principal do módulo.

### Modo aleatório

```c
if (difficulty == AI_RANDOM) {
    return choose_random_move(board);
}
```

No modo aleatório, a IA não tenta vencer nem bloquear. Ela apenas escolhe uma casa vazia.

### Modo fácil

```c
if (difficulty == AI_EASY && rand() % 100 < 75) {
    return choose_random_move(board);
}
```

No modo fácil, existe 75% de chance de jogada aleatória. Nos outros 25%, a IA segue a estratégia normal.

### Modo normal

No modo normal, a IA:

1. tenta vencer;
2. tenta bloquear o jogador;
3. escolhe pela lista de preferências.

Essa ordem cria uma IA simples, mas ainda coerente.

## Decisão arquitetural

As funções auxiliares são `static` porque não fazem parte da interface pública. O único ponto de entrada externo é `ai_choose_move`, além da função que calcula a dificuldade.
