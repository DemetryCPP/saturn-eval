#include <stdlib.h>
#include <stdio.h>

#pragma once

#include "getposdivider.h"

void parse(node_s *node)
{  
    size_t pos = getposdivider(node->expression, node->length);

    if (pos == 100) {
        node->left = NULL;
        node->right = NULL;        
        return;
    }

    node->left = (node_s*)malloc(sizeof(node_s));
    node->right = (node_s*)malloc(sizeof(node_s));

    node->oper = node->expression[pos];
    
    node->left->expression = malloc(pos * sizeof(char));
    node->right->expression = malloc((node->length - pos) * sizeof(char));
    
    node->left->length = pos;
    node->right->length = node->length - pos;

    for (int i = 0; i < pos; i++) node->left->expression[i] = node->expression[i];
    for (int i = pos + 1; i < node->length; i++) node->right->expression[i - pos - 1] = node->expression[i];

    parse(node->left);
    parse(node->right);
}