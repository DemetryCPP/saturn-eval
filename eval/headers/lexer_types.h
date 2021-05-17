#pragma once
typedef enum Tokens_t
{
    t_none,
    t_number,
    t_operators,
    t_decimal_seporator,
    t_brackets,
    t_text
} Tokens_t;

typedef struct Token_t
{
    Tokens_t type;
    char value;
} Token_t;