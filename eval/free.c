#include <stdio.h>
#include <stdlib.h>

#include "eval.h"

void free_tree(Node_s *node)
{
    if (node->left) free_tree(node->left);
    if (node->right) free_tree (node->right);

    free(node);
}

void eval_free(Operator_s **operators, Token_s **tokens, size_t tokens_count, Node_s *head)
{
    if (operators)
    {
        free_operators(operators);
    }

    if (tokens)
    {
        for (size_t i = 0; i < tokens_count; i++) free(tokens[i]);
        free(tokens);
    }

    if (head) free_tree(head);
}