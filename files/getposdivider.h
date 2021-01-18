#include <stdio.h>
#include <stdlib.h>

#pragma once

size_t getposdivider(char *expression, size_t size)
{
    char oper;
    int priority = 3;
    size_t pos = 100, i;

    for (i = 0; i < size; i++)
    {
        char current = expression[i];

        if (current == '\0') break;

        if (current == '-' || current == '+')
        {
            oper = current;
            pos = i;
            priority = 0;
            break;
        }

        if (priority > 1 && (current == '/' || current == '*'))
        {
            oper = current;
            pos = i;
            priority = 1;
            continue;
        }
        
        if (priority == 3 && current == '^')
        {
            oper = '^';
            pos = i;
            priority = 2;
            continue;
        }
    }

    return pos;
}