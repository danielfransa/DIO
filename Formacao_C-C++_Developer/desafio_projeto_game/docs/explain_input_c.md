# Explicação do arquivo `src/input.c`

## Papel do arquivo

O arquivo `input.c` implementa a leitura do teclado no terminal.

Ele transforma caracteres e sequências de escape em valores do enum `Key`.

## Includes

```c
#include "input.h"
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
```

- `input.h`: contrato do módulo.
- `stdio.h`: usado para `getchar`.
- `termios.h`: usado para configurar o terminal.
- `unistd.h`: usado para `STDIN_FILENO`.

## Variáveis internas

```c
static struct termios original_termios;
static int raw_mode_enabled = 0;
```

`original_termios` guarda a configuração original do terminal.

`raw_mode_enabled` indica se o modo raw está ativo.

Ambas são `static`, portanto ficam privadas ao arquivo.

## Função `input_enable_raw_mode`

```c
int input_enable_raw_mode(void)
```

Essa função configura o terminal para capturar teclas imediatamente.

### Passos principais

1. Salva a configuração atual com `tcgetattr`.
2. Copia essa configuração para `raw`.
3. Desativa flags como `ECHO`, `ICANON` e `ISIG`.
4. Ajusta `VMIN` e `VTIME`.
5. Aplica a configuração com `tcsetattr`.

### Por que desativar `ICANON`?

Sem isso, o terminal esperaria o usuário apertar Enter. Para um jogo, queremos reagir a cada tecla.

### Por que desativar `ECHO`?

Sem isso, o terminal imprimiria automaticamente as teclas digitadas.

### Por que desativar `ISIG`?

Isso permite tratar `Ctrl+C` como tecla, em vez de deixar o sistema encerrar o programa imediatamente.

## Função `input_disable_raw_mode`

```c
void input_disable_raw_mode(void)
```

Restaura o terminal para o estado original.

Isso evita que o terminal do usuário continue sem eco ou com comportamento estranho após sair do jogo.

## Função `input_read_key`

```c
Key input_read_key(void)
```

Essa função lê uma tecla e retorna um valor do enum `Key`.

### Teclas simples

- `3`: representa `Ctrl+C`.
- `' '`: representa espaço.
- `'\r'` ou `'\n'`: representam Enter.

### Setas

As setas chegam como sequências:

```text
ESC [ A
ESC [ B
ESC [ C
ESC [ D
```

O código lê os três caracteres e converte:

- `A`: cima;
- `B`: baixo;
- `C`: direita;
- `D`: esquerda.

## Decisão arquitetural

`input.c` isola o detalhe técnico do terminal. Se no futuro o jogo tiver outra forma de entrada, o restante do projeto não precisa mudar tanto.
