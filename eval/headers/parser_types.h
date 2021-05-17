#pragma once
#include "lexer.h"
typedef struct Node_t
{
    struct Node *left;
    struct Node *right;
    Token_t **tokens;
    char Operator_tign;
    size_t divider_pos;
    size_t length;
} Node_t;