#include <stdlib.h>

#pragma once

#include "../lexer/utils.h"
#include "../operators.h"

size_t find_divider_pos(Token_s **tokens, size_t tokens_count, Operator_s **operators, size_t *status)
{
    short priority = 4;
    size_t pos = -1;
    int brackets = 0;

    for (size_t i = tokens_count - 1; i + 1 > 0; i--) // пройтись по токенам с конца
    {
        Token_s *current = tokens[i]; // текущий токен

        if (current->type == t_brackets) // проверка на скобки
        {
            if (current->value == '(') brackets++; // если открывающаяся - инкреминтируем количество не закрытых скобок
            else if (current->value == ')') brackets--; // иначе дикреминтируем

            continue; // переходим к следующей итерации цикла
        }
        else if (current->type != t_operators) continue; // если текущий токен не оператор пофакту, скипаем его

        short current_priority = get_priority(current->value, operators); // получить приоритет оператора

        if (current_priority < priority) // если общий минимальный приоритет в выражении
        {
            pos = i; // установить текущую позицию
            priority = current_priority; // записать другую общий приоритет
        }
    }

    if (brackets != 0) 
    {
        *status = 1;
        printf("Brackets error!\n");
        return -1;
    }

    return pos;
}