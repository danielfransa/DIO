# Arquitetura

O projeto foi organizado em camadas para manter a regra de negocio independente da interface.

## Camadas

### Domain

Arquivos:

- `include/domain/base.h`
- `include/domain/calculator.h`
- `src/domain/base.c`
- `src/domain/calculator.c`

Responsabilidades:

- Definir as bases numericas suportadas.
- Converter texto para inteiro de 64 bits com sinal.
- Formatar resultados em binario, octal, decimal ou hexadecimal.
- Executar as quatro operacoes principais.

Esta camada nao conhece terminal, arquivos, argumentos de linha de comando ou sistema operacional.

### App

Arquivos:

- `include/app/programmer_calculator.h`
- `src/app/programmer_calculator.c`

Responsabilidades:

- Receber uma requisicao de calculo.
- Coordenar parse dos valores, operacao e formatacao de saida.
- Traduzir erros tecnicos para mensagens de aplicacao.

### CLI

Arquivo:

- `src/cli/main.c`

Responsabilidades:

- Ler argumentos ou dados digitados no terminal.
- Mostrar mensagens de erro e resultado.
- Chamar o caso de uso da camada `app`.

## Fluxo

1. A CLI coleta base, valores, operacao e base de saida.
2. A camada `app` valida e orquestra o calculo.
3. A camada `domain` converte, calcula e formata o resultado.
4. A CLI imprime o resultado.

## Dependencias

As dependencias apontam para dentro:

```text
cli -> app -> domain
```

O `domain` nao depende de nenhuma camada do projeto.
