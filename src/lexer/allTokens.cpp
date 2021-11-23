#include <string>
#include <vector>
#include <iostream>

#include "lexer.hpp"
#include "environment.hpp"

std::vector<Token*> Lexer::allTokens()
{
    std::vector<Token*> tokens;
    Token *token = this->next(), 
          *last;
    int brackets = 0;

    if (token->type == Token::Type::Open_Bracket) 
        brackets++;
    
    Token::checkStartValid(token, this->index);

    while (token->type != Token::Type::Null)
    {
        tokens.push_back(token);
        last = token;
        token = this->next();

        Token::checkSameTokens(last, token, index);

        if (token->type == Token::Type::Open_Bracket)
        {
            brackets++;

            Token::checkValidForOpenBracket(last, token, this->index);
        }
        else if (token->type == Token::Type::Closing_Bracket)
        {
            brackets--;

            if (brackets < 0)
                throw Environment::UnexpectedToken(index, token->value);

            Token::checkValidForClosingBracket(last, token, this->index);
        }
    }

    if (brackets > 0)
        throw std::invalid_argument("Unexpected end of input");

    return tokens;
}