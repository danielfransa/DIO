# Makefile

O `Makefile` automatiza compilacao, testes e limpeza do projeto.

Ele evita que o usuario precise digitar comandos longos de compilacao manualmente.

## Variaveis principais

```make
CC ?= gcc
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic -Iinclude
LDFLAGS ?=
```

`CC` define o compilador. O `?=` significa: use `gcc` se o usuario nao informar outro compilador.

`CFLAGS` define flags de compilacao:

- `-std=c11`: usa padrao C11.
- `-Wall`: ativa varios avisos.
- `-Wextra`: ativa avisos extras.
- `-Wpedantic`: cobra conformidade mais rigorosa.
- `-Iinclude`: informa onde estao os headers.

`LDFLAGS` existe para flags de linkagem, caso sejam necessarias no futuro.

## Diretorios e binarios

```make
BUILD_DIR := build
BIN_DIR := bin
TARGET := $(BIN_DIR)/programmer_calc
TEST_TARGET := $(BIN_DIR)/test_calculator
```

`bin/` guarda os executaveis gerados.

`build/` foi reservado para artefatos de build.

## SRC

```make
SRC := \
    src/domain/base.c \
    src/domain/calculator.c \
    src/app/programmer_calculator.c \
    src/cli/main.c
```

Lista todos os arquivos necessarios para criar o programa final.

Inclui a CLI porque o binario principal precisa de `main`.

## LIB_SRC

```make
LIB_SRC := \
    src/domain/base.c \
    src/domain/calculator.c \
    src/app/programmer_calculator.c
```

Lista os arquivos da regra de negocio e aplicacao.

Nao inclui `src/cli/main.c`, porque os testes possuem o proprio `main`.

Essa separacao evita erro de "main duplicado".

## TEST_SRC

```make
TEST_SRC := tests/test_calculator.c
```

Define o arquivo de teste.

## Alvo all

```make
all: $(TARGET)
```

E o alvo padrao.

Quando o usuario roda:

```bash
make
```

O Make executa `all`, que gera o binario principal.

## Alvo dirs

```make
dirs:
    mkdir -p $(BUILD_DIR) $(BIN_DIR)
```

Garante que os diretorios de saida existam.

`mkdir -p` nao falha se o diretorio ja existir.

## Alvo do programa principal

```make
$(TARGET): $(SRC) | dirs
    $(CC) $(CFLAGS) $(SRC) $(LDFLAGS) -o $@
```

Compila todos os arquivos de `SRC` e gera `bin/programmer_calc`.

`$@` representa o alvo atual, ou seja, `bin/programmer_calc`.

## Alvo run

```make
run: $(TARGET)
    ./$(TARGET)
```

Compila o programa se necessario e depois executa.

## Alvo de teste

```make
$(TEST_TARGET): $(LIB_SRC) $(TEST_SRC) | dirs
    $(CC) $(CFLAGS) $(LIB_SRC) $(TEST_SRC) $(LDFLAGS) -o $@
```

Compila os arquivos da aplicacao com o arquivo de teste.

## Alvo test

```make
test: $(TEST_TARGET)
    ./$(TEST_TARGET)
```

Compila e executa os testes.

## Alvo windows

```make
windows:
    mkdir -p $(BIN_DIR)
    x86_64-w64-mingw32-gcc $(CFLAGS) $(SRC) $(LDFLAGS) -o $(BIN_DIR)/programmer_calc.exe
```

Gera um `.exe` usando MinGW.

Esse alvo depende de `x86_64-w64-mingw32-gcc` instalado no sistema.

## Alvo clean

```make
clean:
    rm -rf $(BUILD_DIR) $(BIN_DIR)
```

Remove arquivos gerados.

## Como este arquivo foi projetado

O `Makefile` foi pensado para ser simples e didatico.

Ele mostra uma estrutura comum em projetos C:

- Variaveis para compilador e flags.
- Lista separada de fontes do programa e dos testes.
- Alvos para build, run, test, windows e clean.

Essa organizacao facilita evoluir o projeto sem precisar reescrever comandos de compilacao toda vez.
