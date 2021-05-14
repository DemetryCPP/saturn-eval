#include <stdlib.h>
#include <stdio.h>

#include "solve_types.h"

Constant_s *new_constant(char *name, double value)
{
    Constant_s *result = (Constant_s *)malloc(sizeof(Constant_s));
    
    if (result == NULL)
    {
        puts("memory allocation error.");
        exit(1);
    }

    result->name = name;
    result->value = value;
    return result;
}