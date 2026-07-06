# src/domain/base.c

Este arquivo implementa as funcoes declaradas em `include/domain/base.h`.

Ele e responsavel por reconhecer bases, converter textos em numeros e formatar numeros em bases diferentes.

## Papel na arquitetura

`base.c` pertence ao dominio.

Isso significa que ele contem regra essencial do problema, mas nao contem interface de usuario.

Ele nao usa:

- `printf` para conversar com usuario.
- Argumentos de linha de comando.
- Estado global da aplicacao.

Ele recebe dados, processa e devolve status.

## Includes

```c
#include "domain/base.h"
```

Inclui o proprio contrato que o arquivo implementa.

Os includes da biblioteca padrao aparecem porque a implementacao precisa de recursos especificos:

- `ctype.h`: usar `tolower`.
- `errno.h`: detectar overflow no `strtoll`.
- `inttypes.h`: formatar `int64_t` com `PRId64`.
- `stdio.h`: usar `snprintf`.
- `stdlib.h`: usar `strtoll`.
- `string.h`: utilitarios de string.

## equals_ignore_case

```c
static int equals_ignore_case(const char *left, const char *right)
```

Compara duas strings ignorando maiusculas e minusculas.

Ela e `static`, entao so pode ser usada dentro de `base.c`.

Isso e importante porque ela e um detalhe interno. Nenhum outro arquivo precisa conhece-la.

### Como funciona

A funcao percorre as duas strings ao mesmo tempo.

Em cada caractere:

1. Converte os dois caracteres para minusculo com `tolower`.
2. Compara.
3. Se forem diferentes, retorna `0`.
4. Se chegar ao fim das duas strings juntas, retorna `1`.

O cast para `unsigned char` antes de `tolower` e uma boa pratica em C, porque `tolower` espera valores representaveis como `unsigned char` ou `EOF`.

## parse_base

```c
ParseStatus parse_base(const char *text, NumberBase *base)
```

Transforma texto em uma base numerica conhecida.

Exemplos aceitos:

- `bin`, `binary`, `binario`.
- `oct`, `octal`.
- `dec`, `decimal`.
- `hex`, `hexadecimal`.

### Decisao de projeto

A funcao aceita sinonimos para melhorar a experiencia de uso.

Ela nao imprime erro. Apenas retorna `PARSE_INVALID_BASE`. Isso deixa a funcao reutilizavel em CLI, testes ou outra interface futura.

### Fluxo

1. Valida ponteiros nulos.
2. Compara o texto com sinonimos conhecidos.
3. Preenche `*base`.
4. Retorna `PARSE_OK`.
5. Se nada bater, retorna `PARSE_INVALID_BASE`.

## parse_int64_in_base

```c
ParseStatus parse_int64_in_base(const char *text, NumberBase base, int64_t *value)
```

Converte uma string para `int64_t`, respeitando a base informada.

### Exemplo

```text
text = "01010110"
base = BASE_BINARY
resultado = 86
```

### Uso de strtoll

A funcao usa:

```c
parsed = strtoll(text, &end, (int)base);
```

`strtoll` recebe:

- O texto de entrada.
- Um ponteiro para marcar onde a leitura parou.
- A base numerica.

### Validacao completa

A funcao verifica:

- Se `text` ou `value` sao nulos.
- Se nenhum caractere foi convertido.
- Se sobraram caracteres invalidos no fim.
- Se ocorreu `ERANGE`, indicando valor fora do intervalo.

Essa validacao evita aceitar entradas parcialmente validas.

Por exemplo, em base binaria:

```text
102
```

O `2` e invalido. A funcao retorna `PARSE_INVALID_VALUE`.

## format_unsigned

```c
static ParseStatus format_unsigned(uint64_t value, NumberBase base, char *buffer, size_t buffer_size)
```

Formata um numero sem sinal em uma base.

Ela tambem e `static`, porque e uma funcao auxiliar interna.

### Por que existe?

Formatar decimal pode ser feito com `snprintf`, mas binario, octal e hexadecimal foram implementados manualmente para manter controle do formato.

### Algoritmo

O algoritmo usa divisoes sucessivas.

Exemplo com `86` em binario:

1. `86 % 2 = 0`
2. `43 % 2 = 1`
3. `21 % 2 = 1`
4. `10 % 2 = 0`
5. `5 % 2 = 1`
6. `2 % 2 = 0`
7. `1 % 2 = 1`

Os restos aparecem de tras para frente. Por isso a funcao guarda em `reversed` e depois inverte para o `buffer`.

### Buffer

A funcao sempre verifica se existe espaco suficiente para o texto e para o caractere final `\0`.

Esse cuidado e essencial em C para evitar estouro de buffer.

## format_int64_in_base

```c
ParseStatus format_int64_in_base(int64_t value, NumberBase base, char *buffer, size_t buffer_size)
```

Formata um numero com sinal em uma base.

### Decimal

Para decimal, usa:

```c
snprintf(buffer, buffer_size, "%" PRId64, value);
```

`PRId64` e usado porque a forma correta de imprimir `int64_t` pode variar entre plataformas.

### Bases nao decimais

Para binario, octal e hexadecimal, a funcao chama `format_unsigned`.

Se o numero for negativo:

1. Escreve `-` no inicio.
2. Calcula a magnitude positiva.
3. Formata a magnitude depois do sinal.

### Caso especial de INT64_MIN

O calculo:

```c
magnitude = (uint64_t)(-(value + 1)) + 1;
```

evita tentar fazer `-value` diretamente quando `value` e o menor `int64_t` possivel.

Em complemento de dois, `INT64_MIN` nao tem equivalente positivo dentro de `int64_t`.

## base_label

```c
const char *base_label(NumberBase base)
```

Converte o enum da base para texto de apresentacao.

A CLI usa essa funcao para imprimir:

```text
Resultado (decimal): 86
```

## Como este arquivo foi projetado

O arquivo foi pensado para ser:

- Independente da interface.
- Pequeno o bastante para ser testado.
- Explicito nos erros.
- Seguro com buffers.
- Portavel entre Linux e Windows.

Ele tambem segue o principio de responsabilidade unica: sua responsabilidade e lidar com bases numericas, nao com calculo nem com terminal.
