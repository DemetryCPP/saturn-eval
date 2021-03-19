#include <stdlib.h>
#include "../lexer/utils.h"

#pragma once

typedef struct Node // структура ноды (ветки) 
{
    struct Node *left;       // левое разветвление
    struct Node *right;      // правое разветвление
    Token_s **tokens;   // массив (указателей) токенов
    char operator_sign; // оператор ветки
    size_t divider_pos; // позиция по которой было разделено выражение
    size_t length;      // длинна ветки или количество токенов
} Node_s;

Node_s *new_node(Token_s **tokens, size_t length, Node_s *left, Node_s *right, char operator_sign, size_t divider_pos)
    // функция создания новой ветки
{
    Node_s *result = (Node_s *)malloc(sizeof(Node_s));

    result->tokens = tokens;
    result->length = length;
    result->left = left;
    result->right = right;
    result->operator_sign = operator_sign;
    result->divider_pos = divider_pos;

    return result;
}