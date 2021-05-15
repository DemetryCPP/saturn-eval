#pragma once
#include <stdbool.h>
#include "lexer.h"
#include "parser_types.h"
#include "status.h"

Node_s *new_node(Token_s **, size_t, Node_s *, Node_s *, char, size_t);
size_t find_divider_pos(Token_s **, size_t, Operator_s **);

void parser(Node_s *, Status_s *, Operator_s **);
void remove_brackets(Node_s *);

bool check_brackets(Node_s);