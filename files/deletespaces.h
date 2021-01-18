#include <stdio.h>
#include <stdlib.h>

#pragma once

#include "node.h"

void deletespaces(node_s *node)
{
    int nospaces = 0, counter = 0;

    for (int i = 0; i < node->length; i++)
    {
        if (node->expression[i] == ' ') continue;
        nospaces++;
    }  

    for (int i = 0; i < node->length; i++)
    {
        if (node->expression[i] == ' ') continue;
        node->expression[counter++] = node->expression[i];
    }
    node->expression[counter] = '\0';
    node->length = nospaces;
}