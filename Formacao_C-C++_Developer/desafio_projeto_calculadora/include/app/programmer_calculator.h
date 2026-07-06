#ifndef PROGRAMMER_CALC_APP_PROGRAMMER_CALCULATOR_H
#define PROGRAMMER_CALC_APP_PROGRAMMER_CALCULATOR_H

#include <stddef.h>

#include "domain/base.h"
#include "domain/calculator.h"

typedef enum {
    APP_OK = 0,
    APP_INVALID_INPUT_BASE,
    APP_INVALID_OUTPUT_BASE,
    APP_INVALID_LEFT_VALUE,
    APP_INVALID_RIGHT_VALUE,
    APP_INVALID_OPERATION,
    APP_DIVISION_BY_ZERO,
    APP_OVERFLOW,
    APP_OUTPUT_TOO_SMALL
} AppStatus;

typedef struct {
    NumberBase input_base;
    NumberBase output_base;
    const char *left_text;
    const char *right_text;
    const char *operation_text;
} CalculationRequest;

AppStatus run_calculation(const CalculationRequest *request, char *output, size_t output_size);
const char *app_status_message(AppStatus status);

#endif
