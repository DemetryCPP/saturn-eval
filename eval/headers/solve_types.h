#pragma once

typedef double(* operator_action_t)(double, double);
typedef struct Constant
{
    char *name;
    double value;
} Constant_s;

typedef struct Operator
{
    char sign;
    unsigned short priority;
    operator_action_t action;
} Operator_s;