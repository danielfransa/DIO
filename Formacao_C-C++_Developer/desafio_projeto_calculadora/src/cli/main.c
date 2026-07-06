#include "app/programmer_calculator.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_SIZE 128
#define OUTPUT_SIZE 128
#define DIRECT_TOKENS 5

static void print_usage(const char *program_name)
{
    printf("Uso direto:\n");
    printf("  %s <base-entrada> <valor> <base-saida>\n", program_name);
    printf("  %s <base-entrada> <valor-a> <operacao> <valor-b> [base-saida]\n\n", program_name);
    printf("Bases: bin, oct, dec, hex\n");
    printf("Operacoes: +, -, '*', /\n\n");
    printf("Exemplos:\n");
    printf("  %s bin 01010110 dec\n", program_name);
    printf("  %s bin 1010 + 11 dec\n", program_name);
    printf("  %s hex FF / F bin\n", program_name);
}

static int read_line(const char *prompt, char *buffer, size_t size)
{
    size_t length = 0;

    printf("%s", prompt);
    if (fgets(buffer, (int)size, stdin) == NULL) {
        return 0;
    }

    length = strlen(buffer);
    if (length > 0 && buffer[length - 1] == '\n') {
        buffer[length - 1] = '\0';
    }

    return 1;
}

static int execute_request(const CalculationRequest *request)
{
    char output[OUTPUT_SIZE];
    AppStatus status = run_calculation(request, output, sizeof(output));

    if (status != APP_OK) {
        fprintf(stderr, "Erro: %s.\n", app_status_message(status));
        return EXIT_FAILURE;
    }

    printf("Resultado (%s): %s\n", base_label(request->output_base), output);
    return EXIT_SUCCESS;
}

static int execute_conversion(const ConversionRequest *request)
{
    char output[OUTPUT_SIZE];
    AppStatus status = run_conversion(request, output, sizeof(output));

    if (status != APP_OK) {
        fprintf(stderr, "Erro: %s.\n", app_status_message(status));
        return EXIT_FAILURE;
    }

    printf("Resultado (%s): %s\n", base_label(request->output_base), output);
    return EXIT_SUCCESS;
}

static size_t split_tokens(char *line, char **tokens, size_t max_tokens)
{
    char *token = NULL;
    size_t count = 0;

    token = strtok(line, " \t");
    while (token != NULL && count < max_tokens) {
        tokens[count++] = token;
        token = strtok(NULL, " \t");
    }

    if (token != NULL) {
        return max_tokens + 1;
    }

    return count;
}

static int try_parse_inline_calculation(char **tokens, size_t count, CalculationRequest *request)
{
    if (count != 4 && count != 5) {
        return 0;
    }

    if (parse_base(tokens[0], &request->input_base) != PARSE_OK) {
        return 0;
    }

    if (count == 5) {
        if (parse_base(tokens[4], &request->output_base) != PARSE_OK) {
            return 0;
        }
    } else {
        request->output_base = request->input_base;
    }

    request->left_text = tokens[1];
    request->operation_text = tokens[2];
    request->right_text = tokens[3];

    return 1;
}

static int try_parse_inline_conversion(char **tokens, size_t count, ConversionRequest *request)
{
    if (count != 3) {
        return 0;
    }

    if (parse_base(tokens[0], &request->input_base) != PARSE_OK ||
        parse_base(tokens[2], &request->output_base) != PARSE_OK) {
        return 0;
    }

    request->value_text = tokens[1];
    return 1;
}

static int run_direct_mode(int argc, char **argv)
{
    NumberBase input_base = BASE_DECIMAL;
    NumberBase output_base = BASE_DECIMAL;
    CalculationRequest request;
    ConversionRequest conversion_request;

    if (parse_base(argv[1], &input_base) != PARSE_OK) {
        fprintf(stderr, "Erro: %s.\n", app_status_message(APP_INVALID_INPUT_BASE));
        return EXIT_FAILURE;
    }

    if (argc == 4) {
        if (parse_base(argv[3], &output_base) != PARSE_OK) {
            fprintf(stderr, "Erro: %s.\n", app_status_message(APP_INVALID_OUTPUT_BASE));
            return EXIT_FAILURE;
        }

        conversion_request.input_base = input_base;
        conversion_request.output_base = output_base;
        conversion_request.value_text = argv[2];

        return execute_conversion(&conversion_request);
    }

    if (argc == 6) {
        if (parse_base(argv[5], &output_base) != PARSE_OK) {
            fprintf(stderr, "Erro: %s.\n", app_status_message(APP_INVALID_OUTPUT_BASE));
            return EXIT_FAILURE;
        }
    } else {
        output_base = input_base;
    }

    request.input_base = input_base;
    request.output_base = output_base;
    request.left_text = argv[2];
    request.operation_text = argv[3];
    request.right_text = argv[4];

    return execute_request(&request);
}

static int run_interactive_mode(void)
{
    char input_base_text[INPUT_SIZE];
    char inline_input[INPUT_SIZE];
    char *tokens[DIRECT_TOKENS];
    size_t token_count = 0;
    char output_base_text[INPUT_SIZE];
    char left[INPUT_SIZE];
    char right[INPUT_SIZE];
    char operation[INPUT_SIZE];
    NumberBase input_base = BASE_DECIMAL;
    NumberBase output_base = BASE_DECIMAL;
    CalculationRequest request;
    ConversionRequest conversion_request;

    printf("Calculadora para Programador\n");
    printf("============================\n\n");

    if (!read_line("Base ou expressao (ex: dec 10 + 1 dec): ", input_base_text, sizeof(input_base_text))) {
        fprintf(stderr, "Erro: entrada incompleta.\n");
        return EXIT_FAILURE;
    }

    strcpy(inline_input, input_base_text);
    token_count = split_tokens(inline_input, tokens, DIRECT_TOKENS);
    if (try_parse_inline_conversion(tokens, token_count, &conversion_request)) {
        return execute_conversion(&conversion_request);
    }
    if (try_parse_inline_calculation(tokens, token_count, &request)) {
        return execute_request(&request);
    }

    if (parse_base(input_base_text, &input_base) != PARSE_OK) {
        fprintf(stderr, "Erro: %s.\n", app_status_message(APP_INVALID_INPUT_BASE));
        return EXIT_FAILURE;
    }

    if (!read_line("Primeiro valor: ", left, sizeof(left)) ||
        !read_line("Operacao (+, -, *, /): ", operation, sizeof(operation)) ||
        !read_line("Segundo valor: ", right, sizeof(right))) {
        fprintf(stderr, "Erro: entrada incompleta.\n");
        return EXIT_FAILURE;
    }

    if (!read_line("Base de saida (bin/oct/dec/hex): ", output_base_text, sizeof(output_base_text)) ||
        parse_base(output_base_text, &output_base) != PARSE_OK) {
        fprintf(stderr, "Erro: %s.\n", app_status_message(APP_INVALID_OUTPUT_BASE));
        return EXIT_FAILURE;
    }

    request.input_base = input_base;
    request.output_base = output_base;
    request.left_text = left;
    request.operation_text = operation;
    request.right_text = right;

    return execute_request(&request);
}

int main(int argc, char **argv)
{
    if (argc == 1) {
        return run_interactive_mode();
    }

    if (argc == 2 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)) {
        print_usage(argv[0]);
        return EXIT_SUCCESS;
    }

    if (argc == 4 || argc == 5 || argc == 6) {
        return run_direct_mode(argc, argv);
    }

    print_usage(argv[0]);
    return EXIT_FAILURE;
}
