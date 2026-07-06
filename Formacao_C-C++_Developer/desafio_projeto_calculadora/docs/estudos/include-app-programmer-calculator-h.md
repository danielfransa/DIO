# include/app/programmer_calculator.h

Este header define o contrato da camada de aplicacao.

A camada de aplicacao representa os casos de uso do programa.

## Intencao do arquivo

Este arquivo responde:

- Como pedir um calculo completo?
- Como pedir uma conversao completa?
- Quais erros a aplicacao pode devolver?
- Como transformar um status em mensagem amigavel?

Ele importa o dominio:

```c
#include "domain/base.h"
#include "domain/calculator.h"
```

Isso mostra que a aplicacao depende das regras de dominio.

## Enum AppStatus

```c
typedef enum {
    APP_OK = 0,
    APP_INVALID_INPUT_BASE,
    APP_INVALID_OUTPUT_BASE,
    APP_INVALID_LEFT_VALUE,
    APP_INVALID_RIGHT_VALUE,
    APP_INVALID_OPERATION,
    APP_DIVISION_BY_ZERO,
    APP_OVERFLOW,
    APP_OUTPUT_TOO_SMALL
} AppStatus;
```

Esse enum representa erros no nivel do caso de uso.

Ele e diferente de `ParseStatus` e `CalcStatus`.

Por que?

Porque a aplicacao precisa falar em termos mais proximos da tarefa do usuario.

Exemplo:

- O dominio pode dizer `PARSE_INVALID_VALUE`.
- A aplicacao traduz para `APP_INVALID_LEFT_VALUE` ou `APP_INVALID_RIGHT_VALUE`.

Assim a mensagem final pode dizer qual valor esta errado.

## Struct CalculationRequest

```c
typedef struct {
    NumberBase input_base;
    NumberBase output_base;
    const char *left_text;
    const char *right_text;
    const char *operation_text;
} CalculationRequest;
```

Representa uma solicitacao de calculo.

Campos:

- `input_base`: base dos dois valores de entrada.
- `output_base`: base desejada para o resultado.
- `left_text`: primeiro valor ainda em texto.
- `right_text`: segundo valor ainda em texto.
- `operation_text`: operador ainda em texto.

Os valores sao texto porque a camada de aplicacao e responsavel por coordenar a conversao.

## Struct ConversionRequest

```c
typedef struct {
    NumberBase input_base;
    NumberBase output_base;
    const char *value_text;
} ConversionRequest;
```

Representa uma conversao simples de base.

Exemplo:

```text
bin 01010110 dec
```

Essa estrutura existe porque conversao nao e a mesma coisa que calculo.

Criar uma struct propria evita usar campos artificiais, como operacao vazia ou segundo valor falso.

## run_calculation

```c
AppStatus run_calculation(const CalculationRequest *request, char *output, size_t output_size);
```

Executa o caso de uso de calculo.

Ela recebe uma requisicao, escreve o resultado em `output` e retorna status.

## run_conversion

```c
AppStatus run_conversion(const ConversionRequest *request, char *output, size_t output_size);
```

Executa o caso de uso de conversao.

Ela converte um valor de uma base para outra sem executar operacao matematica.

## app_status_message

```c
const char *app_status_message(AppStatus status);
```

Transforma status em mensagem.

A CLI usa essa funcao para mostrar erros claros ao usuario.

## Como este arquivo foi pensado

Este header representa uma fronteira arquitetural.

Quem esta fora da aplicacao, como a CLI, nao precisa chamar varias funcoes do dominio manualmente.

Em vez disso, chama:

- `run_calculation`.
- `run_conversion`.

Isso reduz acoplamento e deixa a CLI mais simples.
