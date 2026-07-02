# Explicação do arquivo `include/game.h`

## Papel do arquivo

O arquivo `game.h` é o contrato central das regras do jogo. Ele define os tipos fundamentais usados por quase todos os módulos.

Este é o arquivo mais próximo do domínio do problema: jogo da velha, tabuleiro, células, resultado e placar.

## Constante `BOARD_SIZE`

```c
#define BOARD_SIZE 9
```

O tabuleiro tem 9 casas. Usar uma constante evita repetir o número `9` pelo código.

Se algum trecho precisa percorrer o tabuleiro, ele usa `BOARD_SIZE`. Isso melhora a manutenção e deixa a intenção clara.

## Enum `Cell`

```c
typedef enum {
    CELL_EMPTY = ' ',
    CELL_PLAYER = 'X',
    CELL_COMPUTER = 'O'
} Cell;
```

Esse enum representa o conteúdo de cada casa:

- vazia;
- marcada pelo usuário;
- marcada pelo computador.

Os valores são caracteres (`' '`, `'X'`, `'O'`) porque isso facilita a renderização no terminal.

## Enum `GameResult`

```c
typedef enum {
    GAME_RUNNING,
    GAME_PLAYER_WIN,
    GAME_COMPUTER_WIN,
    GAME_DRAW
} GameResult;
```

Esse enum representa o estado de uma partida:

- ainda em andamento;
- vitória do jogador;
- vitória do computador;
- empate.

Com isso, o restante do programa pode tomar decisões sem depender de códigos numéricos obscuros.

## Struct `Board`

```c
typedef struct {
    Cell cells[BOARD_SIZE];
} Board;
```

O tabuleiro é guardado como um array linear de 9 posições.

O mapeamento é:

```text
0 | 1 | 2
3 | 4 | 5
6 | 7 | 8
```

Essa escolha simplifica loops e evita uma matriz bidimensional para um caso pequeno.

## Struct `Score`

```c
typedef struct {
    int player_wins;
    int computer_wins;
    int draws;
} Score;
```

Essa struct guarda o placar da sessão:

- vitórias do usuário;
- vitórias do PC;
- empates.

Ela fica no domínio compartilhado porque `main.c` atualiza o placar e `render.c` exibe o placar.

## Funções declaradas

```c
void board_reset(Board *board);
int board_is_full(const Board *board);
int board_mark(Board *board, int position, Cell cell);
GameResult game_result(const Board *board);
```

### `board_reset`

Limpa o tabuleiro e coloca todas as casas como vazias.

### `board_is_full`

Verifica se não existe mais casa vazia.

### `board_mark`

Tenta marcar uma casa. Retorna `1` se conseguiu e `0` se a posição era inválida ou já estava ocupada.

### `game_result`

Calcula o estado atual da partida.

## Decisão arquitetural

`game.h` funciona como o núcleo do projeto. Ele não depende de terminal, IA ou renderização. Essa independência é importante porque as regras do jogo devem ser simples e reutilizáveis.
