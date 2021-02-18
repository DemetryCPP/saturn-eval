#include <stdlib.h>

#pragma once

typedef struct Lexem Lexem_s;

struct Lexem
{
    char Data;
    int Type;
};

Lexem_s *new_lexem(char Data, int Type)
{
    Lexem_s *lexem = (Lexem_s*)malloc(sizeof(Lexem_s));
    lexem->Data = Data;
    lexem->Type = Type;
    return lexem;
}
