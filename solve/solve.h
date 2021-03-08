#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#pragma once

#include "../parser/data.h"
#include "../lexer/data.h"

#include "mini.h"

#define big_num (unsigned)-1

double get_constant(char *name)
{
    if (!strcmp(name, "e")) return exp(1);
    if (!strcmp(name, "pi")) return 3.14159265358979;
    return -1;
}

double get_value(char *text)
{
    double result;

    if (text[0] >= 'a' && text[0] <= 'z') 
    {
        result = get_constant(text);

        if (result == -1) 
        {
            printf("\"%s\" is not defined\n", text);
            return big_num;
        }
    }
    else result = atof(text);
    return result;
}

double solve(Node_s *node)
{
    if (node->right == NULL && node->left == NULL)
    {
        char *text = lexems_to_text(node->lexems, node->length);
        double result;

        result = get_value(text);

        free(text);
        return result;
    }

    char *leftT = lexems_to_text(node->left->lexems, node->left->length),
         *rightT = lexems_to_text(node->right->lexems, node->right->length);

    double left, right;

    if (node->left->left == NULL && node->left->right == NULL) left = get_value(leftT);
    else left = solve(node->left);

    if (node->right->left == NULL && node->right->right == NULL) right = get_value(rightT);
    else right = solve(node->right);

    if (right == big_num || left == big_num) return big_num;

    return mini(left, right, node->Operator);
}