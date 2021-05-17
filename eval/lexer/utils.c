#include <stdlib.h>
#include "lexer.h"

Token_t *new_token(Tokens_t type, char value)
{
    Token_t *result = malloc(sizeof(Token_t));

    if (!result)
    {
        puts("memory allocation error.");
        exit(1);
    }

    result->type = type;
    result->value = value;

    return result;
}

void lexer_unexped_token(char token, size_t position)
{
    printf("unexted token '%c' at %ld\n", token, position);
}

void lexer_log(Token_t *token)
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

char *tokens_to_text(Token_t **tokens, size_t length)
{
    char *result = malloc(length * sizeof(char));

    if (!result)
    {
        puts("memory allocation error.\n");
        exit(1);
    }

    for (size_t i = 0; i < length; i++)
        result[i] = tokens[i]->value;

    result[length] = '\0';

    return result;
}