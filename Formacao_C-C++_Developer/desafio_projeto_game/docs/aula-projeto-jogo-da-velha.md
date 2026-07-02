# Aula: Construindo um Jogo da Velha em C para Terminal

## 1. Objetivo da aula

Este documento explica, passo a passo, como este projeto foi pensado e estruturado. O projeto é um jogo da velha em C para terminal, no qual:

- o usuário joga com `X`;
- o computador joga com `O`;
- o usuário move o cursor com as setas;
- o usuário marca a casa com espaço;
- o computador joga automaticamente após a jogada do usuário;
- o placar vale apenas durante a sessão aberta;
- ao final de uma partida, `Enter` inicia uma nova partida;
- `Ctrl+C` encerra o jogo.

A intenção pedagógica não é apenas mostrar "um código que funciona", mas estudar como organizar um pequeno projeto C de maneira compreensível, modular e evolutiva.

Mesmo sendo um jogo simples, ele possui vários conceitos importantes:

- modelagem de estado;
- separação de responsabilidades;
- interface entre módulos usando arquivos `.h`;
- implementação em arquivos `.c`;
- compilação incremental com `Makefile`;
- leitura de teclado em modo terminal;
- renderização textual;
- estratégia simples de inteligência artificial;
- relação com princípios de Clean Code e Clean Architecture.

## 2. Visão geral do projeto

A estrutura do projeto ficou assim:

