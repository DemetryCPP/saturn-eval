#pragma once

#include "lexer.h"
#include "parser.h"
#include "solve.h"
#include "status.h"

#include "lexer_types.h"
#include "parser_types.h"
#include "solve_types.h"

#define VERSION "3.0.3"

double eval(char *expression, Status_s *status, Constant_s **constants);
void free_tree(Node_s *node);
void eval_free(Operator_s **operators, Token_s **tokens, size_t tokens_count, Node_s *head);