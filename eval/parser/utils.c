#include <stdlib.h>
#include <stdio.h>

#include "lexer.h"
#include "parser_types.h"

Node_t *new_node(Token_t **tokens, size_t length, Node_t *left, Node_t *right, char Operator_tign, size_t divider_pos)
{
    Node_t *result = malloc(sizeof(Node_t));

    if (!result)
    {
        puts("memory allocation error.");
        exit(1);
    }

    result->tokens = tokens;
    result->length = length;
    result->left = left;
    result->right = right;
    result->Operator_tign = Operator_tign;
    result->divider_pos = divider_pos;

    return result;
}