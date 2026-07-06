#ifndef PROGRAMMER_CALC_DOMAIN_BASE_H
#define PROGRAMMER_CALC_DOMAIN_BASE_H

#include <stdint.h>
#include <stddef.h>

typedef enum {
    BASE_BINARY = 2,
    BASE_OCTAL = 8,
    BASE_DECIMAL = 10,
    BASE_HEXADECIMAL = 16
} NumberBase;

typedef enum {
    PARSE_OK = 0,
    PARSE_INVALID_BASE,
    PARSE_INVALID_VALUE,
    PARSE_OUT_OF_RANGE,
    PARSE_OUTPUT_TOO_SMALL
} ParseStatus;

ParseStatus parse_base(const char *text, NumberBase *base);
ParseStatus parse_int64_in_base(const char *text, NumberBase base, int64_t *value);
ParseStatus format_int64_in_base(int64_t value, NumberBase base, char *buffer, size_t buffer_size);
const char *base_label(NumberBase base);

#endif