```text
desafio_projeto_game/
|-- build/
|   `-- .gitkeep
|-- docs/
|   `-- aula-projeto-jogo-da-velha.md
|-- include/
|   |-- ai.h
|   |-- game.h
|   |-- input.h
|   `-- render.h
|-- src/
|   |-- ai.c
|   |-- game.c
|   |-- input.c
|   |-- main.c
|   `-- render.c
|-- .gitignore
|-- Makefile
`-- README.md
```

Essa organização segue uma convenção muito comum em projetos C:

- `include/`: contém os arquivos de cabeçalho, ou seja, as interfaces públicas dos módulos.
- `src/`: contém as implementações.
- `build/`: recebe arquivos gerados pela compilação, como objetos `.o`.
- `docs/`: guarda documentação técnica e material de estudo.
- `Makefile`: automatiza compilação, execução e limpeza.
- `README.md`: explica rapidamente como compilar e jogar.

Historicamente, essa separação aparece em muitos projetos C e C++ porque a linguagem C trabalha com um modelo de compilação separado. Cada arquivo `.c` pode ser compilado individualmente para gerar um arquivo objeto `.o`. Depois, o linker une esses objetos em um executável final.

Essa forma de trabalhar influenciou a arquitetura de muitos sistemas Unix, bibliotecas de sistema, kernels, ferramentas de linha de comando e projetos embarcados.

## 3. Por que separar `include/` e `src/`?

Em C, arquivos `.h` e `.c` têm papéis diferentes.

O arquivo `.h` diz:

> "Estas são as funções, tipos e constantes que este módulo oferece."

O arquivo `.c` diz:

> "Esta é a implementação concreta dessas funções."

Essa separação cria um contrato. Outros arquivos não precisam saber todos os detalhes internos de um módulo; eles precisam apenas incluir o cabeçalho correto.

Exemplo:

```c
#include "game.h"
```

Ao fazer isso, um arquivo passa a conhecer os tipos `Board`, `Score`, `GameResult` e funções como `board_mark` e `game_result`, sem precisar conhecer detalhes internos como a tabela `WIN_LINES`.

Essa ideia se conecta diretamente com dois princípios importantes:

- Encapsulamento: esconder detalhes internos.
- Baixo acoplamento: reduzir dependência entre partes do sistema.

Em Clean Architecture, essa ideia aparece como a separação entre regras de negócio e detalhes externos. No nosso projeto, as regras do jogo ficam em `game.c`, enquanto detalhes de terminal ficam em `input.c` e `render.c`.

## 4. Decisões de arquitetura

### 4.1 Arquitetura modular

O projeto foi dividido em módulos pequenos:

```text
game   -> regras e estado do jogo
ai     -> decisão da jogada do computador
input  -> leitura do teclado
render -> desenho da tela no terminal
main   -> fluxo principal da aplicação
```

Essa divisão evita que todo o código fique dentro de `main.c`. Em programas pequenos isso pode parecer excesso, mas para estudo e uma ótima prática. Ela mostra como um software cresce com mais organização.

Se todo o código estivesse em um único arquivo, teríamos:

- maior dificuldade de leitura;
- maior chance de alterar uma parte e quebrar outra;
- mais dificuldade para testar funções isoladas;
- menor reutilização.

Separar em módulos e uma aplicação prática do princípio da responsabilidade única, muito associado ao SOLID e ao Clean Code.

Cada módulo deve ter um motivo principal para mudar:

- `game.c` muda se as regras do jogo mudarem.
- `ai.c` muda se a estratégia do computador mudar.
- `input.c` muda se a forma de ler teclado mudar.
- `render.c` muda se a tela mudar.
- `main.c` muda se o fluxo da aplicação mudar.

### 4.2 Regras independentes da interface

Uma decisão importante foi manter as regras do jogo em `game.c`, sem depender de terminal, teclado, cores ou `printf`.

Isso significa que a função `game_result` não sabe se o jogo roda no terminal, em uma interface gráfica, em um navegador ou em testes automatizados. Ela apenas recebe um tabuleiro e responde o estado do jogo.

Essa é uma versão pequena de uma ideia central da Clean Architecture:

> As regras de negócio devem depender menos dos detalhes externos.

No nosso projeto:

- regra do jogo = núcleo;
- terminal = detalhe externo;
- teclado = detalhe externo;
- renderização = detalhe externo;
- Makefile = detalhe de build.

### 4.3 Uso de `enum` para clareza

Em vez de espalhar números mágicos pelo código, foram criados `enum`.

Exemplo em `game.h`:

```c
typedef enum {
    CELL_EMPTY = ' ',
    CELL_PLAYER = 'X',
    CELL_COMPUTER = 'O'
} Cell;
```

Isso deixa claro que uma célula pode estar vazia, ter a marca do jogador ou ter a marca do computador.

Outro exemplo:

```c
typedef enum {
    GAME_RUNNING,
    GAME_PLAYER_WIN,
    GAME_COMPUTER_WIN,
    GAME_DRAW
} GameResult;
```

Esse `enum` evita que o programa retorne códigos pouco expressivos, como `0`, `1`, `2` e `3`, sem significado evidente.

Essa escolha dialoga com Clean Code: nomes devem revelar intenção.

### 4.4 Uso de `struct` para estado

O tabuleiro foi modelado assim:

```c
typedef struct {
    Cell cells[BOARD_SIZE];
} Board;
```

E o placar assim:

```c
typedef struct {
    int player_wins;
    int computer_wins;
    int draws;
} Score;
```

Essa decisão agrupa dados relacionados. Em vez de passar vários arrays e contadores soltos, o código passa uma unidade conceitual.

Um `Board` representa o tabuleiro. Um `Score` representa o placar. Isso torna as assinaturas das funções mais claras.

### 4.5 Uso de funções pequenas

O projeto evita funções muito grandes. Por exemplo, `ai_choose_move` usa funções auxiliares:

- `find_winning_move`;
- `choose_random_move`;
- `ai_difficulty_for_game`.

Essa decomposição facilita a leitura. Uma função deve responder a uma pergunta principal:

- "Existe uma jogada vencedora?"
- "Qual casa aleatória está vazia?"
- "Qual dificuldade vale para esta partida?"
- "Qual jogada a IA deve fazer agora?"

Essa forma de pensar é um fundamento prático de Clean Code.

## 5. Explicando cada arquivo de `include/`

## 5.1 `include/game.h`

Este é o cabeçalho do módulo de regras do jogo.

Ele define:

- tamanho do tabuleiro;
- tipos de células;
- resultados possíveis da partida;
- estrutura do tabuleiro;
- estrutura do placar;
- funções públicas para manipular o jogo.

Trecho importante:

```c
#define BOARD_SIZE 9
```

O jogo da velha tem 9 casas. Ao usar uma constante, evitamos repetir o número `9` em várias partes.

Tipos principais:

```c
typedef enum {
    CELL_EMPTY = ' ',
    CELL_PLAYER = 'X',
    CELL_COMPUTER = 'O'
} Cell;
```

Aqui, cada célula já carrega o caractere que será exibido no terminal.

Funções declaradas:

```c
void board_reset(Board *board);
int board_is_full(const Board *board);
int board_mark(Board *board, int position, Cell cell);
GameResult game_result(const Board *board);
```

Observe o uso de ponteiros:

- `Board *board`: usado quando a função pode alterar o tabuleiro.
- `const Board *board`: usado quando a função apenas lê o tabuleiro.

Essa é uma prática importante em C. O `const` documenta a intenção e ajuda o compilador a proteger o código contra alterações indevidas.

## 5.2 `include/ai.h`

Este cabeçalho define a interface da inteligência artificial.

```c
typedef enum {
    AI_EASY,
    AI_RANDOM,
    AI_NORMAL
} AiDifficulty;
```

O projeto possui três comportamentos:

- `AI_NORMAL`: tenta vencer, bloquear e escolher casas estratégicas.
- `AI_RANDOM`: escolhe qualquer casa vazia.
- `AI_EASY`: mistura comportamento aleatório com comportamento inteligente.

Funções públicas:

```c
AiDifficulty ai_difficulty_for_game(int game_number);
int ai_choose_move(const Board *board, AiDifficulty difficulty);
```

A função `ai_difficulty_for_game` aplica a regra de ciclo:

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

Depois da décima partida, a contagem reinicia.

Essa decisão cria previsibilidade para estudo e, ao mesmo tempo, torna o jogo menos frustrante para o usuário.

## 5.3 `include/input.h`

Este cabeçalho isola a entrada do teclado.

```c
typedef enum {
    KEY_NONE,
    KEY_UP,
    KEY_DOWN,
    KEY_LEFT,
    KEY_RIGHT,
    KEY_SPACE,
    KEY_ENTER,
    KEY_CTRL_C
} Key;
```

Em vez de o programa inteiro lidar com códigos crus do teclado, ele usa nomes semânticos.

Por exemplo:

- seta para cima vira `KEY_UP`;
- espaço vira `KEY_SPACE`;
- Enter vira `KEY_ENTER`;
- Ctrl+C vira `KEY_CTRL_C`.

Isso deixa o restante do código mais limpo. O `main.c` não precisa saber que uma seta do teclado chega como uma sequência de escape iniciada por `\033`.

Funções:

```c
int input_enable_raw_mode(void);
void input_disable_raw_mode(void);
Key input_read_key(void);
```

Esse módulo é um bom exemplo de isolamento de detalhes técnicos.

## 5.4 `include/render.h`

Este cabeçalho define como a tela será desenhada.

```c
void render_game(const Board *board, int cursor, const Score *score, GameResult result);
```

A função recebe tudo que precisa para desenhar:

- tabuleiro;
- posição atual do cursor;
- placar;
- resultado da partida.

Ela não decide regras. Ela apenas apresenta o estado atual.

Essa separação é fundamental: renderização não deve validar vitória, nem escolher jogada, nem alterar tabuleiro.

## 6. Explicando cada arquivo de `src/`

## 6.1 `src/game.c`

Este arquivo implementa as regras do jogo da velha.

### Linhas de vitória

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

O tabuleiro é representado como um array linear de 9 posições:

```text
0 | 1 | 2
3 | 4 | 5
6 | 7 | 8
```

As oito combinações de vitória são:

- três linhas;
- três colunas;
- duas diagonais.

O uso de uma tabela evita escrever vários `if` repetidos.

### Por que `static const`?

`static` limita a visibilidade da variável ao arquivo `game.c`.

Isso significa que outros arquivos não conseguem acessar diretamente `WIN_LINES`. Isso é bom porque essa tabela é um detalhe interno da implementação.

`const` indica que a tabela não deve ser alterada.

Essa combinação é comum em C para dados privados e imutáveis.

### `board_reset`

```c
void board_reset(Board *board)
{
    int i;

    for (i = 0; i < BOARD_SIZE; i++) {
        board->cells[i] = CELL_EMPTY;
    }
}
```

Essa função limpa o tabuleiro. Ela recebe ponteiro porque precisa alterar o `Board`.

### `board_mark`

```c
int board_mark(Board *board, int position, Cell cell)
```

Essa função tenta marcar uma casa.

Ela retorna:

- `1` se conseguiu marcar;
- `0` se a posição era inválida ou já estava ocupada.

Essa decisão é importante porque protege o estado do jogo. Mesmo que o usuário mova o cursor para uma casa ocupada e aperte espaço, `board_mark` não sobrescreve a jogada anterior.

### `game_result`

Essa função verifica se alguém venceu, se houve empate ou se a partida continua.

Ela percorre `WIN_LINES` e compara as três posições de cada linha de vitória.

Essa função pertence ao domínio do jogo. Ela não sabe nada sobre teclado, terminal ou IA.

## 6.2 `src/ai.c`

Este arquivo implementa a jogada do computador.

### Ordem de decisão no modo normal

No modo normal, a IA segue esta ordem:

1. Se puder vencer agora, vence.
2. Se o jogador puder vencer na próxima jogada, bloqueia.
3. Se nada disso ocorrer, escolhe uma casa preferencial.

As casas preferenciais são:

```c
static const int PREFERRED_MOVES[BOARD_SIZE] = {4, 0, 2, 6, 8, 1, 3, 5, 7};
```

Essa ordem privilegia:

- centro;
- cantos;
- laterais.

No jogo da velha, centro e cantos costumam ser posições fortes.

### `find_winning_move`

Essa função simula jogadas.

Para cada casa vazia:

1. copia o tabuleiro;
2. marca temporariamente a casa;
3. verifica se aquela jogada venceria.

Trecho conceitual:

```c
Board test = *board;
test.cells[i] = cell;
```

Essa cópia é pequena, pois o tabuleiro tem apenas 9 células. Em projetos maiores, essa decisão poderia exigir outra estratégia.

### Modos de dificuldade

O projeto possui três modos:

```c
AI_NORMAL
AI_RANDOM
AI_EASY
```

O modo `AI_RANDOM` sempre escolhe uma casa vazia aleatória. Isso deixa o computador bem mais fraco.

O modo `AI_EASY` tem uma alta chance de jogar aleatoriamente, mas ainda pode fazer uma jogada inteligente em alguns momentos.

O modo `AI_NORMAL` usa a estratégia mais forte.

### Ciclo de partidas

A função `ai_difficulty_for_game` calcula a dificuldade com base no número da partida:

```c
int cycle_position = (game_number - 1) % 10 + 1;
```

Esse cálculo transforma qualquer partida em uma posição de 1 a 10.

Exemplos:

```text
game_number = 1  -> cycle_position = 1
game_number = 10 -> cycle_position = 10
game_number = 11 -> cycle_position = 1
game_number = 12 -> cycle_position = 2
```

Isso usa aritmética modular, um recurso muito comum em jogos, menus circulares, calendários, buffers circulares e sistemas de turnos.

## 6.3 `src/input.c`

Este arquivo é responsável pela leitura do teclado.

Normalmente, no terminal, o programa só recebe a entrada depois que o usuário aperta Enter. Para um jogo, isso seria ruim. Queremos reagir imediatamente a cada seta ou espaço.

Por isso o projeto usa `termios`.

### Modo canônico e modo raw

Em modo canônico, o terminal espera uma linha completa.

Em modo raw, o programa recebe teclas de forma mais direta.

No código:

```c
raw.c_lflag &= (tcflag_t) ~(ECHO | ICANON | ISIG);
```

Essa linha desativa:

- `ECHO`: o terminal não imprime automaticamente o que o usuário digita.
- `ICANON`: a entrada não fica presa esperando Enter.
- `ISIG`: sinais como Ctrl+C deixam de interromper automaticamente o processo.

Como `ISIG` foi desativado, o próprio programa consegue ler `Ctrl+C` como tecla e encerrar de forma controlada, restaurando o terminal antes de sair.

### Restaurando o terminal

Antes de mudar o terminal, o projeto salva a configuração original:

```c
tcgetattr(STDIN_FILENO, &original_termios)
```

Ao sair, restaura:

```c
tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_termios)
```

Essa é uma decisão essencial. Programas de terminal que não restauram o modo original podem deixar o terminal em um estado estranho.

### Leitura das setas

Setas não chegam como um único caractere simples. Em muitos terminais, elas chegam como sequências de escape.

Exemplo conceitual:

```text
ESC [ A -> seta para cima
ESC [ B -> seta para baixo
ESC [ C -> seta para direita
ESC [ D -> seta para esquerda
```

O módulo `input.c` converte isso para `KEY_UP`, `KEY_DOWN`, `KEY_RIGHT` e `KEY_LEFT`.

Essa conversão é um exemplo de adaptador: o módulo transforma uma interface técnica e pouco amigável em uma interface simples para o resto do programa.

## 6.4 `src/render.c`

Este arquivo desenha o jogo no terminal.

### Limpeza de tela

```c
printf("\033[2J\033[H");
```

Esse comando usa sequências ANSI:

- `\033[2J`: limpa a tela;
- `\033[H`: move o cursor para o início.

Isso permite redesenhar a tela inteira a cada jogada.

### Cursor visual

O cursor do jogo é mostrado com colchetes:

```text
[.]
[X]
[O]
```

Casas vazias são exibidas como `.` para que o usuário veja onde pode jogar.

### Separação entre desenho e regra

`render_game` não altera o estado do jogo. Ela recebe dados e imprime.

Esse é um padrão importante: funções de apresentação devem apresentar, não decidir a lógica principal.

Em arquiteturas maiores, isso se relaciona com separações como:

- Model-View-Controller;
- Model-View-Presenter;
- camadas de apresentação na Clean Architecture.

Aqui, `render.c` funciona como uma camada simples de View.

## 6.5 `src/main.c`

Este arquivo coordena a aplicação.

Ele não deveria conter todas as regras detalhadas. Sua função principal é orquestrar:

1. preparar terminal;
2. iniciar estado;
3. desenhar tela;
4. ler tecla;
5. mover cursor;
6. marcar jogada do usuário;
7. chamar IA;
8. verificar resultado;
9. atualizar placar;
10. reiniciar ou sair.

### Loop principal

O jogo roda dentro de:

```c
for (;;) {
    Key key = input_read_key();
    ...
}
```

Esse é um loop infinito controlado por eventos. Ele só termina quando o usuário pressiona `Ctrl+C`.

Loops desse tipo são comuns em jogos e aplicações interativas:

- ler entrada;
- atualizar estado;
- renderizar;
- repetir.

### Movimento do cursor

```c
static int move_cursor(int cursor, Key key)
```

Essa função recebe a posição atual e a tecla pressionada. Ela retorna a nova posição.

O tabuleiro é tratado como array linear, mas a movimentação respeita a ideia de grade 3x3.

Exemplo:

```c
case KEY_UP:
    return (cursor + 6) % BOARD_SIZE;
```

Subir equivale a voltar 3 posições. Para permitir circular da primeira linha para a última, usa-se `+ 6`, que é equivalente a `- 3` em módulo 9.

### Por que o cursor pode passar por casas ocupadas?

Uma decisão de usabilidade foi permitir que o cursor navegue por qualquer casa. Mesmo que uma casa já tenha `X` ou `O`, o cursor pode passar por ela.

Mas marcar uma casa ocupada continua proibido por `board_mark`.

Isso separa duas responsabilidades:

- navegação visual;
- validade da jogada.

Essa separação melhora a experiência do usuário e mantém a regra protegida no módulo correto.

### Placar da sessão

O placar fica em memória:

```c
Score score = {0, 0, 0};
```

Ele não é salvo em arquivo. Portanto, vale apenas durante a sessão aberta.

Essa foi uma decisão de escopo. Persistência em arquivo poderia ser uma evolução futura, mas não era necessária para o objetivo inicial.

## 7. O Makefile explicado

O `Makefile` automatiza o processo de compilação.

Sem Make, seria necessário digitar manualmente algo como:

```bash
gcc -std=c11 -Wall -Wextra -Wpedantic -Iinclude src/*.c -o jogo_da_velha
```

Isso funciona, mas não escala bem. Em projetos maiores, queremos:

- compilar apenas o que mudou;
- organizar objetos em `build/`;
- ter comandos padronizados;
- evitar comandos longos e repetitivos.

## 7.1 Variáveis

```make
CC := gcc
CFLAGS := -std=c11 -Wall -Wextra -Wpedantic -Iinclude
TARGET := jogo_da_velha
BUILD_DIR := build
SRC := $(wildcard src/*.c)
OBJ := $(SRC:src/%.c=$(BUILD_DIR)/%.o)
```

### `CC`

Define o compilador.

```make
CC := gcc
```

Se um dia quisermos usar `clang`, basta trocar essa linha.

### `CFLAGS`

Define flags de compilação.

```make
CFLAGS := -std=c11 -Wall -Wextra -Wpedantic -Iinclude
```

Significado:

- `-std=c11`: usa o padrão C11.
- `-Wall`: ativa muitos avisos importantes.
- `-Wextra`: ativa avisos adicionais.
- `-Wpedantic`: cobra mais conformidade com o padrão.
- `-Iinclude`: informa ao compilador onde procurar headers do projeto.

Usar warnings fortes é uma prática de qualidade. Muitos bugs aparecem primeiro como warnings.

### `SRC`

```make
SRC := $(wildcard src/*.c)
```

`wildcard` busca todos os arquivos `.c` dentro de `src/`.

### `OBJ`

```make
OBJ := $(SRC:src/%.c=$(BUILD_DIR)/%.o)
```

Essa substituição transforma:

```text
src/main.c  -> build/main.o
src/game.c  -> build/game.o
src/ai.c    -> build/ai.o
```

Ou seja, para cada fonte `.c`, existe um objeto `.o`.

## 7.2 Alvos principais

```make
.PHONY: all run clean
```

`.PHONY` informa ao Make que `all`, `run` e `clean` são comandos, não arquivos reais.

### `all`

```make
all: $(TARGET)
```

Quando o usuário roda:

```bash
make
```

O Make executa o primeiro alvo, que é `all`. Ele depende do executável final.

### Linkagem

```make
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@
```

Essa regra gera o executável final a partir dos objetos.

Variáveis automáticas:

- `$^`: todas as dependências, ou seja, todos os `.o`.
- `$@`: o alvo, ou seja, `jogo_da_velha`.

### Compilação de objetos

```make
$(BUILD_DIR)/%.o: src/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
```

Essa é uma regra de padrão.

Ela diz:

> Para gerar `build/algum_nome.o`, compile `src/algum_nome.c`.

Variáveis automáticas:

- `$<`: primeira dependência, o arquivo `.c`.
- `$@`: alvo, o arquivo `.o`.

### `run`

```make
run: $(TARGET)
	./$(TARGET)
```

Esse alvo compila se necessário e executa o jogo.

Uso:

```bash
make run
```

### `clean`

```make
clean:
	rm -f $(OBJ) $(TARGET)
```

Remove arquivos gerados:

- objetos `.o`;
- executável.

Ele não remove `build/.gitkeep`, pois queremos manter a pasta `build/` versionada no Git.

## 8. `.gitignore` e `build/.gitkeep`

O projeto ignora artefatos de compilação:

```gitignore
build/*
!build/.gitkeep
jogo_da_velha
```

Isso significa:

- ignore tudo dentro de `build/`;
- mas não ignore `build/.gitkeep`;
- ignore o executável `jogo_da_velha`.

Git não versiona pastas vazias. Por isso usamos `.gitkeep`, que é uma convenção da comunidade para manter uma pasta vazia no repositório.

Esse arquivo não tem função para o compilador. Ele existe apenas para o controle de versão.

## 9. Relação com Clean Code

Clean Code é um conjunto de práticas voltadas para legibilidade, manutenção e clareza.

Neste projeto, aplicamos várias ideias:

### Nomes expressivos

Exemplos:

- `board_reset`;
- `board_mark`;
- `game_result`;
- `ai_choose_move`;
- `input_read_key`;
- `render_game`.

Esses nomes dizem o que a função faz.

### Funções pequenas

Cada função tem um papel claro. Isso facilita leitura e teste.

### Evitar números mágicos

O projeto usa:

```c
#define BOARD_SIZE 9
```

Também usa enums para estados e teclas.

### Separação de responsabilidades

Cada arquivo tem uma finalidade:

- regra;
- IA;
- entrada;
- apresentação;
- fluxo.

### Controle de efeitos colaterais

Funções que alteram estado recebem ponteiros não constantes.

Funções que apenas leem recebem `const`.

Isso documenta intenção.

## 10. Relação com Clean Architecture

Clean Architecture, popularizada por Robert C. Martin, defende que regras importantes do sistema devem ficar separadas de detalhes externos.

Em um projeto grande, poderíamos ter camadas como:

```text
Entities
Use Cases
Interface Adapters
Frameworks and Drivers
```

Neste projeto pequeno, podemos fazer uma analogia:

```text
Regras do jogo      -> game.c / game.h
Caso de uso geral   -> main.c
Adaptador de entrada -> input.c / input.h
Adaptador de saída   -> render.c / render.h
Detalhe de build     -> Makefile
```

Naturalmente, este projeto não implementa Clean Architecture completa. Seria exagero para um jogo da velha de terminal. Mas ele aplica a ideia central:

> Regras importantes devem ser simples, isoladas e independentes de detalhes externos.

Por exemplo, `game_result` não chama `printf`, não lê teclado e não depende da IA. Isso é uma boa decisão arquitetural.

## 11. Fluxo de execução

O fluxo principal pode ser entendido assim:

```text
Início
  |
  v
Configura terminal em modo raw
  |
  v
Inicializa tabuleiro, placar e dificuldade
  |
  v
Renderiza tela
  |
  v
Lê tecla
  |
  +-- Ctrl+C? -> restaura terminal e sai
  |
  +-- Partida acabou?
  |      |
  |      +-- Enter? -> nova partida
  |      +-- Outra tecla? -> ignora
  |
  +-- Move cursor se tecla for seta
  |
  +-- Espaço em casa vazia?
         |
         v
      Marca X
         |
         v
      Verifica resultado
         |
         +-- Se continua: IA marca O
         |
         v
      Verifica resultado
         |
         v
      Atualiza placar se acabou
         |
         v
      Renderiza novamente
```

Esse tipo de raciocínio é essencial para programar jogos e interfaces interativas.

## 12. Possíveis evoluções para estudo

Este projeto pode crescer em várias direções.

### 12.1 Testes automatizados

Criar testes para:

- `board_mark`;
- `game_result`;
- `ai_difficulty_for_game`;
- `ai_choose_move`.

Isso ajudaria a estudar compilação de testes em C e validação de regras.

### 12.2 Minimax

A IA poderia usar o algoritmo Minimax, que encontra a melhor jogada possível em jogos de soma zero com informação perfeita.

Nesse caso, o computador ficaria invencível.

Como o objetivo atual inclui permitir que o usuário ganhe, o projeto preferiu uma IA com modos de dificuldade.

### 12.3 Cores ANSI

Poderíamos colorir:

- `X` em uma cor;
- `O` em outra;
- linha vencedora em destaque.

Isso ficaria no módulo `render.c`, pois é uma decisão de apresentação.

### 12.4 Persistência de placar

O placar poderia ser salvo em arquivo.

Isso criaria um novo módulo, talvez:

```text
score_storage.c
score_storage.h
```

Mas seria importante não misturar persistência diretamente em `game.c`.

### 12.5 Suporte a Windows

O uso de `termios` funciona em ambientes Unix-like, como Linux e macOS.

Para Windows nativo, seria necessário outro módulo de entrada, usando APIs específicas do console.

Essa é uma oportunidade para estudar portabilidade.

## 13. Exercícios sugeridos

1. Adicione uma mensagem na tela mostrando o número da partida atual.
2. Mostre na tela qual dificuldade está ativa: normal, aleatória ou fácil.
3. Implemente cores ANSI para `X` e `O`.
4. Crie uma função que detecte e destaque a linha vencedora.
5. Separe a lógica de placar em um módulo próprio.
6. Adicione testes automatizados para `game_result`.
7. Modifique o ciclo de dificuldade para 5 partidas em vez de 10.
8. Crie um modo "dois jogadores" local.

## 14. Conclusão

Este projeto mostra que até um jogo simples pode ensinar fundamentos importantes de desenvolvimento em C.

Ele trabalha com:

- modularização;
- cabeçalhos;
- ponteiros;
- enums;
- structs;
- compilação com Make;
- terminal em modo raw;
- separação de regras e interface;
- controle de estado;
- ciclo principal de jogo.

A principal lição arquitetural é: organize o programa de acordo com responsabilidades.

Quando cada módulo tem um papel claro, o código fica mais fácil de ler, explicar, testar e evoluir. Essa é a mesma ideia que aparece, em escala maior, em metodologias e arquiteturas como Clean Code, SOLID e Clean Architecture.
