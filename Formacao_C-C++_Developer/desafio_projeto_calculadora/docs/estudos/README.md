# Estudos do Projeto

Esta pasta foi criada para estudar o projeto arquivo por arquivo.

Ordem sugerida de leitura:

1. [Contexto geral dos diretorios](contexto-geral.md)
2. [include/domain/base.h](include-domain-base-h.md)
3. [src/domain/base.c](src-domain-base-c.md)
4. [include/domain/calculator.h](include-domain-calculator-h.md)
5. [src/domain/calculator.c](src-domain-calculator-c.md)
6. [include/app/programmer_calculator.h](include-app-programmer-calculator-h.md)
7. [src/app/programmer_calculator.c](src-app-programmer-calculator-c.md)
8. [src/cli/main.c](src-cli-main-c.md)
9. [tests/test_calculator.c](tests-test-calculator-c.md)
10. [Makefile](makefile.md)

## Como estudar

Leia primeiro o contexto geral para entender por que o projeto separa contratos, regras de negocio, casos de uso e interface.

Depois, leia sempre o par `.h` e `.c` da mesma area:

- O `.h` mostra o contrato publico.
- O `.c` mostra como o contrato foi implementado.

Esse habito e importante em C porque a linguagem nao tem classes ou modulos como algumas linguagens modernas. A organizacao nasce da disciplina de separar arquivos, responsabilidades e dependencias.
