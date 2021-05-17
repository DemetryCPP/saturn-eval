#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include "solve_types.h"

#define OPERATORS_COUNT 7
#define OPERATION(name, action) double name(double left, double right) { return action; }

Operator_t *new_operator(char sign, unsigned short priority, operator_action_t action)
{
    Operator_t *result = malloc(sizeof(Operator_t));
    
    if (!result)
    {
        puts("memory allocation error.");
        exit(1);
    }
    
    result->sign = sign;
    result->priority = priority;
    result->action = action;
    return result;
}

OPERATION(add, left + right)
OPERATION(differency, left - right)
OPERATION(product, left * right)
OPERATION(division, left / right)
OPERATION(modulo_division, left - right * floor(left / right))
OPERATION(whole_division, round(left / right))

Operator_t **init_operators()
{
    Operator_t **operators = malloc(OPERATORS_COUNT * sizeof(Operator_t *));

    if (!operators)
    {
        puts("memory allocation error.");
        exit(1);
    }

    operators[0] = new_operator('+', 1, add);
    operators[1] = new_operator('-', 1, differency);
    operators[2] = new_operator('*', 2, product);
    operators[3] = new_operator('/', 2, division);
    operators[4] = new_operator('%', 2, modulo_division);
    operators[5] = new_operator('\\', 2, whole_division);
    operators[6] = new_operator('^', 3, pow);

    return operators;
}

bool check_operator(char _char, Operator_t **operators)
{
    for (size_t i = 0; i < OPERATORS_COUNT; i++)
        if (operators[i]->sign == _char) 
            return true;

    return false;
}

short get_priority(char _char, Operator_t **operators)
{
    for (size_t i = 0; i < OPERATORS_COUNT; i++)
        if (operators[i]->sign == _char) return operators[i]->priority;

    return -1;
}

void free_operators(Operator_t **operators)
{
    for (size_t i = 0; i < OPERATORS_COUNT; i++) free(operators[i]);
    free(operators);
}

double execute_operator(char sign, Operator_t **operators, double left, double right)
{
    for (size_t i = 0; i < OPERATORS_COUNT; i++)
        if (operators[i]->sign == sign)
            return operators[i]->action(left, right);

    return 0;
}
