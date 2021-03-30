#include <string.h>
#include <stdlib.h>

#include "../headers/lexer_types.h"
#include "../headers/lexer.h"
#include "../headers/solve.h"
#include "../headers/solve_types.h"

Token_s **lexer(char *expression, size_t *tokens_count_ptr, size_t *status, Operator_s **operators)
{
    size_t expression_length = strlen(expression), 
        tokens_count = 0,
        brackets = 0;
    
    Token_s **tokens = (Token_s **)calloc(expression_length, sizeof(Token_s *)), 
        *empty_token = new_token(t_none, '\0');

    for (size_t i = 0; i < expression_length; i++)
    {
        char current = expression[i];
        Tokens_e type = t_none;
        Token_s *last = tokens_count > 0 ? tokens[tokens_count - 1] : empty_token;

        if (current >= '0' && current <= '9')
        {
            if (last->type && last->value != '(' && last->type != t_number && last->type != t_decimal_seporator && last->type != t_operators) 
                *status = 1; 
            type = t_number;
        }
        else if (check_operator(current, operators))
        {
            if (last->type && last->type != t_text && last->type != t_number && last->value != ')' && !(last->type == t_operators && current == '-'))
                *status = 1;
            type = t_operators;
        }
        else if (current == '.')
        {
            if (last->type && last->type != t_number) 
                *status = 1;
            type = t_decimal_seporator;
        }
        else if (current == '(' || current == ')')
        {
            if (last->type && (
                (current == '(' && last->type != t_operators && last->type != t_text && last->value != '(') ||
                (current == ')' && last->type != t_number && last->value != ')' && last->type != t_text))) 
                    *status = 1;

            if (current == '(') brackets++;
            else if (current == ')') brackets--;

            if (brackets < 0) *status = 1;

            type = t_brackets;
        }
        else if ((current >= 'a' && current <= 'z') || (current >= 'A' && current <= 'Z'))
        {
            if (last->type && last->type != t_text && last->type != t_operators && last->value != '(') 
                *status = 1;
            type = t_text;
        }
        else if (current >= 33)
            *status = 1;

        if (*status)
        {
            lexer_unexped_token(current, i);
            *tokens_count_ptr = tokens_count;
            free(empty_token);
            return tokens;
        }

        if (type != t_none)
        {
            tokens[tokens_count] = new_token(type, current);
            // lexer_log(tokens[tokens_count]);
            tokens_count++;
        }
    }

    if (brackets != 0) 
    {
        *status = 1;
        *tokens_count_ptr = tokens_count;
        printf("Expected closed bracket!\n");
        free(empty_token);
        return tokens;
    }

    free(empty_token);
    *tokens_count_ptr = tokens_count;
    tokens = (Token_s **)realloc(tokens, tokens_count * sizeof(Token_s *));
    return tokens;
}