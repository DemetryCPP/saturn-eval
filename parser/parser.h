#include <stdio.h>
#include <stdlib.h>

#pragma once

#include "../lexer/data.h"
#include "data.h"
#include "find_divider_pos.h"

void parser(Node_s *node)
{        
    node->divider_pos = find_divider_pos(node->lexems, node->length);

    if (node->divider_pos == -1)
    {
        if (node->lexems[0]->Data == '(' && node->lexems[node->length - 1]->Data == ')')
        {
            while (node->divider_pos == -1)
            {
                if (node->lexems[0]->Data == '(' && node->lexems[node->length - 1]->Data == ')') 
                {
                    node->lexems++;
                    node->length -= 2;
                    node->divider_pos = find_divider_pos(node->lexems, node->length);
                }
                else break;
            }
        } 
        else
        {
            node->left = NULL;
            node->right = NULL;
            return;
        }
    }

    node->left = (Node_s *)malloc(sizeof(Node_s));
    node->right = (Node_s *)malloc(sizeof(Node_s));

    node->Operator = node->lexems[node->divider_pos]->Data;
    
    node->left = (Node_s *)malloc(sizeof(Node_s));
    node->right = (Node_s *)malloc(sizeof(Node_s));

    node->left->lexems = node->lexems;
    node->right->lexems = node->lexems + (node->divider_pos + 1);

    node->left->length = node->divider_pos;
    node->right->length = node->length - node->divider_pos - 1;


    // printf("pos: %ld; left length: %ld; right length: %ld\n", node->divider_pos, node->left->length, node->right->length);

    char *t = lexems_to_text(node->lexems, node->length);
    char *leftT = lexems_to_text(node->left->lexems, node->left->length);
    char *rightT = lexems_to_text(node->right->lexems, node->right->length);

    printf("%s: '%s' '%c' '%s'\n", t, leftT, node->Operator, rightT);

    free(t);
    free(leftT);
    free(rightT);

    parser(node->left);
    parser(node->right);
}