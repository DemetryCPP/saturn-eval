#include <stdio.h>
#include <stdlib.h>

#pragma once

struct node
{
    char *expression;
    char oper;
    size_t length;
    struct node *left;
    struct node *right;
};

typedef struct node node_s;