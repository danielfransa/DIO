# Calculadora para Programador

Calculadora em C para as quatro operacoes principais (`+`, `-`, `*`, `/`) usando valores em binario, octal, decimal e hexadecimal.

O projeto usa uma arquitetura simples inspirada em Clean Architecture:

- `domain`: regras puras de base numerica e calculo.
- `app`: caso de uso que coordena entrada, operacao e saida.
- `cli`: interface de terminal.

## Compilar

```bash
make
```

O binario Linux sera gerado em:

```text
bin/programmer_calc
```

## Executar

Modo interativo:

```bash
make run
```

No modo interativo voce pode informar a expressao completa no primeiro prompt:

```text
dec 10 + 1 dec
```

Ou informar apenas a base, por exemplo `dec`, e responder os campos seguintes.

Modo direto:

```bash
./bin/programmer_calc <base-entrada> <valor-a> <operacao> <valor-b> [base-saida]
```

Exemplos:

```bash
./bin/programmer_calc bin 1010 + 11 dec
./bin/programmer_calc hex FF / F bin
./bin/programmer_calc oct 17 "*" 2 hex
```

Bases aceitas: `bin`, `binary`, `oct`, `octal`, `dec`, `decimal`, `hex`, `hexadecimal`.

## Testes

```bash
make test
```

## Windows

Com MinGW instalado:

```bash
make windows
```

O executavel sera gerado em:

```text
bin/programmer_calc.exe
```

## Documentacao

A pasta `docs/` descreve a arquitetura, as decisoes tecnicas, principios de Clean Code/Clean Architecture e instrucoes de build.
