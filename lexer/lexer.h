#include <stdio.h>
#include <stdlib.h>

#pragma once

#include "data.h"

/*
    0 - Number
    1 - Decimal Seporator
    2 - Operator
    3 - Bracket
*/

void lexer_info_log(Lexem_s *lexem)
{
    switch (lexem->Type) {
        case 1: printf("[      Number      ]"); break;
        case 2: printf("[ DecimalSeporator ]"); break;
        case 3: printf("[     Operator     ]"); break;
        case 4: printf("[     Brackets     ]"); break;
    }

    printf(" '%c'\n", lexem->Data);
}

Lexem_s **lexer(char *expression, size_t *lexemsLength)
{
    int length, lexemsCount = 0;
    for (length = 0; expression[length] != '\0'; length++);

    Lexem_s **lexems = (Lexem_s**)malloc(length * sizeof(Lexem_s*));

    for (int i = 0; expression[i] != '\0'; i++)
    {
        char current = expression[i];
        int type = 0;

        if (current >= '0' && current <= '9')           type = 1;
        else if (current == '.')                        type = 2;
        else if (current == '+' || current == '-' ||
                 current == '*' || current == '/')      type = 3;
        else if (current == '(' || current == ')')      type = 4;

        if (type)
        {
            Lexem_s *newLexem = (Lexem_s*)malloc(sizeof(Lexem_s));
            newLexem = new_lexem(current, type);
            lexer_info_log(newLexem);
            lexems[lexemsCount++] = newLexem;
        }
    }

    *lexemsLength = lexemsCount;
    lexems = realloc(lexems, lexemsCount * sizeof(Lexem_s*));
    return lexems;
}
