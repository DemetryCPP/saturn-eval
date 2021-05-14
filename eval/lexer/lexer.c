#include <string.h>
#include <stdlib.h>

#include "lexer_types.h"
#include "lexer.h"
#include "solve.h"
#include "solve_types.h"
#include "status.h"

Token_s **lexer(char *expression, size_t *tokens_count_ptr, Status_s *status, Operator_s **operators)
{
    size_t expression_length = strlen(expression), 
        tokens_count = 0,
        brackets = 0;
    
    Token_s **tokens = (Token_s **)malloc(expression_length * sizeof(Token_s *)), 
        *empty_token = new_token(t_none, '\0');

    if (tokens == NULL)
    {
        puts("memory allocation error.");
        exit(1);
    }

    for (size_t i = 0; i < expression_length; i++)
    {
        char current = expression[i];
        Tokens_e type = t_none;
        Token_s *last = tokens_count > 0 ? tokens[tokens_count - 1] : empty_token;

        if (current >= '0' && current <= '9')
        {
            if (last->type && last->value != '(' && last->type != t_number && last->type != t_decimal_seporator && last->type != t_operators) 
                status->code = sc_unexped_token; 
            type = t_number;
        }
        else if (check_operator(current, operators))
        {
            if((last->type == t_none && current != '-')
                || (last->type != t_text
                && last->type != t_number
                && last->value != ')'
                && (current != '-' && (last->type == t_operators || last->value == '(')))
            ) status->code = sc_unexped_token; 

            type = t_operators;
        }
        else if (current == '.')
        {
            if (last->type != t_number) 
                status->code = sc_unexped_token; 
            type = t_decimal_seporator;
        }
        else if (current == '(' || current == ')')
        {
            if ((last->type && current == '(' && last->type != t_operators && last->type != t_text && last->value != '(') ||
                (current == ')' && last->type != t_number && last->value != ')' && last->type != t_text))
                    status->code = sc_unexped_token;

            if (current == '(') brackets++;
            else if (current == ')') brackets--;

            if (brackets < 0) status->code = sc_brackets_error;

            type = t_brackets;
        }
        else if ((current >= 'a' && current <= 'z') || (current >= 'A' && current <= 'Z'))
        {
            if (last->type && last->type != t_text && last->type != t_operators && last->value != '(') 
                status->code = sc_unexped_token; 
            type = t_text;
        }
        else if (current >= 33)
                status->code = sc_unexped_token;

        if (status->code != sc_ok)
        {
            *tokens_count_ptr = tokens_count;
            free(empty_token);
            status->data1 = i;
            status->data3 = current;
            return tokens;
        }

        if (type != t_none)
        {
            tokens[tokens_count] = new_token(type, current);
            tokens_count++;
        }
    }

    if (brackets != 0) 
    {
        status->code = sc_brackets_error;
        *tokens_count_ptr = tokens_count;
        free(empty_token);
        return tokens;
    }

    free(empty_token);
    *tokens_count_ptr = tokens_count;
    tokens = (Token_s **)realloc(tokens, tokens_count * sizeof(Token_s *));

    if (tokens == NULL)
    {
        puts("memory allocation error.");
        exit(1);
    }

    return tokens;
}