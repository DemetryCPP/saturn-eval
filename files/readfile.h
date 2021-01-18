#include <stdio.h>
#include <stdlib.h>

#pragma once

void readFile(char *text)
{
    FILE *fptr = fopen("./expression.txt", "r");
    if (fptr == NULL)
    {
        printf("error at open file.");
        exit(1);
    }
    fgets(text, 100, fptr);
    fclose(fptr);
}