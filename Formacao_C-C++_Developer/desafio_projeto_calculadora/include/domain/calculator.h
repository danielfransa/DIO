#ifndef PROGRAMMER_CALC_DOMAIN_CALCULATOR_H
#define PROGRAMMER_CALC_DOMAIN_CALCULATOR_H

#include <stdint.h>

typedef enum {
    OP_ADD,
    OP_SUBTRACT,
    OP_MULTIPLY,
    OP_DIVIDE
} Operation;

typedef enum {
    CALC_OK = 0,
    CALC_INVALID_OPERATION,
    CALC_DIVISION_BY_ZERO,
    CALC_OVERFLOW
} CalcStatus;

CalcStatus parse_operation(const char *text, Operation *operation);
CalcStatus calculate_int64(int64_t left, int64_t right, Operation operation, int64_t *result);
const char *operation_label(Operation operation);

#endif
