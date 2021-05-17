#include <stdio.h>
#pragma once

typedef enum Status_code_t
{
    sc_ok,
    sc_unexped_token,
    sc_brackets_error,
    sc_is_not_defined,
    sc_is_not_a_function,
    sc_unexped_end_of_line,
    sc_zero_tokens
} Status_code_t;

typedef struct Status_t
{
    Status_code_t code;
    size_t data1;
    char *data2;
    char data3;
} Status_t;