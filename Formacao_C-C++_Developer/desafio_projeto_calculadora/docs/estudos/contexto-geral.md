# Contexto Geral dos Diretorios

Este projeto e uma calculadora para programador escrita em C. Ela faz dois tipos de tarefa:

- Calculos com as quatro operacoes principais: soma, subtracao, multiplicacao e divisao.
- Conversoes entre bases: binario, octal, decimal e hexadecimal.

A ideia arquitetural principal e simples: separar o que e regra de negocio do que e entrada e saida de terminal.

## Visao dos diretorios

```text
include/
  app/
  domain/
src/
  app/
  cli/
  domain/
tests/
docs/
Makefile
README.md
```

## Diretorio include

O diretorio `include/` guarda arquivos `.h`, tambem chamados de headers.

Em C, um header funciona como um contrato. Ele diz:

- Quais tipos existem.
- Quais funcoes podem ser chamadas por outros arquivos.
- Quais valores de enum fazem parte da API.

Ele nao deve concentrar regras complexas. A regra fica nos arquivos `.c`.

Neste projeto, `include/` e dividido assim:

```text
include/domain/
include/app/
```

### include/domain

Guarda os contratos da camada de dominio.

A camada de dominio e a parte mais importante da aplicacao, porque contem as regras essenciais:

- O que e uma base numerica suportada.
- Como representar uma operacao.
- Quais erros podem acontecer durante parse, formatacao e calculo.
- Quais funcoes puras fazem conversao e calculo.

Essa camada nao conhece terminal, `printf`, argumentos de linha de comando ou `make`.

### include/app

Guarda os contratos da camada de aplicacao.

A camada de aplicacao coordena uma tarefa completa. Por exemplo:

- Receber uma requisicao de calculo.
- Converter textos para numeros.
- Executar uma operacao.
- Formatar o resultado na base desejada.

Ela usa o dominio, mas ainda nao depende da CLI.

## Diretorio src

O diretorio `src/` guarda arquivos `.c`, ou seja, as implementacoes.

Neste projeto, `src/` e dividido assim:

```text
src/domain/
src/app/
src/cli/
```

### src/domain

Implementa as regras puras:

- `base.c`: parse de bases, parse de numeros e formatacao de saida.
- `calculator.c`: parse de operacoes e execucao da matematica.

Esses arquivos foram pensados para serem testaveis sem terminal.

### src/app

Implementa os casos de uso:

- `run_calculation`: calcula uma expressao com dois valores e uma operacao.
- `run_conversion`: converte um valor de uma base para outra.

Essa camada e a ponte entre a regra pura e a interface.

### src/cli

Implementa a interface de linha de comando.

Ela e responsavel por:

- Ler argumentos.
- Ler entrada interativa.
- Mostrar mensagens de erro.
- Mostrar resultados.

Ela nao deveria conter regra matematica. Quando precisa calcular, chama a camada `app`.

## Diretorio tests

Guarda testes automatizados.

O teste chama a camada `app`, nao a CLI. Isso e proposital:

- Testar a CLI exigiria simular entrada de terminal.
- Testar a camada `app` e mais direto e cobre a regra principal.
- A CLI fica fina, com pouca regra, reduzindo risco.

## Makefile

O `Makefile` automatiza tarefas comuns:

- Compilar o programa.
- Executar o programa.
- Compilar e rodar testes.
- Gerar `.exe` com MinGW.
- Limpar artefatos de build.

## Fluxo de dependencia

O projeto foi desenhado para que as dependencias apontem para dentro:

```text
src/cli -> src/app -> src/domain
```

Isso significa:

- A CLI conhece a aplicacao.
- A aplicacao conhece o dominio.
- O dominio nao conhece ninguem.

Esse fluxo ajuda a preservar Clean Architecture em um projeto C simples.

## Por que separar assim?

Separar em camadas evita que o projeto vire um unico arquivo grande cheio de `printf`, `scanf`, conversao e matematica misturados.

Com a separacao:

- Fica mais facil testar.
- Fica mais facil trocar a interface no futuro.
- Fica mais facil localizar erros.
- Fica mais facil explicar cada responsabilidade.
- Fica mais proximo de um projeto C organizado profissionalmente.

## Exemplo de fluxo real

Entrada:

```text
bin 01010110 dec
```

Fluxo:

1. `src/cli/main.c` quebra a linha em tokens.
2. A CLI identifica que sao 3 tokens, entao e conversao.
3. A CLI cria um `ConversionRequest`.
4. `src/app/programmer_calculator.c` recebe a requisicao.
5. A camada `app` chama `parse_int64_in_base`.
6. O valor binario vira `int64_t`.
7. A camada `app` chama `format_int64_in_base`.
8. O resultado e formatado em decimal.
9. A CLI imprime `Resultado (decimal): 86`.
