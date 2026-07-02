# Explicação do arquivo `Makefile`

## Papel do arquivo

O `Makefile` automatiza a compilação do projeto.

Sem ele, seria necessário digitar manualmente comandos longos de `gcc`. Com ele, basta usar:

```bash
make
make run
make clean
```

## Variáveis principais

```make
CC := gcc
```

Define o compilador C usado pelo projeto.

```make
CFLAGS := -std=c11 -Wall -Wextra -Wpedantic -Iinclude
```

Define as flags de compilação:

- `-std=c11`: usa o padrão C11.
- `-Wall`: ativa avisos comuns.
- `-Wextra`: ativa avisos adicionais.
- `-Wpedantic`: cobra mais conformidade com o padrão.
- `-Iinclude`: diz ao compilador onde procurar os headers.

```make
TARGET := jogo_da_velha
```

Nome do executável final.

```make
BUILD_DIR := build
```

Diretório onde ficam os arquivos objeto `.o`.

## Fontes e objetos

```make
SRC := $(wildcard src/*.c)
```

Busca todos os arquivos `.c` dentro de `src/`.

```make
OBJ := $(SRC:src/%.c=$(BUILD_DIR)/%.o)
```

Transforma cada arquivo fonte em um arquivo objeto correspondente.

Exemplo:

```text
src/main.c -> build/main.o
src/game.c -> build/game.o
src/ai.c   -> build/ai.o
```

## `.PHONY`

```make
.PHONY: all run clean
```

Indica que `all`, `run` e `clean` são comandos do Make, não arquivos reais.

## Alvo `all`

```make
all: $(TARGET)
```

É o alvo padrão. Quando o usuário roda `make`, esse alvo é executado.

## Linkagem do executável

```make
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@
```

Essa regra cria o executável final a partir dos arquivos objeto.

Variáveis automáticas:

- `$^`: todas as dependências da regra.
- `$@`: o alvo da regra.

## Compilação dos objetos

```make
$(BUILD_DIR)/%.o: src/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
```

Essa regra diz como transformar um `.c` em um `.o`.

Variáveis automáticas:

- `$<`: primeira dependência, ou seja, o arquivo `.c`.
- `$@`: alvo, ou seja, o arquivo `.o`.

O comando `mkdir -p` garante que a pasta `build/` exista antes de salvar o objeto.

## Alvo `run`

```make
run: $(TARGET)
	./$(TARGET)
```

Compila o projeto se necessário e executa o jogo.

## Alvo `clean`

```make
clean:
	rm -f $(OBJ) $(TARGET)
```

Remove arquivos gerados:

- objetos `.o`;
- executável `jogo_da_velha`.

Ele não remove `build/.gitkeep`, para manter a pasta `build/` versionada no Git.

## Decisão arquitetural

O `Makefile` separa código-fonte de artefatos de build. Isso mantém o projeto organizado e aproxima a estrutura de práticas comuns em projetos C profissionais.
