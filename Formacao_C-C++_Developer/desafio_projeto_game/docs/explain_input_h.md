# Explicação do arquivo `include/input.h`

## Papel do arquivo

O arquivo `input.h` define a interface pública para entrada do teclado.

Ele protege o restante do projeto de detalhes técnicos do terminal, como códigos de escape e modo raw.

## Enum `Key`

```c
typedef enum {
    KEY_NONE,
    KEY_UP,
    KEY_DOWN,
    KEY_LEFT,
    KEY_RIGHT,
    KEY_SPACE,
    KEY_ENTER,
    KEY_CTRL_C
} Key;
```

Esse enum traduz teclas reais para nomes semânticos.

Em vez de `main.c` lidar com caracteres crus como `'\033'`, `' '` ou `3`, ele lida com:

- `KEY_UP`;
- `KEY_DOWN`;
- `KEY_LEFT`;
- `KEY_RIGHT`;
- `KEY_SPACE`;
- `KEY_ENTER`;
- `KEY_CTRL_C`.

Isso deixa o fluxo principal mais legível.

## Função `input_enable_raw_mode`

```c
int input_enable_raw_mode(void);
```

Configura o terminal para ler teclas sem esperar Enter.

Retorna:

- `1` em caso de sucesso;
- `0` em caso de falha.

## Função `input_disable_raw_mode`

```c
void input_disable_raw_mode(void);
```

Restaura a configuração original do terminal.

Essa função é importante porque um programa de terminal não deve deixar o terminal do usuário em estado alterado após encerrar.

## Função `input_read_key`

```c
Key input_read_key(void);
```

Lê uma tecla do teclado e retorna um valor do enum `Key`.

O resto do programa não precisa saber como cada tecla foi detectada. Ele apenas consome uma abstração limpa.

## Decisão arquitetural

`input.h` representa um adaptador de entrada. Ele transforma um detalhe externo do sistema operacional em uma interface simples para a aplicação.
