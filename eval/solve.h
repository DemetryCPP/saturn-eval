#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer/utils.h"
#include "parser/utils.h"
#include "operators.h"
#include "constants.h"
#include "function.h"

#define status_ret if (*status) return -1;

double get_value(char *text, Constant_s **constants, size_t *status)
{
    if (text[0] >= 'a' && text[0] <= 'z' || text[0] >= 'A' && text[0] <= 'Z')
    {
        for (size_t i = 0; constants[i]->name != ""; i++)
        {
            Constant_s *current = constants[i];

            if (strcmp(current->name, text) == 0) return current->value;
        }

        printf("\"%s\" is not defined.\n", text);
        *status = 1;
        return 0;
    }
    else
        return atof(text);
}

double solve(Node_s *node, size_t *status, Operator_s **operators, Constant_s **constants)
{
    status_ret
    double left, right, result;

    if (node->operator_sign == '\0')
    {
        char *text = tokens_to_text(node->tokens, node->length);
        double result = get_value(text, constants, status);
        free(text);
        return result;
    }

    if (node->operator_sign == 'f')
    {
        double arg = solve(node->right, status, operators, constants);
        status_ret
        char *fname = tokens_to_text(node->left->tokens, node->left->length);

        double result = function(fname, arg, status);
        status_ret
        free(fname);
        return result;
    }

    left = solve(node->left, status, operators, constants);
    right = solve(node->right, status, operators, constants);
    status_ret

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