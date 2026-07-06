# Build e Execucao

## Requisitos

- GCC ou Clang com suporte a C11.
- `make`.
- Opcional para Windows: MinGW com `x86_64-w64-mingw32-gcc`.

## Linux

Compilar:

```bash
make
```

Executar em modo interativo:

```bash
make run
```

Executar em modo direto:

```bash
./bin/programmer_calc dec 10 + 5 bin
```

## Windows

Em uma maquina Linux com MinGW instalado:

```bash
make windows
```

O arquivo gerado sera:

```text
bin/programmer_calc.exe
```

Tambem e possivel compilar manualmente no Windows com GCC/MinGW apontando para os mesmos arquivos `src`.

## Testes

```bash
make test
```

Os testes cobrem:

- Soma binaria.
- Subtracao decimal com saida hexadecimal.
- Multiplicacao octal.
- Divisao hexadecimal com saida binaria.
- Valor invalido para a base.
- Divisao por zero.
