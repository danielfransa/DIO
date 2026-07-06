#include "app/programmer_calculator.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void assert_status(AppStatus actual, AppStatus expected, const char *case_name)
{
    if (actual != expected) {
        fprintf(stderr, "FAIL %s: esperado status %d, recebido %d\n", case_name, expected, actual);
        exit(EXIT_FAILURE);
    }
}

static void assert_text(const char *actual, const char *expected, const char *case_name)
{
    if (strcmp(actual, expected) != 0) {
        fprintf(stderr, "FAIL %s: esperado '%s', recebido '%s'\n", case_name, expected, actual);
        exit(EXIT_FAILURE);
    }
}

static void test_sum_binary_to_decimal(void)
{
    char output[128];
    CalculationRequest request = {BASE_BINARY, BASE_DECIMAL, "1010", "11", "+"};

    assert_status(run_calculation(&request, output, sizeof(output)), APP_OK, "soma binaria");
    assert_text(output, "13", "soma binaria");
}

static void test_subtract_decimal_to_hex(void)
{
    char output[128];
    CalculationRequest request = {BASE_DECIMAL, BASE_HEXADECIMAL, "255", "16", "-"};

    assert_status(run_calculation(&request, output, sizeof(output)), APP_OK, "subtracao decimal");
    assert_text(output, "EF", "subtracao decimal");
}

static void test_multiply_octal_to_decimal(void)
{
    char output[128];
    CalculationRequest request = {BASE_OCTAL, BASE_DECIMAL, "17", "2", "*"};

    assert_status(run_calculation(&request, output, sizeof(output)), APP_OK, "multiplicacao octal");
    assert_text(output, "30", "multiplicacao octal");
}

static void test_divide_hex_to_binary(void)
{
    char output[128];
    CalculationRequest request = {BASE_HEXADECIMAL, BASE_BINARY, "FF", "F", "/"};

    assert_status(run_calculation(&request, output, sizeof(output)), APP_OK, "divisao hexadecimal");
    assert_text(output, "10001", "divisao hexadecimal");
}

static void test_convert_binary_to_decimal(void)
{
    char output[128];
    ConversionRequest request = {BASE_BINARY, BASE_DECIMAL, "01010110"};

    assert_status(run_conversion(&request, output, sizeof(output)), APP_OK, "conversao binaria");
    assert_text(output, "86", "conversao binaria");
}

static void test_invalid_binary_value(void)
{
    char output[128];
    CalculationRequest request = {BASE_BINARY, BASE_DECIMAL, "102", "1", "+"};

    assert_status(run_calculation(&request, output, sizeof(output)), APP_INVALID_LEFT_VALUE, "binario invalido");
}

static void test_division_by_zero(void)
{
    char output[128];
    CalculationRequest request = {BASE_DECIMAL, BASE_DECIMAL, "10", "0", "/"};

    assert_status(run_calculation(&request, output, sizeof(output)), APP_DIVISION_BY_ZERO, "divisao por zero");
}

int main(void)
{
    test_sum_binary_to_decimal();
    test_subtract_decimal_to_hex();
    test_multiply_octal_to_decimal();
    test_divide_hex_to_binary();
    test_convert_binary_to_decimal();
    test_invalid_binary_value();
    test_division_by_zero();

    printf("Todos os testes passaram.\n");
    return EXIT_SUCCESS;
}
