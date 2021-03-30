#include <stdlib.h>
#include "../headers/solve_types.h"

// typedef struct Constant
// {
//     char *name;
//     double value;
// } Constant_s;

Constant_s *new_constant(char *name, double value)
{
    Constant_s *constant = (Constant_s *)malloc(sizeof(Constant_s));
    constant->name = name;
    constant->value = value;
    return constant;
}