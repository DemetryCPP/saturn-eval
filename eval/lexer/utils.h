#include <stdlib.h>
#pragma once

typedef enum Tokens Tokens_e;
typedef struct Token Token_s;

enum Tokens
{
    t_number,
    t_operators,
    t_decimal_seporator,
    t_brackets,
    t_text,
    t_none
};


struct Token
{
    Tokens_e type;
    char value;
};

Token_s *new_token(Tokens_e type, char value)
{
    Token_s *result = (Token_s *)malloc(sizeof(Token_s));

    result->type = type;
    result->value = value;

    return result;
}

void lexer_unexped_token(char token, size_t position)
{
    printf("unexted token '%c' at %ld\n", token, position);
}

void lexer_log(Token_s *token)
{
    switch (token->type)
    {
        case t_number:              printf("[       NUMBER       ]"); break;
        case t_operators:           printf("[      OPERATOR      ]"); break;
        case t_decimal_seporator:   printf("[ DECIMAL  SEPARATOR ]"); break;
        case t_brackets:            printf("[      BRACKETS      ]"); break;
        case t_text:                printf("[        TEXT        ]"); break;
    }

    printf(" %c\n", token->value);
}