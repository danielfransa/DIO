# src/cli/main.c

Este arquivo implementa a interface de linha de comando.

Ele e a parte mais externa da aplicacao.

## Papel na arquitetura

A CLI conversa com o usuario.

Ela:

- Mostra instrucoes.
- Le argumentos do terminal.
- Le entrada interativa.
- Quebra linhas em partes.
- Chama a camada `app`.
- Imprime resultados e erros.

Ela nao deveria implementar regra matematica.

## Constantes

```c
#define INPUT_SIZE 128
#define OUTPUT_SIZE 128
#define DIRECT_TOKENS 5
```

`INPUT_SIZE` define o tamanho dos buffers de entrada interativa.

`OUTPUT_SIZE` define o tamanho do buffer usado para receber o resultado formatado.

`DIRECT_TOKENS` representa o maior numero de partes esperado em uma expressao direta:

```text
dec 10 + 1 bin
```

## print_usage

```c
static void print_usage(const char *program_name)
```

Mostra como usar o programa.

E chamada quando:

- O usuario passa `-h`.
- O usuario passa `--help`.
- A quantidade de argumentos e invalida.

Ela recebe `program_name` para imprimir o nome real usado no terminal, como `./bin/programmer_calc`.

## read_line

```c
static int read_line(const char *prompt, char *buffer, size_t size)
```

Mostra um prompt e le uma linha do teclado.

Usa `fgets`, que e mais segura que `gets`.

Depois remove o `\n` final, se existir.

Retorna:

- `1` se conseguiu ler.
- `0` se falhou.

## execute_request

```c
static int execute_request(const CalculationRequest *request)
```

Recebe uma requisicao de calculo ja montada.

Chama:

```c
run_calculation(request, output, sizeof(output))
```

Se der erro, imprime mensagem.

Se der certo, imprime:

```text
Resultado (decimal): 11
```

## execute_conversion

```c
static int execute_conversion(const ConversionRequest *request)
```

Parecida com `execute_request`, mas chama `run_conversion`.

Foi criada para manter conversao e calculo separados tambem na CLI.

## split_tokens

```c
static size_t split_tokens(char *line, char **tokens, size_t max_tokens)
```

Quebra uma linha em palavras separadas por espaco ou tab.

Exemplo:

```text
bin 01010110 dec
```

Vira:

```text
tokens[0] = bin
tokens[1] = 01010110
tokens[2] = dec
```

A funcao usa `strtok`, que altera a string original. Por isso o codigo cria uma copia antes de chamar essa funcao.

Se houver mais tokens que o permitido, retorna `max_tokens + 1`.

## try_parse_inline_calculation

```c
static int try_parse_inline_calculation(char **tokens, size_t count, CalculationRequest *request)
```

Tenta interpretar os tokens como calculo.

Formatos aceitos:

```text
bin 1010 + 11
bin 1010 + 11 dec
```

Se a base de saida nao for informada, a saida usa a mesma base de entrada.

A funcao apenas monta a request. Ela nao calcula.

## try_parse_inline_conversion

```c
static int try_parse_inline_conversion(char **tokens, size_t count, ConversionRequest *request)
```

Tenta interpretar os tokens como conversao.

Formato aceito:

```text
bin 01010110 dec
```

Ela espera exatamente tres tokens:

- Base de entrada.
- Valor.
- Base de saida.

## run_direct_mode

```c
static int run_direct_mode(int argc, char **argv)
```

Executa quando o usuario passa argumentos diretamente no terminal.

Exemplos:

```bash
./bin/programmer_calc bin 01010110 dec
./bin/programmer_calc dec 10 + 1 bin
```

Se `argc == 4`, o programa entende como conversao.

Se `argc == 5` ou `argc == 6`, entende como calculo.

## run_interactive_mode

```c
static int run_interactive_mode(void)
```

Executa quando o programa e chamado sem argumentos.

Primeiro ele permite digitar uma linha completa:

```text
bin 01010110 dec
```

ou:

```text
dec 10 + 1 bin
```

Se a linha nao for uma expressao completa, ele tenta tratar a entrada como base e pergunta os campos restantes separadamente.

Essa decisao deixa o programa mais amigavel para iniciantes.

## main

```c
int main(int argc, char **argv)
```

E o ponto de entrada do programa.

Fluxo:

1. Se nao ha argumentos, chama modo interativo.
2. Se recebe `-h` ou `--help`, mostra ajuda.
3. Se a quantidade de argumentos combina com conversao ou calculo, chama modo direto.
4. Caso contrario, mostra uso e retorna erro.

## Como este arquivo foi projetado

`main.c` foi projetado como adaptador de interface.

Ele traduz entrada humana para estruturas da camada `app`.

Isso evita que o dominio precise saber o que e terminal.

Se no futuro o projeto ganhar interface grafica, a nova interface pode chamar `run_calculation` e `run_conversion` sem reescrever as regras.
