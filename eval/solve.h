#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer/utils.h"
#include "parser/utils.h"
#include "operators.h"

double solve(Node_s *node, Operator_s **operators)
{
    double left;
    double right;
    double result;

    if (node->left == NULL && node->right == NULL)
    {
        char *text = tokens_to_text(node->tokens, node->length);
        double result = atof(text);
        free(text);
        return result;
    }

    if (node->left->operator_sign == '\0')
    {
        char *leftt = tokens_to_text(node->left->tokens, node->left->length);
        left = atof(leftt);
        free(leftt);
    }
    else
        left = solve(node->left, operators);

    if (node->right->operator_sign == '\0')
    {
        char *rightt = tokens_to_text(node->right->tokens, node->right->length);
        right = atof(rightt);
        free(rightt);
    }
    else
        right = solve(node->right, operators);

    for (size_t i = 0; i < OPERATORS_COUNT; i++)
    {
        if (operators[i]->sign == node->operator_sign)
        {
            result = operators[i]->action(left, right);
            break;
        }
    }

    printf("%lf %c %lf = %lf\n", left, node->operator_sign, right, result);
    return result;
}