#include <string>
#include <vector>
#include <iostream>

#include "lexer.hpp"
#include "environment.hpp"

std::vector<Token*> Token::Lexer::allTokens()
{
    std::vector<Token*> tokens;
    Token *token = this->next(), *last;
    int brackets = 0;

    if (token->type == Token::Type::Open_Bracket)
        brackets++;
    else if (token->type == Token::Type::Closing_Bracket || token->type == Token::Type::Operator)
        unexpectedToken(this->index, token);

    while (token->type != Token::Type::Null)
    {
        tokens.push_back(token);
        last = token;
        token = this->next();

        if (token->type == Token::Type::Open_Bracket)
        {
            brackets++;

            if ((last->type != Token::Type::Operator && last->type != Token::Type::Open_Bracket && this->index != 0) 
              && last->type != Token::Type::Closing_Bracket)
                Token::Lexer::unexpectedToken(this->index, token);
        }
        else if (token->type == Token::Type::Closing_Bracket)
        {
            brackets--;

            if ((last->type != Token::Type::Number && last->type != Token::Type::Closing_Bracket) || brackets < 0)
                Token::Lexer::unexpectedToken(this->index, token);

            if (brackets < 0)
                Token::Lexer::unexpectedToken(this->index, token);
        }
        else if (((token->type == Token::Type::Number || token->type == Token::Type::Operator) && last->type == token->type) 
               || (token->type == Token::Type::Operator && last->type == Token::Type::Open_Bracket))
            Token::Lexer::unexpectedToken(this->index, token);
    }

    if (brackets > 0)
        throw std::invalid_argument("Unexpected end of input");

    return tokens;
}