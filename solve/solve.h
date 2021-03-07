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
        double result;

        if (text[0] >= 'a' && text[0] <= 'z') 
        {
            result = get_constant(text);

            if (result == -1) 
            {
                printf("\"%s\" is not defined\n", text);
                return (unsigned)-1;
            }
        }
        else result = atof(text);

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

        if (leftT[0] >= 'a' && leftT[0] <= 'z') 
        {
            leftN = get_constant(leftT);

            if (leftN == -1) 
            {
                printf("\"%s\" is not defined\n", leftT);
                return (unsigned)-1;
            }
        }
        else leftN = atof(leftT);

        if (rightT[0] >= 'a' && rightT[0] <= 'z') 
        {
            rightN = get_constant(rightT);

            if (rightN == -1) 
            {
                printf("\"%s\" is not defined\n", rightT);
                return (unsigned)-1;
            }
        }
        else rightN = atof(rightT);

        free(leftT);
        free(rightT);

        return mini(leftN, rightN, node->Operator);
    }
    else if (node->left->left == NULL
          && node->left->right == NULL)
    {
        char *text = lexems_to_text(node->left->lexems, node->left->length);
        double n;

        if (text[0] >= 'a' && text[0] <= 'z') 
        {
            n = get_constant(text);

            if (n == -1) 
            {
                printf("\"%s\" is not defined\n", text);
                return (unsigned)-1;
            }
        }
        else n = atof(text);
        
        free(text);

        return mini(n, solve(node->right), node->Operator);
    }
    else if (node->right->left == NULL
          && node->right->right == NULL)
    {
        char *text = lexems_to_text(node->right->lexems, node->right->length);
        double n;

        if (text[0] >= 'a' && text[0] <= 'z') 
        {
            n = get_constant(text);

            if (n == -1) 
            {
                printf("\"%s\" is not defined\n", text);
                return (unsigned)-1;
            }
        }
        else n = atof(text);

        free(text);

        return mini(solve(node->left), n, node->Operator);
    }
    else
        return mini(solve(node->left), solve(node->right), node->Operator);
}