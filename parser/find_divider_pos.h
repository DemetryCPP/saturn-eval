#include <stdio.h>
#include <stdlib.h>

#pragma once

#include "../lexer/data.h"

size_t find_divider_pos(Lexem_s **lexems, size_t length)
{
    size_t position = -1;

    for (int i = 0; i < length; i++)
    {
        Lexem_s *current = lexems[i];

        if (current->Type != 3) continue;
        
        if (current->Data == '+' || current->Data == '-') return i;
        else if (current->Data == '/' || current->Data == '*') position = i;
    }

    return position;
}