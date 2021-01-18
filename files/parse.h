#include <stdlib.h>
#include <stdio.h>

#pragma once

void parse(node_s *node)
{  
    size_t pos = getPosDivider(node->expression, node->length);

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
    for (int i = pos + 1; i < node->length; i++) 
    {
        node->right->expression[i - pos - 1] = node->expression[i];
    }
    printf("%s = (left: '%s', operator: '%c', right: '%s')\n", node->expression, node->left->expression, node->oper, node->right->expression);

    parse(node->left);
    parse(node->right);
}