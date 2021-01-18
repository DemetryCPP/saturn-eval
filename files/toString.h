#include <stdio.h>
#include <stdlib.h>

#pragma once

char* toString(int num)
{
    int digitsCount = 0, i, ornum = num;
    while(num != 0)
    {   
        digitsCount++;
        num /= 10;
    }
    // printf("%d", digitsCount);
    char *str = malloc(digitsCount * sizeof(int));
    num = ornum;
    while (num != 0)
    {
        str[--digitsCount] = (num % 10) + '0';
        num /= 10;
    }
    return str;
}