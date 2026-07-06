# include/domain/base.h

Este arquivo define o contrato publico para trabalhar com bases numericas.

Ele nao implementa a conversao. Ele apenas declara quais tipos e funcoes existem para que outros arquivos possam usar.

## Intencao do arquivo

`base.h` responde a tres perguntas:

- Quais bases numericas o projeto suporta?
- Quais erros podem acontecer ao interpretar ou formatar valores?
- Quais funcoes podem ser chamadas para parsear e formatar numeros?

## Includes

```c
#include <stdint.h>
#include <stddef.h>
```

`stdint.h` e usado porque as funcoes trabalham com `int64_t`.

`stddef.h` e usado porque `format_int64_in_base` recebe `size_t`, o tipo comum em C para tamanhos de buffer.

## Include guard

```c
#ifndef PROGRAMMER_CALC_DOMAIN_BASE_H
#define PROGRAMMER_CALC_DOMAIN_BASE_H
...
#endif
```

O include guard evita que o mesmo header seja incluido mais de uma vez durante a compilacao.

Sem isso, o compilador poderia encontrar definicoes repetidas.

## Enum NumberBase

```c
typedef enum {
    BASE_BINARY = 2,
    BASE_OCTAL = 8,
    BASE_DECIMAL = 10,
    BASE_HEXADECIMAL = 16
} NumberBase;
```

Esse enum representa as bases suportadas.

Uma decisao importante aqui e que os valores do enum sao iguais aos valores reais das bases:

- `BASE_BINARY` vale `2`.
- `BASE_OCTAL` vale `8`.
- `BASE_DECIMAL` vale `10`.
- `BASE_HEXADECIMAL` vale `16`.

Isso facilita chamar funcoes da biblioteca padrao, como `strtoll`, que recebe a base como inteiro.

## Enum ParseStatus

```c
typedef enum {
    PARSE_OK = 0,
    PARSE_INVALID_BASE,
    PARSE_INVALID_VALUE,
    PARSE_OUT_OF_RANGE,
    PARSE_OUTPUT_TOO_SMALL
} ParseStatus;
```

Esse enum padroniza erros relacionados a parse e formatacao.

Cada valor tem uma intencao:

- `PARSE_OK`: deu certo.
- `PARSE_INVALID_BASE`: a base digitada nao foi reconhecida.
- `PARSE_INVALID_VALUE`: o texto nao representa um numero valido naquela base.
- `PARSE_OUT_OF_RANGE`: o numero ultrapassou o limite de `int64_t`.
- `PARSE_OUTPUT_TOO_SMALL`: o buffer de saida nao tem espaco suficiente.

Usar enum deixa o codigo mais legivel do que retornar `-1`, `0`, `1` sem significado claro.

## Funcao parse_base

```c
ParseStatus parse_base(const char *text, NumberBase *base);
```

Recebe um texto, como `bin` ou `hex`, e tenta converter para `NumberBase`.

Ela recebe um ponteiro `NumberBase *base` porque precisa devolver o resultado para quem chamou.

Padrao usado:

- O retorno indica sucesso ou erro.
- O ponteiro de saida recebe o valor convertido.

Esse padrao e comum em C porque a linguagem nao tem retorno multiplo.

## Funcao parse_int64_in_base

```c
ParseStatus parse_int64_in_base(const char *text, NumberBase base, int64_t *value);
```

Converte um texto em numero inteiro de 64 bits com sinal.

Exemplos:

- Texto `1010` em base binaria vira `10`.
- Texto `FF` em base hexadecimal vira `255`.
- Texto `17` em base octal vira `15`.

Ela tambem valida se o valor realmente pertence a base informada.

## Funcao format_int64_in_base

```c
ParseStatus format_int64_in_base(int64_t value, NumberBase base, char *buffer, size_t buffer_size);
```

Faz o caminho inverso: pega um `int64_t` e escreve o texto em uma base.

O resultado e colocado em `buffer`.

`buffer_size` existe para evitar escrita fora do limite do array, que e uma preocupacao essencial em C.

## Funcao base_label

```c
const char *base_label(NumberBase base);
```

Devolve um texto amigavel para a base.

Exemplo:

- `BASE_BINARY` vira `binario`.
- `BASE_DECIMAL` vira `decimal`.

Ela e usada pela CLI para imprimir o resultado de forma clara.

## Como este arquivo foi pensado

Este header foi desenhado como uma API pequena e estavel para o dominio de bases numericas.

Ele esconde detalhes de implementacao. Quem usa esse arquivo nao precisa saber se a conversao usa `strtoll`, divisao sucessiva ou qualquer outro algoritmo.

Essa separacao e uma aplicacao simples de Clean Architecture: o contrato e publico, mas o detalhe fica isolado no `.c`.
