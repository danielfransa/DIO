# Explicação do arquivo `include/render.h`

## Papel do arquivo

O arquivo `render.h` declara a interface de renderização do jogo.

Ele responde à pergunta:

> Como outros módulos pedem para a tela ser redesenhada?

## Include de `game.h`

```c
#include "game.h"
```

O render precisa conhecer `Board`, `Score` e `GameResult`, pois esses tipos aparecem na assinatura de `render_game`.

## Função `render_game`

```c
void render_game(const Board *board, int cursor, const Score *score, GameResult result);
```

Essa função recebe todo o estado necessário para desenhar a tela:

- `board`: tabuleiro atual;
- `cursor`: casa selecionada pelo usuário;
- `score`: placar da sessão;
- `result`: estado da partida.

Ela não retorna valor porque seu efeito é visual: imprimir no terminal.

## Uso de `const`

Tanto `board` quanto `score` são recebidos como ponteiros constantes:

```c
const Board *board
const Score *score
```

Isso comunica que a renderização apenas lê o estado. Ela não deve alterar o jogo.

## Decisão arquitetural

O render é a camada de saída. Ele sabe como mostrar o jogo, mas não decide regras. Essa separação evita misturar apresentação com lógica de domínio.
