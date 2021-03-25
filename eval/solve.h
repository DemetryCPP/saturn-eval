#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer/utils.h"
#include "parser/utils.h"
#include "operators.h"
#include "constants.h"

double get_value(char *text, Constant_s **constants, size_t *status)
{
    if (text[0] >= 'a' && text[0] <= 'z' || text[0] >= 'A' && text[0] <= 'Z')
    {
        for (size_t i = 0; constants[i]->name != ""; i++)
        {
            Constant_s *current = constants[i];

            if (strcmp(current->name, text) == 0) return current->value;
        }

        printf("\"%s\" is not defined.\n");
        *status = 1;
        return 0;
    }
    else
        return atof(text);
}

double solve(Node_s *node, size_t *status, Operator_s **operators, Constant_s **constants)
{
    double left;
    double right;
    double result;

    if (node->left == NULL && node->right == NULL)
    {
        char *text = tokens_to_text(node->tokens, node->length);
        double result = get_value(text, constants, status);
        free(text);
        return result;
    }

    if (node->left->operator_sign == '\0')
    {
        char *leftt = tokens_to_text(node->left->tokens, node->left->length);
        left = get_value(leftt, constants, status);
        if (*status) return;
        free(leftt);
    }
    else
        left = solve(node->left, status, operators, constants);

    if (node->right->operator_sign == '\0')
    {
        char *rightt = tokens_to_text(node->right->tokens, node->right->length);
        right = get_value(rightt, constants, status);
        if (*status) return;
        free(rightt);
    }
    else
        right = solve(node->right, status, operators, constants);

    for (size_t i = 0; i < OPERATORS_COUNT; i++)
    {
        if (operators[i]->sign == node->operator_sign)
        {
            result = operators[i]->action(left, right);
            break;
        }
    }

    return result;
}