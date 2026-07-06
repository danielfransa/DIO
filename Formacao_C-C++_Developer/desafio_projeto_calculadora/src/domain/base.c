#include "domain/base.h"

#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int equals_ignore_case(const char *left, const char *right)
{
    while (*left != '\0' && *right != '\0') {
        if (tolower((unsigned char)*left) != tolower((unsigned char)*right)) {
            return 0;
        }
        left++;
        right++;
    }

    return *left == '\0' && *right == '\0';
}

ParseStatus parse_base(const char *text, NumberBase *base)
{
    if (text == NULL || base == NULL) {
        return PARSE_INVALID_BASE;
    }

    if (equals_ignore_case(text, "bin") || equals_ignore_case(text, "binary") ||
        equals_ignore_case(text, "binario")) {
        *base = BASE_BINARY;
        return PARSE_OK;
    }

    if (equals_ignore_case(text, "oct") || equals_ignore_case(text, "octal")) {
        *base = BASE_OCTAL;
        return PARSE_OK;
    }

    if (equals_ignore_case(text, "dec") || equals_ignore_case(text, "decimal")) {
        *base = BASE_DECIMAL;
        return PARSE_OK;
    }

    if (equals_ignore_case(text, "hex") || equals_ignore_case(text, "hexadecimal")) {
        *base = BASE_HEXADECIMAL;
        return PARSE_OK;
    }

    return PARSE_INVALID_BASE;
}

ParseStatus parse_int64_in_base(const char *text, NumberBase base, int64_t *value)
{
    char *end = NULL;
    long long parsed = 0;

    if (text == NULL || value == NULL) {
        return PARSE_INVALID_VALUE;
    }

    errno = 0;
    parsed = strtoll(text, &end, (int)base);

    if (end == text || *end != '\0') {
        return PARSE_INVALID_VALUE;
    }

    if (errno == ERANGE) {
        return PARSE_OUT_OF_RANGE;
    }

    *value = (int64_t)parsed;
    return PARSE_OK;
}

static ParseStatus format_unsigned(uint64_t value, NumberBase base, char *buffer, size_t buffer_size)
{
    static const char digits[] = "0123456789ABCDEF";
    char reversed[65];
    size_t count = 0;
    size_t index = 0;

    if (buffer_size == 0) {
        return PARSE_OUTPUT_TOO_SMALL;
    }

    if (value == 0) {
        if (buffer_size < 2) {
            return PARSE_OUTPUT_TOO_SMALL;
        }
        buffer[0] = '0';
        buffer[1] = '\0';
        return PARSE_OK;
    }

    while (value > 0) {
        reversed[count++] = digits[value % (uint64_t)base];
        value /= (uint64_t)base;
    }

    if (count + 1 > buffer_size) {
        return PARSE_OUTPUT_TOO_SMALL;
    }

    while (count > 0) {
        buffer[index++] = reversed[--count];
    }
    buffer[index] = '\0';

    return PARSE_OK;
}

ParseStatus format_int64_in_base(int64_t value, NumberBase base, char *buffer, size_t buffer_size)
{
    uint64_t magnitude = 0;
    ParseStatus status = PARSE_OK;

    if (buffer == NULL) {
        return PARSE_OUTPUT_TOO_SMALL;
    }

    if (base == BASE_DECIMAL) {
        int written = snprintf(buffer, buffer_size, "%" PRId64, value);
        if (written < 0 || (size_t)written >= buffer_size) {
            return PARSE_OUTPUT_TOO_SMALL;
        }
        return PARSE_OK;
    }

    if (value < 0) {
        if (buffer_size < 2) {
            return PARSE_OUTPUT_TOO_SMALL;
        }
        buffer[0] = '-';
        magnitude = (uint64_t)(-(value + 1)) + 1;
        status = format_unsigned(magnitude, base, buffer + 1, buffer_size - 1);
        return status;
    }

    return format_unsigned((uint64_t)value, base, buffer, buffer_size);
}

const char *base_label(NumberBase base)
{
    switch (base) {
    case BASE_BINARY:
        return "binario";
    case BASE_OCTAL:
        return "octal";
    case BASE_DECIMAL:
        return "decimal";
    case BASE_HEXADECIMAL:
        return "hexadecimal";
    default:
        return "desconhecida";
    }
}
