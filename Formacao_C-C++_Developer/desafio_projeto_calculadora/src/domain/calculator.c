#include "domain/calculator.h"

#include <limits.h>
#include <stddef.h>
#include <string.h>

CalcStatus parse_operation(const char *text, Operation *operation)
{
    if (text == NULL || operation == NULL) {
        return CALC_INVALID_OPERATION;
    }

    if (strcmp(text, "+") == 0) {
        *operation = OP_ADD;
        return CALC_OK;
    }
    if (strcmp(text, "-") == 0) {
        *operation = OP_SUBTRACT;
        return CALC_OK;
    }
    if (strcmp(text, "*") == 0 || strcmp(text, "x") == 0 || strcmp(text, "X") == 0) {
        *operation = OP_MULTIPLY;
        return CALC_OK;
    }
    if (strcmp(text, "/") == 0) {
        *operation = OP_DIVIDE;
        return CALC_OK;
    }

    return CALC_INVALID_OPERATION;
}

CalcStatus calculate_int64(int64_t left, int64_t right, Operation operation, int64_t *result)
{
    if (result == NULL) {
        return CALC_INVALID_OPERATION;
    }

    switch (operation) {
    case OP_ADD:
#if defined(__GNUC__) || defined(__clang__)
        return __builtin_add_overflow(left, right, result) ? CALC_OVERFLOW : CALC_OK;
#else
        if ((right > 0 && left > INT64_MAX - right) || (right < 0 && left < INT64_MIN - right)) {
            return CALC_OVERFLOW;
        }
        *result = left + right;
        return CALC_OK;
#endif
    case OP_SUBTRACT:
#if defined(__GNUC__) || defined(__clang__)
        return __builtin_sub_overflow(left, right, result) ? CALC_OVERFLOW : CALC_OK;
#else
        if ((right < 0 && left > INT64_MAX + right) || (right > 0 && left < INT64_MIN + right)) {
            return CALC_OVERFLOW;
        }
        *result = left - right;
        return CALC_OK;
#endif
    case OP_MULTIPLY:
#if defined(__GNUC__) || defined(__clang__)
        return __builtin_mul_overflow(left, right, result) ? CALC_OVERFLOW : CALC_OK;
#else
        if (left != 0 && right != 0 && (left > INT64_MAX / right || left < INT64_MIN / right)) {
            return CALC_OVERFLOW;
        }
        *result = left * right;
        return CALC_OK;
#endif
    case OP_DIVIDE:
        if (right == 0) {
            return CALC_DIVISION_BY_ZERO;
        }
        if (left == INT64_MIN && right == -1) {
            return CALC_OVERFLOW;
        }
        *result = left / right;
        return CALC_OK;
    default:
        return CALC_INVALID_OPERATION;
    }
}

const char *operation_label(Operation operation)
{
    switch (operation) {
    case OP_ADD:
        return "+";
    case OP_SUBTRACT:
        return "-";
    case OP_MULTIPLY:
        return "*";
    case OP_DIVIDE:
        return "/";
    default:
        return "?";
    }
}
