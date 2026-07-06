#include "app/programmer_calculator.h"

#include <stdint.h>

static AppStatus map_parse_status(ParseStatus status, AppStatus invalid_status)
{
    switch (status) {
    case PARSE_OK:
        return APP_OK;
    case PARSE_OUT_OF_RANGE:
        return APP_OVERFLOW;
    case PARSE_OUTPUT_TOO_SMALL:
        return APP_OUTPUT_TOO_SMALL;
    case PARSE_INVALID_BASE:
    case PARSE_INVALID_VALUE:
    default:
        return invalid_status;
    }
}

static AppStatus map_calc_status(CalcStatus status)
{
    switch (status) {
    case CALC_OK:
        return APP_OK;
    case CALC_DIVISION_BY_ZERO:
        return APP_DIVISION_BY_ZERO;
    case CALC_OVERFLOW:
        return APP_OVERFLOW;
    case CALC_INVALID_OPERATION:
    default:
        return APP_INVALID_OPERATION;
    }
}

AppStatus run_calculation(const CalculationRequest *request, char *output, size_t output_size)
{
    int64_t left = 0;
    int64_t right = 0;
    int64_t result = 0;
    Operation operation = OP_ADD;
    AppStatus app_status = APP_OK;

    if (request == NULL) {
        return APP_INVALID_LEFT_VALUE;
    }

    app_status = map_parse_status(
        parse_int64_in_base(request->left_text, request->input_base, &left),
        APP_INVALID_LEFT_VALUE);
    if (app_status != APP_OK) {
        return app_status;
    }

    app_status = map_parse_status(
        parse_int64_in_base(request->right_text, request->input_base, &right),
        APP_INVALID_RIGHT_VALUE);
    if (app_status != APP_OK) {
        return app_status;
    }

    if (parse_operation(request->operation_text, &operation) != CALC_OK) {
        return APP_INVALID_OPERATION;
    }

    app_status = map_calc_status(calculate_int64(left, right, operation, &result));
    if (app_status != APP_OK) {
        return app_status;
    }

    return map_parse_status(
        format_int64_in_base(result, request->output_base, output, output_size),
        APP_OUTPUT_TOO_SMALL);
}

AppStatus run_conversion(const ConversionRequest *request, char *output, size_t output_size)
{
    int64_t value = 0;
    AppStatus app_status = APP_OK;

    if (request == NULL) {
        return APP_INVALID_LEFT_VALUE;
    }

    app_status = map_parse_status(
        parse_int64_in_base(request->value_text, request->input_base, &value),
        APP_INVALID_LEFT_VALUE);
    if (app_status != APP_OK) {
        return app_status;
    }

    return map_parse_status(
        format_int64_in_base(value, request->output_base, output, output_size),
        APP_OUTPUT_TOO_SMALL);
}

const char *app_status_message(AppStatus status)
{
    switch (status) {
    case APP_OK:
        return "calculo realizado com sucesso";
    case APP_INVALID_INPUT_BASE:
        return "base de entrada invalida";
    case APP_INVALID_OUTPUT_BASE:
        return "base de saida invalida";
    case APP_INVALID_LEFT_VALUE:
        return "primeiro valor invalido para a base informada";
    case APP_INVALID_RIGHT_VALUE:
        return "segundo valor invalido para a base informada";
    case APP_INVALID_OPERATION:
        return "operacao invalida";
    case APP_DIVISION_BY_ZERO:
        return "divisao por zero nao e permitida";
    case APP_OVERFLOW:
        return "resultado fora do intervalo de 64 bits com sinal";
    case APP_OUTPUT_TOO_SMALL:
        return "buffer de saida insuficiente";
    default:
        return "erro desconhecido";
    }
}
