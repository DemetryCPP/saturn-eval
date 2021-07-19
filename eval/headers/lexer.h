#pragma once
#include <stdio.h>

#include "lexer_types.h"
#include "parser_types.h"
#include "solve_types.h"
#include "status.h"

Token_t *new_token(Tokens_t, char);
Token_t **lexer(char *, size_t *, Status_t *, Operator_t **);

void lexer_unexpected_token(char, size_t);
void lexer_log(Token_t *);

char *tokens_to_text(Token_t **, size_t);