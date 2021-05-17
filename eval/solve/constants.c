#include <stdlib.h>
#include <stdio.h>

#include "solve_types.h"

Constant_t *new_constant(char *name, double value)
{
    Constant_t *result = malloc(sizeof(Constant_t));
    
    if (!result)
    {
        puts("memory allocation error.");
        exit(1);
    }

    result->name = name;
    result->value = value;
    return result;
}