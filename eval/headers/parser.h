#pragma once
#include "lexer.h"
#include "lexer_types.h"
#include "parser_types.h"

Node_s *new_node(Token_s **tokens, size_t length, Node_s *left, Node_s *right, char operator_sign, size_t divider_pos);
size_t find_divider_pos(Token_s **tokens, size_t tokens_count, Operator_s **operators, size_t *status);
void parser(Node_s *node, size_t *status, Operator_s **operators);
short check_brackets(Node_s node);
void remove_brackets(Node_s *node);