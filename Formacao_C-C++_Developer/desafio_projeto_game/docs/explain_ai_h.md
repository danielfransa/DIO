# Explicação do arquivo `include/ai.h`

## Papel do arquivo

O arquivo `ai.h` define a interface pública do módulo de inteligência artificial. Ele responde à pergunta:

> O que outros arquivos precisam conhecer para pedir uma jogada ao computador?

Ele não implementa a IA. A implementação fica em `src/ai.c`. Essa separação entre contrato (`.h`) e implementação (`.c`) é uma prática clássica em C.

## Include de `game.h`

```c
#include "game.h"
```

A IA precisa conhecer tipos definidos pelo módulo de regras, principalmente `Board` e `Cell`. Por isso, `ai.h` inclui `game.h`.

Essa dependência faz sentido: a IA decide uma jogada olhando para o tabuleiro. Ela depende do domínio do jogo, mas o domínio do jogo não depende da IA.

## Enum `AiDifficulty`

```c
typedef enum {
    AI_EASY,
    AI_RANDOM,
    AI_NORMAL
} AiDifficulty;
```

Esse enum representa os modos de comportamento do computador:

- `AI_EASY`: modo fácil, com alta chance de jogada aleatória.
- `AI_RANDOM`: modo totalmente aleatório.
- `AI_NORMAL`: modo mais estratégico.

Usar `enum` evita passar números sem significado, como `0`, `1` e `2`. Isso deixa a chamada mais clara e reduz erros.

## Função `ai_difficulty_for_game`

```c
AiDifficulty ai_difficulty_for_game(int game_number);
```

Essa função recebe o número da partida e retorna a dificuldade que deve ser usada.

Ela existe para isolar a regra do ciclo de dificuldade:

```text
1 normal
2 normal
3 aleatória
4 normal
5 normal
6 aleatória
7 normal
8 normal
9 aleatória
10 fácil
```

Depois da décima partida, o ciclo recomeça.

## Função `ai_choose_move`

```c
int ai_choose_move(const Board *board, AiDifficulty difficulty);
```

Essa função recebe:

- `const Board *board`: o estado atual do tabuleiro.
- `AiDifficulty difficulty`: a dificuldade ativa da partida.

Ela retorna:

- o índice da casa escolhida, entre `0` e `8`;
- `-1` se não houver jogada possível.

O `const` indica que a IA não deve alterar diretamente o tabuleiro. Ela apenas calcula uma decisão. Quem marca a jogada no tabuleiro é o fluxo principal em `main.c`.

## Decisão arquitetural

O arquivo `ai.h` deixa a IA substituível. Se no futuro a implementação mudar para Minimax, árvore de decisão ou outro algoritmo, os outros módulos podem continuar chamando as mesmas funções.
