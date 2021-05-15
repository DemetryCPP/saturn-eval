#pragma once

#include <stdio.h>
#include <stdbool.h>

#include "parser.h"
#include "parser_types.h"
#include "solve_types.h"
#include "status.h"

Constant_s *new_constant(char *, double);
Operator_s *new_operator(char, short, operator_action_t);
Operator_s **init_operators();

double execute_operator(char, Operator_s **, double, double);
double function(char *, double, Status_s *);
double get_value(char *, Constant_s **, Status_s *);
double solve(Node_s *, Status_s *, Operator_s **, Constant_s **);

short get_priority(char, Operator_s **);
bool check_operator(char, Operator_s **);
void free_operators(Operator_s **);