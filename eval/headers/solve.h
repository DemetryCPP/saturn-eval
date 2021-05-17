#pragma once

#include <stdio.h>
#include <stdbool.h>

#include "parser.h"
#include "parser_types.h"
#include "solve_types.h"
#include "status.h"

Constant_t *new_constant(char *, double);
Operator_t *new_operator(char, short, operator_action_t);
Operator_t **init_operators();

double execute_operator(char, Operator_t **, double, double);
double function(char *, double, Status_t *);
double get_value(char *, Constant_t **, Status_t *);
double solve(Node_t *, Status_t *, Operator_t **, Constant_t **);

short get_priority(char, Operator_t **);
bool check_operator(char, Operator_t **);
void free_operators(Operator_t **);