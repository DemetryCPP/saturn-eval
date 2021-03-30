#pragma once
#include <stdio.h>
#include "parser.h"
#include "parser_types.h"
#include "solve_types.h"

Constant_s *new_constant(char *name, double value);
Operator_s *new_operator(char sign, unsigned short priority, operator_action_t aciton);

double add(double left, double right);
double differency(double left, double right);
double product(double left, double right);
double division(double left, double right);
double modulo_division(double left, double right);
double whole_division(double left, double right);
double exponentation(double left, double right);

Operator_s **init_operators();

short check_operator(char _char, Operator_s **operators);
short get_priority(char _char, Operator_s **operators);
double function(char *fname, double arg, size_t *status);

double get_value(char *text, Constant_s **constants, size_t *status);
double solve(Node_s *node, size_t *status, Operator_s **operators, Constant_s **constants);