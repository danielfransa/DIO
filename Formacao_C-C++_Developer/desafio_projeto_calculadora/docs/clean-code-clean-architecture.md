# Clean Code e Clean Architecture

## Principios de Clean Code

### Nomes claros

Funcoes como `parse_int64_in_base`, `calculate_int64` e `format_int64_in_base` descrevem exatamente o que fazem.

### Funcoes pequenas

Cada funcao tem uma responsabilidade principal:

- Parse de base.
- Parse de valor.
- Calculo.
- Formatacao.
- Execucao do caso de uso.
- Entrada e saida da CLI.

### Erros explicitos

O codigo usa enums de status em vez de retornar valores magicos. Isso evita ambiguidades e deixa o fluxo de erro mais legivel.

### Baixo acoplamento

A regra de negocio nao imprime no terminal e nao le argumentos de linha de comando. Isso facilita testar e trocar a interface no futuro.

### Testabilidade

Os testes chamam a camada `app` diretamente, sem depender de entrada interativa.

## Principios de Clean Architecture

### Regra de dependencia

As camadas externas dependem das internas:

```text
cli -> app -> domain
```

O dominio nao conhece a CLI. Isso preserva a independencia das regras de negocio.

### Entidades e regras de dominio

As operacoes matematicas e as bases numericas ficam em `domain`, porque representam o comportamento central da aplicacao.

### Casos de uso

`run_calculation` representa o caso de uso principal: receber uma requisicao de calculo e devolver uma resposta formatada.

### Adaptadores de interface

`src/cli/main.c` adapta entrada de usuario para o formato esperado pelo caso de uso.

## Limites atuais

- O projeto trabalha com `int64_t`, nao com inteiros arbitrariamente grandes.
- A divisao e inteira, como costuma ser esperado em calculadoras para programador.
- A saida representa numeros negativos com sinal `-`, em vez de complemento de dois.
