# src/domain/calculator.c

Este arquivo implementa a matematica da calculadora.

Ele recebe numeros ja convertidos para `int64_t` e executa soma, subtracao, multiplicacao ou divisao.

## Papel na arquitetura

`calculator.c` pertence ao dominio.

Ele nao sabe se os numeros vieram de binario, decimal ou hexadecimal. Quando esta funcao e chamada, a conversao ja aconteceu.

Essa decisao simplifica muito a regra:

```text
base numerica -> base.c
matematica -> calculator.c
```

## parse_operation

```c
CalcStatus parse_operation(const char *text, Operation *operation)
```

Transforma o operador digitado pelo usuario em um enum `Operation`.

### Validacao inicial

```c
if (text == NULL || operation == NULL) {
    return CALC_INVALID_OPERATION;
}
```

A funcao protege contra ponteiros nulos.

Em C, acessar ponteiro nulo causa comportamento indefinido. Por isso a validacao vem antes de qualquer uso.

### Operadores aceitos

A funcao aceita:

- `+` para soma.
- `-` para subtracao.
- `*`, `x` ou `X` para multiplicacao.
- `/` para divisao.

Aceitar `x` e `X` ajuda no terminal, porque `*` pode ter significado especial no shell se nao estiver entre aspas.

## calculate_int64

```c
CalcStatus calculate_int64(int64_t left, int64_t right, Operation operation, int64_t *result)
```

Executa a operacao.

Parametros:

- `left`: valor da esquerda.
- `right`: valor da direita.
- `operation`: operacao ja parseada.
- `result`: ponteiro onde o resultado sera escrito.

### Por que retornar status?

Nem toda conta produz resultado valido.

Exemplos:

- `10 / 0` nao pode ser calculado.
- `INT64_MAX + 1` ultrapassa o limite.
- Uma operacao desconhecida nao deve ser executada.

Por isso a funcao retorna `CalcStatus`.

## Tratamento de overflow

Para GCC e Clang, o codigo usa builtins:

```c
__builtin_add_overflow
__builtin_sub_overflow
__builtin_mul_overflow
```

Essas funcoes detectam overflow de forma segura.

Isso e importante porque overflow de inteiro com sinal em C pode causar comportamento indefinido.

## Fallback sem builtins

O codigo tambem possui blocos `#else` para compiladores sem esses builtins.

Isso melhora a portabilidade.

O projeto tenta ser simples para Linux e Windows, entao nao depende exclusivamente de um recurso de compilador.

## Divisao

A divisao tem duas validacoes especiais:

```c
if (right == 0) {
    return CALC_DIVISION_BY_ZERO;
}
```

Evita divisao por zero.

```c
if (left == INT64_MIN && right == -1) {
    return CALC_OVERFLOW;
}
```

Evita overflow no caso extremo de `INT64_MIN / -1`.

## operation_label

```c
const char *operation_label(Operation operation)
```

Retorna o simbolo textual da operacao.

Mesmo sendo simples, ela evita que outras partes do sistema precisem conhecer os detalhes do enum.

## Como este arquivo foi projetado

O arquivo foi pensado para ter funcoes puras e previsiveis:

- Mesma entrada gera mesma saida.
- Nenhuma funcao le teclado.
- Nenhuma funcao imprime na tela.
- Erros sao retornados por enum.

Isso facilita testes e preserva a camada de dominio.
