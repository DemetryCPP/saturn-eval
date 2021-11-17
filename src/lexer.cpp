#include <string>
#include <vector>
#include <iostream>

#include "lexer.hpp"

Token::Token(Token::Type type, std::string value) : type(type), value(value){};
Token::Token() : type(Token::Type::Null), value(""){};
Token::Lexer::Lexer(std::string expression) : expression(expression){};

void Token::Lexer::unexpectedToken(size_t pos, Token token)
{
    throw std::invalid_argument(
        std::string(2 + pos - token.value.length(), ' ') +
        "^" + std::string(token.value.length() - 1, '~') +
        "\nUnexpected token \"" + token.value + "\"");
};

bool Token::isNumber(char c)
{
    return c >= '0' && c <= '9';
}

void Token::Lexer::log(Token *token)
{
    std::string type;

    switch (token->type)
    {
    case Token::Type::Number:
        type = "[ NUMBER ]";
        break;

    case Token::Type::Additive_Operator:
        type = "[ ADD_OP ]";
        break;

    case Token::Type::Multiplicative_Operator:
        type = "[ MUL_OP ]";
        break;
    }

    std::cout << type << " " << token->value << std::endl;
}

Token Token::Lexer::next()
{
    if (this->index == this->expression.length())
        return Token(Token::Type::Null, "");

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
                if (isDouble)
                    throw std::invalid_argument(std::string(2 + this->index, ' ') + "^\nUnexpected token '.'");
                else
                    isDouble = true;
        }

        Token newtoken(Token::Type::Number, buffer);

        return Token(Token::Type::Number, buffer);
    }

    Token::Type type;

    switch (this->current())
    {
    case '+':
    case '-':
        type = Token::Type::Additive_Operator;
        break;

    case '*':
    case '/':
        type = Token::Type::Multiplicative_Operator;
        break;

    case '(':
        type = Token::Type::Open_Bracket;
        break;

    case ')':
        type = Token::Type::Closing_Bracket;
        break;
    }

    return Token(type, std::string(1, this->peek()));
}

std::vector<Token> Token::Lexer::allTokens()
{
    std::vector<Token> tokens;
    Token token = this->next();
    Token last;
    int brackets = 0;

    if (token.type == Token::Type::Open_Bracket)
        brackets++;
    else if (token.type == Token::Type::Closing_Bracket 
          || token.type == Token::Type::Additive_Operator 
          || token.type == Token::Type::Multiplicative_Operator)
        unexpectedToken(this->index, token);

    while (token.type != Token::Type::Null)
    {
        tokens.push_back(token);
        last = token;
        token = this->next();

        if (token.type == Token::Type::Open_Bracket) 
        {
            brackets++;

            if ((last.type != Token::Type::Additive_Operator && last.type != Token::Type::Multiplicative_Operator && last.type != Token::Type::Open_Bracket && this->index != 0)
            && last.type != Token::Type::Closing_Bracket)
                Token::Lexer::unexpectedToken(this->index, token);
        }
        else if (token.type == Token::Type::Closing_Bracket)
        {
            brackets--;

            if ((last.type != Token::Type::Number && last.type != Token::Type::Closing_Bracket) || brackets < 0)
                Token::Lexer::unexpectedToken(this->index, token);

            if (brackets < 0)
                Token::Lexer::unexpectedToken(this->index, token);
        } else if (((token.type == Token::Type::Number 
                || token.type == Token::Type::Additive_Operator 
                || token.type == Token::Type::Multiplicative_Operator)
                && last.type == token.type)

                || ((token.type == Token::Type::Additive_Operator
                || token.type == Token::Type::Multiplicative_Operator)
                && last.type == Token::Type::Open_Bracket))
            Token::Lexer::unexpectedToken(this->index, token);
    }

    if (brackets > 0)
        throw std::invalid_argument("Unexpected end of input");

    return tokens;
}