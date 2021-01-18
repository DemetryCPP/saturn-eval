#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "files/node.h"
#include "files/parse.h"
#include "files/deletespaces.h"
#include "files/parseint.h"
#include "files/solve.h"

int main() 
{
    char expression[100];
    printf("write expression: ");
    fgets(expression, 100, stdin);

    node_s head;
    head.expression = expression;

    for (head.length = 0; head.length < 100; head.length++)
    {
        if (expression[head.length] == '\n' || expression[head.length] == '\0') break;
        head.expression[head.length] = expression[head.length];
    }

    deletespaces(&head);
    printf("read: '%s'\n", head.expression);
    parse(&head);
    printf("result: %d\n", solve(&head));
}