# Explicação do arquivo `src/main.c`

## Papel do arquivo

O arquivo `main.c` coordena a aplicação.

Ele conecta os módulos:

- `game`: regras;
- `ai`: jogada do computador;
- `input`: leitura do teclado;
- `render`: desenho da tela.

`main.c` não deveria concentrar todos os detalhes. Ele funciona como orquestrador.

## Includes internos

```c
#include "ai.h"
#include "game.h"
#include "input.h"
#include "render.h"
```

Esses includes mostram a função integradora de `main.c`.

## Includes da biblioteca padrão

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
```

- `stdio.h`: usado para mensagens finais e erro.
- `stdlib.h`: usado para `EXIT_SUCCESS`, `EXIT_FAILURE`, `atexit` e `srand`.
- `time.h`: usado para iniciar a aleatoriedade com `time(NULL)`.

## Função `move_cursor`

```c
static int move_cursor(int cursor, Key key)
```

Essa função calcula a nova posição do cursor.

O tabuleiro é linear, mas representa uma grade 3x3.

### Movimento vertical

```c
KEY_UP    -> (cursor + 6) % BOARD_SIZE
KEY_DOWN  -> (cursor + 3) % BOARD_SIZE
```

Subir equivale a voltar 3 casas. Como o código usa módulo, `+ 6` produz o mesmo efeito de `- 3` em um tabuleiro de 9 posições, mas sem risco de índice negativo.

### Movimento horizontal

```c
KEY_LEFT
KEY_RIGHT
```

O código trata as bordas da linha para permitir navegação circular.

Exemplo: se o cursor está na coluna 0 e o usuário aperta esquerda, ele vai para a coluna 2 da mesma linha.

## Função `apply_score`

```c
static void apply_score(Score *score, GameResult result)
```

Atualiza o placar de acordo com o resultado da partida.

Ela incrementa:

- vitórias do jogador;
- vitórias do computador;
- empates.

## Função `main`

```c
int main(void)
```

Essa é a entrada do programa.

### Inicialização

O programa:

1. declara o tabuleiro;
2. declara o placar;
3. define o resultado inicial;
4. define cursor e número da partida;
5. habilita o modo raw;
6. inicializa o gerador aleatório;
7. limpa o tabuleiro;
8. calcula a dificuldade;
9. renderiza a tela inicial.

### Loop principal

```c
for (;;) {
    Key key = input_read_key();
    ...
}
```

O loop lê uma tecla por vez e reage a ela.

### Saída com `Ctrl+C`

```c
if (key == KEY_CTRL_C) {
    break;
}
```

O programa encerra o loop e restaura o terminal.

### Reinício de partida

Se a partida acabou e o usuário aperta Enter:

1. limpa o tabuleiro;
2. reseta o cursor;
3. incrementa o número da partida;
4. recalcula a dificuldade;
5. renderiza a nova tela.

### Jogada do usuário

Se o jogo está rodando:

1. setas movem o cursor;
2. espaço tenta marcar `X`;
3. `board_mark` impede marcação em casa ocupada.

### Jogada do computador

Após o usuário marcar:

1. o jogo verifica se o usuário venceu;
2. se a partida continua, a IA escolhe uma casa;
3. o computador marca `O`;
4. o resultado é verificado novamente.

## Decisão arquitetural

`main.c` representa o caso de uso principal do jogo. Ele não implementa profundamente regras, IA, entrada ou saída. Ele coordena esses módulos.
