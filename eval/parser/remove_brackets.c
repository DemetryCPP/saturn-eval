#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "parser_types.h"
#include "lexer_types.h"

bool check_brackets(Node_s *node)
{
    size_t brackets = 0;
    if (node->tokens[0]->type != t_brackets || node->tokens[node->length - 1]->type != t_brackets) return false;

    for (size_t i = 0; i < node->length; i++)
    {
        Token_s *current = node->tokens[i];

        if (current->type != t_brackets) continue;

        if (current->value == '(') brackets++;
        else if (current->value == ')') brackets--;

        if (brackets == 0 && i != node->length - 1) return false;
    }

    return true;
}

void remove_brackets(Node_s *node)
{
    while (check_brackets(node))
    {
        node->tokens++;
        node->length -= 2;
    }
}