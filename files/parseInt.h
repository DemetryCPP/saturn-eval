#include <stdio.h>

#pragma once

int parseInt(char *str)
{
    int result = 0;
    for (int i = 0; str[i] != 0; i++)
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            int num = str[i] - '0';
            result *= 10;
            result += num;
        }
    }
    return result;
}