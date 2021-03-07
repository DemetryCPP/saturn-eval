#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#pragma once

#include "../parser/data.h"
#include "../lexer/data.h"

#include "mini.h"

double get_constant(char *name)
{
    if (!strcmp(name, "e")) return exp(1);
    if (!strcmp(name, "pi")) return 3.14159265358979;
    return -1;
}

double solve(Node_s *node)
{
    if (node->left == NULL && node->right == NULL) 
    {
        char *text = lexems_to_text(node->lexems, node->length);
        double result = get_constant(text);
        if (result == -1) result = atof(text);
        free(text);
        return result;
    } 
    else if (node->left->left == NULL 
     && node->left->right == NULL 
     && node->right->left == NULL
     && node->right->right == NULL)
    {
        char *leftT = lexems_to_text(node->left->lexems, node->left->length);
        char *rightT = lexems_to_text(node->right->lexems, node->right->length);

        double leftN = get_constant(leftT);
        double rightN = get_constant(rightT);

        if (rightN == -1) rightN = atof(rightT);
        if (leftN == -1) leftN = atof(leftT);

        free(leftT);
        free(rightT);

        return mini(leftN, rightN, node->Operator);
    }
    else if (node->left->left == NULL
          && node->left->right == NULL)
    {
        char *T = lexems_to_text(node->left->lexems, node->left->length);
        double N = get_constant(T);
        if (N == -1) N = atof(T);
        
        free(T);

        return mini(N, solve(node->right), node->Operator);
    }
    else if (node->right->left == NULL
          && node->right->right == NULL)
    {
        char *T = lexems_to_text(node->right->lexems, node->right->length);
        double N = get_constant(T);
        if (N == -1) N = atof(T);

        free(T);

        return mini(solve(node->left), N, node->Operator);
    }
    else
        return mini(solve(node->left), solve(node->right), node->Operator);
}