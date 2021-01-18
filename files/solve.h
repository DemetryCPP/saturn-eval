#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#pragma once

#include "node.h"
#include "getVoidNode.h"
#include "parseInt.h"

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
        return mini(parseInt(node->left->expression), parseInt(node->right->expression), node->oper);
    }
    else if (node->left->left == NULL && node->left->right == NULL)
    {
        return mini(parseInt(node->left->expression), solve(node->right), node->oper);
    }
    else if (node->right->left == NULL && node->right->right == NULL)
    {
        return mini(solve(node->left), parseInt(node->right->expression), node->oper);
    }
    else
    {
        return mini(solve(node->left), solve(node->right), node->oper);
    }
}