# Jogo da Velha em C

Jogo da velha para terminal em que o usuario joga como `X` contra o computador como `O`.

## Como compilar

```bash
make
```

## Como jogar

```bash
make run
```

- Use as setas para escolher a casa.
- Pressione espaco para marcar `X`.
- O computador joga automaticamente como `O`.
- A dificuldade segue um ciclo de 10 partidas: duas normais, uma aleatoria, repetindo ate a decima partida facil.
- Ao final da partida, pressione Enter para jogar novamente.
- Pressione Ctrl+C para sair.

O placar vale apenas para a sessao aberta.

## Material de estudo

A explicacao detalhada da arquitetura, dos arquivos e das decisoes do projeto esta em:

[docs/aula-projeto-jogo-da-velha.md](docs/aula-projeto-jogo-da-velha.md)

As explicacoes individuais de cada arquivo do projeto estao em:

[docs/explain_index.md](docs/explain_index.md)
