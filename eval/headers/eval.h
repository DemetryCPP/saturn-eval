#pragma once

#include "lexer.h"
#include "parser.h"
#include "solve.h"
#include "status.h"

#define VERSION "3.0.3"

double eval(char *, Status_s *, Constant_s **);
void free_tree(Node_s *);
void eval_free(Operator_s **, Token_s **, size_t, Node_s *);