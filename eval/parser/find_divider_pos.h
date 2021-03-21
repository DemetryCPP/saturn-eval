#include <stdlib.h>

#pragma once

#include "../lexer/utils.h"
#include "../operators.h"

size_t find_divider_pos(Token_s **tokens, size_t tokens_count, Operator_s **operators, size_t *status)
{
    short priority = 4;
    size_t pos = -1;
    int brackets = 0;

    for (size_t i = tokens_count - 1; i + 1 > 0; i--)
    {
        Token_s *current = tokens[i];
        if (current->type == t_brackets)
        {
            if (current->value == '(') brackets++;
            else if (current->value == ')') brackets--;

            continue;
        }
        else if (current->type != t_operators) continue;

        short current_priority = get_priority(current->value, operators);

        if (current_priority < priority)
        {
            pos = i;
            priority = current_priority;
        }
    }

    if (brackets != 0) 
    {
        *status = 1;
        printf("Brackets error!\n");
        return -1;
    }

    return pos;
}