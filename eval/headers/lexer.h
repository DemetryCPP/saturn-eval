#pragma once
#include <stdio.h>

#include "lexer_types.h"
#include "parser_types.h"
#include "solve_types.h"
#include "status.h"

Token_s *new_token(Tokens_e, char);
Token_s **lexer(char *, size_t *, Status_s *, Operator_s **);

void lexer_unexped_token(char, size_t);
void lexer_log(Token_s *);

char *tokens_to_text(Token_s **, size_t);