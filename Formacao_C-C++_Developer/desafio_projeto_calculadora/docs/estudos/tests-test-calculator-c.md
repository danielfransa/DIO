# tests/test_calculator.c

Este arquivo contem testes automatizados simples para a calculadora.

Ele nao usa framework externo. Isso foi feito para manter o projeto facil de compilar em qualquer ambiente com GCC ou Clang.

## Papel no projeto

Os testes verificam a camada `app`.

Isso e uma escolha importante:

- A camada `app` cobre conversao, calculo e formatacao.
- A CLI fica fora dos testes unitarios para evitar depender de entrada interativa.
- O teste fica simples e rapido.

## assert_status

```c
static void assert_status(AppStatus actual, AppStatus expected, const char *case_name)
```

Compara o status recebido com o esperado.

Se forem diferentes:

1. Imprime uma mensagem de erro.
2. Encerra o programa com `exit(EXIT_FAILURE)`.

Isso faz o comando `make test` falhar quando algum comportamento quebra.

## assert_text

```c
static void assert_text(const char *actual, const char *expected, const char *case_name)
```

Compara duas strings.

E usada para verificar o resultado textual da calculadora.

Exemplo:

```text
esperado: 86
recebido: 86
```

## test_sum_binary_to_decimal

Testa soma em base binaria com saida decimal.

Entrada conceitual:

```text
bin 1010 + 11 dec
```

Resultado esperado:

```text
13
```

Porque `1010` em binario e `10`, e `11` em binario e `3`.

## test_subtract_decimal_to_hex

Testa subtracao decimal com saida hexadecimal.

```text
255 - 16 = 239
```

`239` em hexadecimal e `EF`.

## test_multiply_octal_to_decimal

Testa multiplicacao com entrada octal.

```text
17 octal = 15 decimal
15 * 2 = 30
```

Resultado esperado:

```text
30
```

## test_divide_hex_to_binary

Testa divisao com entrada hexadecimal e saida binaria.

```text
FF hex = 255
F hex = 15
255 / 15 = 17
17 decimal = 10001 binario
```

## test_convert_binary_to_decimal

Testa conversao sem operacao.

```text
bin 01010110 dec
```

Resultado esperado:

```text
86
```

Esse teste foi criado para garantir que conversao direta continue funcionando.

## test_invalid_binary_value

Testa erro de valor invalido.

Entrada:

```text
102 em base binaria
```

O digito `2` nao existe em binario.

O status esperado e `APP_INVALID_LEFT_VALUE`.

## test_division_by_zero

Testa a protecao contra divisao por zero.

Entrada:

```text
10 / 0
```

Status esperado:

```text
APP_DIVISION_BY_ZERO
```

## main dos testes

```c
int main(void)
```

Executa todos os testes em sequencia.

Se algum teste falhar, o programa encerra antes da mensagem final.

Se todos passam, imprime:

```text
Todos os testes passaram.
```

## Como este arquivo foi projetado

O teste foi pensado como uma verificacao simples de regressao.

Quando uma nova funcionalidade e adicionada, um teste deve ser adicionado para garantir que ela continue funcionando no futuro.

Mesmo sem framework, o arquivo ja ensina tres ideias importantes:

- Teste deve ter entrada clara.
- Teste deve ter resultado esperado claro.
- Teste deve falhar de forma visivel.
