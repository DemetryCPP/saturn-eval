#pragma once
#include <stdbool.h>
#include "lexer.h"
#include "parser_types.h"
#include "status.h"

Node_t *new_node(Token_t **, size_t, Node_t *, Node_t *, char, size_t);
size_t find_divider_pos(Token_t **, size_t, Operator_t **);

void parser(Node_t *, Status_t *, Operator_t **);
void remove_brackets(Node_t *);

bool check_brackets(Node_t);