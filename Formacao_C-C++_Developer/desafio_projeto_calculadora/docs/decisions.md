# Decisoes Tecnicas

## Linguagem C11

O projeto usa C11 por ser portavel, simples de compilar em Linux e compativel com toolchains comuns para Windows, como MinGW.

## Inteiros de 64 bits com sinal

Os calculos usam `int64_t`. Essa escolha permite trabalhar com numeros negativos e define um limite claro para overflow.

## Bases suportadas

Foram implementadas quatro bases:

- Binario: base 2.
- Octal: base 8.
- Decimal: base 10.
- Hexadecimal: base 16.

O termo "octagonal" do enunciado foi interpretado como "octal", que e a base numerica usada em programacao.

## Interface de terminal

A interface e uma CLI simples, com dois modos:

- Modo interativo, quando o programa e executado sem argumentos.
- Modo direto, quando os parametros sao informados na linha de comando.

Essa escolha mantem o projeto facil de testar, compilar e executar em Linux e Windows.

## Build

O `Makefile` oferece:

- `make`: compila o binario Linux.
- `make test`: compila e executa testes.
- `make windows`: compila `.exe` usando `x86_64-w64-mingw32-gcc`.

## Tratamento de erros

O projeto diferencia:

- Base invalida.
- Valor invalido para a base.
- Operacao invalida.
- Divisao por zero.
- Overflow.
- Buffer de saida insuficiente.

Essa separacao ajuda a manter mensagens claras e facilita testes.
