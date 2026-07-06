# include/domain/calculator.h

Este header define o contrato da parte matematica da calculadora.

Ele declara as operacoes suportadas, os erros possiveis e as funcoes de calculo.

## Intencao do arquivo

`calculator.h` existe para separar a matematica da conversao de bases.

Bases numericas ficam em `base.h`.

Operacoes matematicas ficam em `calculator.h`.

Essa separacao evita misturar conceitos diferentes.

## Include

```c
#include <stdint.h>
```

O arquivo usa `int64_t` na assinatura de `calculate_int64`, por isso precisa de `stdint.h`.

## Enum Operation

```c
typedef enum {
    OP_ADD,
    OP_SUBTRACT,
    OP_MULTIPLY,
    OP_DIVIDE
} Operation;
```

Representa as quatro operacoes principais.

Usar enum e melhor do que espalhar caracteres como `+` e `*` pelo codigo inteiro.

O parse de texto para enum acontece uma vez. Depois disso, o dominio trabalha com um tipo forte.

## Enum CalcStatus

```c
typedef enum {
    CALC_OK = 0,
    CALC_INVALID_OPERATION,
    CALC_DIVISION_BY_ZERO,
    CALC_OVERFLOW
} CalcStatus;
```

Representa o resultado de uma tentativa de calculo.

Erros previstos:

- Operacao invalida.
- Divisao por zero.
- Overflow.

Overflow e importante porque o projeto usa `int64_t`, que tem limite.

## parse_operation

```c
CalcStatus parse_operation(const char *text, Operation *operation);
```

Converte texto em `Operation`.

Exemplos:

- `+` vira `OP_ADD`.
- `-` vira `OP_SUBTRACT`.
- `*`, `x` ou `X` viram `OP_MULTIPLY`.
- `/` vira `OP_DIVIDE`.

## calculate_int64

```c
CalcStatus calculate_int64(int64_t left, int64_t right, Operation operation, int64_t *result);
```

Executa uma operacao entre dois valores `int64_t`.

Assim como outras funcoes do projeto, ela retorna status e escreve o resultado em um ponteiro.

Esse padrao permite representar tanto sucesso quanto erro sem perder o valor calculado.

## operation_label

```c
const char *operation_label(Operation operation);
```

Converte uma operacao para texto.

Embora seja simples, essa funcao centraliza a traducao entre enum e simbolo.

## Como este arquivo foi pensado

O header define uma API pequena para calculo.

Ele nao sabe:

- Como o usuario digitou os dados.
- Qual base numerica foi usada.
- Como o resultado sera exibido.

Ele sabe apenas que existem dois numeros, uma operacao e um resultado possivel.
