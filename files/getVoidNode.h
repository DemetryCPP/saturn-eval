#include <stdio.h>

#pragma once

#include "node.h"

node_s *getVoidNodeLeft(node_s *node)
{
    if (node->left->left == NULL && node->right->left == NULL && node->left->right == NULL && node->right->right == NULL) return node;
    if (node->left->right == NULL && node->left->left) return NULL;
    return getVoidNodeLeft(node->left);
}

node_s *getVoidNodeRight(node_s *node)
{
    if (node->left->left == NULL && node->right->left == NULL && node->left->right == NULL && node->right->right == NULL) return node;
    if (node->right->right == NULL && node->right->left) return NULL;
    return getVoidNodeRight(node->right);
}