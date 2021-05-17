#pragma once

typedef double(* operator_action_t)(double, double);
typedef struct Constant_t
{
    char *name;
    double value;
} Constant_t;

typedef struct Operator_t
{
    char sign;
    unsigned short priority;
    operator_action_t action;
} Operator_t;