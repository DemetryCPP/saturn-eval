#include <stdlib.h>
#include "eval.h"

double eval(char *expression, Status_t *status, Constant_t **constants)
{
    size_t tokens_count;
    Operator_t **operators = init_operators();
    Token_t **tokens = lexer(expression, &tokens_count, status, operators);

    if (status->code != sc_ok)
    {
        eval_free(operators, tokens, tokens_count, NULL);
        return 0.0;
    }

    Node_t *head = new_node(tokens, tokens_count, NULL, NULL, 0, 0);
    parser(head, status, operators);
    
    if (status->code != sc_ok)
    {
        eval_free(operators, tokens, tokens_count, head);
        return 0.0;
    }

    double result = solve(head, status, operators, constants);
    eval_free(operators, tokens, tokens_count, head);

    return result;
}