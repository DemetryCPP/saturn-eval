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
    if (node->left == NULL && node->right == NULL) 
    {
        char *text = lexems_to_text(node->lexems, node->length);
        double result;

        result = get_value(text);

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

        double leftN;
        double rightN;

        leftN = get_value(leftT);
        rightN = get_value(rightT);

        if (leftN == big_num || rightN == big_num) return big_num;

        free(leftT);
        free(rightT);

        return mini(leftN, rightN, node->Operator);
    }
    else if (node->left->left == NULL
          && node->left->right == NULL)
    {
        char *text = lexems_to_text(node->left->lexems, node->left->length);
        double n = get_value(text);

        if (n == big_num) return big_num;
        
        free(text);

        return mini(n, solve(node->right), node->Operator);
    }
    else if (node->right->left == NULL
          && node->right->right == NULL)
    {
        char *text = lexems_to_text(node->right->lexems, node->right->length);
        double n = get_value(text);

        if (n == big_num) return big_num;

        free(text);

        double left = solve(node->left);
        if (left == big_num) return big_num;

        return mini(left, n, node->Operator);
    }
    else
    {
        double left = solve(node->left);
        double right = solve(node->right);

        if (left == big_num || right == big_num) return big_num;

        return mini(left, right, node->Operator);
    }
}