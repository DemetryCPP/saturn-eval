#include <string>
#include <vector>
#include <iostream>

#include "lexer.hpp"
#include "environment.hpp"

Token *Lexer::next()
{
    // if end of expression return null token
    if (this->index == this->expression.length())
        return new Token(Token::Type::Null, "");

    // skip whitespaces
    while (this->current() <= 32)
        this->index++;

    std::string buffer;

    // check number
    if (Token::isNumber(this->current()))
    {
        bool isDouble = false;

        while (Token::isNumber(this->current()) || this->current() == '.')
        {
            buffer += this->peek();

            if (this->current() == '.')
                if (isDouble) throw Environment::UnexpectedToken(this->index, ".");
                else isDouble = true;
        }

        return new Token(Token::Type::Number, buffer);
    }

    // variables
    if (Token::isText(this->current()))
    {
        while (Token::isText(this->current()))
            buffer += this->peek();

        return new Token(Token::Type::Id, buffer);
    }

    // all one-char tokens
    Token::Type type;

    if (this->env.isOperator(this->current()))  type = Token::Type::Operator;
    else if (this->current() == '(')            type = Token::Type::Open_Bracket;
    else if (this->current() == ')')            type = Token::Type::Closing_Bracket;

    return new Token(type, std::string(1, this->peek()));
}