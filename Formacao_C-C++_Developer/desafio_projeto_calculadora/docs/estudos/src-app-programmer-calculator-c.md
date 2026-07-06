# src/app/programmer_calculator.c

Este arquivo implementa os casos de uso da calculadora.

Ele e a ponte entre a interface e o dominio.

## Papel na arquitetura

A camada `app` coordena o fluxo de uma tarefa completa.

Ela nao faz a matematica diretamente e nao implementa parse de base manualmente.

Em vez disso, ela chama o dominio na ordem correta.

## map_parse_status

```c
static AppStatus map_parse_status(ParseStatus status, AppStatus invalid_status)
```

Converte um `ParseStatus` do dominio em `AppStatus` da aplicacao.

Ela recebe tambem `invalid_status`, porque o mesmo erro de parse pode significar coisas diferentes dependendo do campo.

Exemplo:

- Se o primeiro valor falha, vira `APP_INVALID_LEFT_VALUE`.
- Se o segundo valor falha, vira `APP_INVALID_RIGHT_VALUE`.

Essa funcao evita duplicacao de `switch` dentro dos casos de uso.

## map_calc_status

```c
static AppStatus map_calc_status(CalcStatus status)
```

Converte erros da matematica para erros da aplicacao.

Exemplos:

- `CALC_DIVISION_BY_ZERO` vira `APP_DIVISION_BY_ZERO`.
- `CALC_OVERFLOW` vira `APP_OVERFLOW`.
- `CALC_INVALID_OPERATION` vira `APP_INVALID_OPERATION`.

## run_calculation

```c
AppStatus run_calculation(const CalculationRequest *request, char *output, size_t output_size)
```

Executa o fluxo completo de calculo.

### Passo 1: validar request

```c
if (request == NULL) {
    return APP_INVALID_LEFT_VALUE;
}
```

Protege contra ponteiro nulo.

### Passo 2: converter o primeiro valor

```c
parse_int64_in_base(request->left_text, request->input_base, &left)
```

O texto do primeiro valor vira `int64_t`.

Se falhar, a aplicacao retorna `APP_INVALID_LEFT_VALUE`.

### Passo 3: converter o segundo valor

```c
parse_int64_in_base(request->right_text, request->input_base, &right)
```

O segundo valor tambem usa a mesma base de entrada.

Se falhar, retorna `APP_INVALID_RIGHT_VALUE`.

### Passo 4: converter operador

```c
parse_operation(request->operation_text, &operation)
```

O operador textual vira enum `Operation`.

Isso evita que a funcao de calculo trabalhe com strings.

### Passo 5: calcular

```c
calculate_int64(left, right, operation, &result)
```

O dominio executa a matematica.

Se houver divisao por zero ou overflow, o erro e traduzido para `AppStatus`.

### Passo 6: formatar resultado

```c
format_int64_in_base(result, request->output_base, output, output_size)
```

O resultado numerico vira texto na base desejada.

## run_conversion

```c
AppStatus run_conversion(const ConversionRequest *request, char *output, size_t output_size)
```

Executa o fluxo completo de conversao.

Fluxo:

1. Valida a requisicao.
2. Converte `value_text` para `int64_t` usando `input_base`.
3. Formata o valor usando `output_base`.

Ela e parecida com `run_calculation`, mas sem operador e sem segundo valor.

Essa separacao foi uma decisao importante: conversao e calculo sao casos de uso diferentes.

## app_status_message

```c
const char *app_status_message(AppStatus status)
```

Transforma enum em texto.

Essa funcao centraliza mensagens para que a CLI nao precise ter um `switch` proprio.

## Como este arquivo foi projetado

O arquivo foi pensado como uma camada de orquestracao.

Ele nao deve conter detalhes de terminal, e tambem nao deve duplicar algoritmos do dominio.

Ele chama o dominio e traduz os resultados para uma linguagem mais adequada ao caso de uso.

Isso segue o principio de Clean Architecture: casos de uso coordenam entidades/regras, mas nao dependem da interface externa.
