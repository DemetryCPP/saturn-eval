#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "files/readfile.h"
#include "files/getPosDivider.h"
#include "files/node.h"
#include "files/parse.h"
#include "files/delete_spaces.h"
#include "files/parseInt.h"
#include "files/solve.h"
#include "files/getVoidNode.h"
#include "files/parseInt.h"
#include "files/toString.h"

int main() 
{
    char text[100];
    fgets(text, 100, stdin);

    node_s head;
    head.expression = text;

    for (head.length = 0; head.length < 100; head.length++)
    {
        if (text[head.length] == ';' || text[head.length] == '\0') break;
        head.expression[head.length] = text[head.length];
    }

    delete_spaces(&head);
    printf("read: '%s'\n\n", head.expression);
    parse(&head);
    printf("\n");
    printf("result: %d\n", solve(&head));
}