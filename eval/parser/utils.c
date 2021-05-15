#include <stdlib.h>
#include <stdio.h>

#include "lexer.h"
#include "parser_types.h"

Node_s *new_node(Token_s **tokens, size_t length, Node_s *left, Node_s *right, char operator_sign, size_t divider_pos)
{
    Node_s *result = (Node_s *)malloc(sizeof(Node_s));

    if (!result)
    {
        puts("memory allocation error.");
        exit(1);
    }

    result->tokens = tokens;
    result->length = length;
    result->left = left;
    result->right = right;
    result->operator_sign = operator_sign;
    result->divider_pos = divider_pos;

    return result;
}