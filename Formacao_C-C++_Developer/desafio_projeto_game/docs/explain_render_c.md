# Explicação do arquivo `src/render.c`

## Papel do arquivo

O arquivo `render.c` implementa a apresentação visual do jogo no terminal.

Ele não altera o tabuleiro e não decide regras. Ele apenas desenha o estado recebido.

## Includes

```c
#include "render.h"
#include <stdio.h>
```

`render.h` traz o contrato da função `render_game`.

`stdio.h` é usado para `printf` e `fflush`.

## Função `result_text`

```c
static const char *result_text(GameResult result)
```

Converte o estado da partida em uma mensagem textual.

Exemplos:

- `GAME_PLAYER_WIN`: `"Voce venceu!"`;
- `GAME_COMPUTER_WIN`: `"Computador venceu!"`;
- `GAME_DRAW`: `"Empate!"`;
- `GAME_RUNNING`: mensagem de instrução.

Ela é `static` porque só é usada dentro de `render.c`.

## Função `print_cell`

```c
static void print_cell(const Board *board, int index, int cursor)
```

Imprime uma célula do tabuleiro.

Se a célula é a posição atual do cursor, ela aparece entre colchetes:

```text
[.]
[X]
[O]
```

Se não for o cursor, aparece com espaços:

```text
 . 
 X 
 O 
```

Casas vazias são exibidas como `.` para facilitar a visualização.

## Função `render_game`

```c
void render_game(const Board *board, int cursor, const Score *score, GameResult result)
```

Essa é a função pública do módulo.

Ela:

1. limpa a tela;
2. imprime título e legenda;
3. imprime placar;
4. imprime o tabuleiro;
5. imprime mensagem de estado;
6. mostra instrução de reinício se a partida terminou.

## Sequências ANSI

```c
printf("\033[2J\033[H");
```

Essa sequência:

- limpa a tela;
- move o cursor do terminal para o topo.

Com isso, o programa redesenha a tela inteira a cada atualização.

## `fflush(stdout)`

```c
fflush(stdout);
```

Força a saída a aparecer imediatamente no terminal.

Isso é útil em programas interativos, porque a tela precisa responder logo após cada tecla.

## Decisão arquitetural

`render.c` é a camada de apresentação. Ele depende do estado do jogo, mas não modifica esse estado. Essa separação deixa as regras em `game.c` e a interface visual em `render.c`.
