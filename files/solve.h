#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#pragma once

#include "node.h"
#include "parseint.h"

int mini(int left, int right, char operator)
{
    switch (operator)
    {
        case '+': return left + right;
        case '-': return left - right;
        case '/': return left / right;
        case '*': return left * right;
        case '^': return pow(left, right);
    }
}

int solve(node_s *node)
{
    if (node->left->left == NULL && node->left->right == NULL && node->right->left == NULL && node->right->right == NULL)
    {
        return mini(parseint(node->left->expression), parseint(node->right->expression), node->oper);
    }
    else if (node->left->left == NULL && node->left->right == NULL)
    {
        return mini(parseint(node->left->expression), solve(node->right), node->oper);
    }
    else if (node->right->left == NULL && node->right->right == NULL)
    {
        return mini(solve(node->left), parseint(node->right->expression), node->oper);
    }
    else
    {
        return mini(solve(node->left), solve(node->right), node->oper);
    }
}