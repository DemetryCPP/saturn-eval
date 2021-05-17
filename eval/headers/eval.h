#pragma once

#include "lexer.h"
#include "parser.h"
#include "solve.h"
#include "status.h"

#define VERSION "3.0.4"

double eval(char *, Status_t *, Constant_t **);
void free_tree(Node_t *);
void eval_free(Operator_t **, Token_t **, size_t, Node_t *);