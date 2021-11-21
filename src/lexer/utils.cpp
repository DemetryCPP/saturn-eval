#include <string>
#include <vector>
#include <iostream>

#include "lexer.hpp"
#include "environment.hpp"

Token::Token(Token::Type type, std::string value) : type(type), value(value){};
Token::Token() : type(Token::Type::Null), value(""){};
Token::Lexer::Lexer(std::string expression, Environment env) : expression(expression), env(env){};

char Token::Lexer::current() 
{ return this->expression[this->index]; }

char Token::Lexer::previous() 
{ return this->expression[this->index - 1]; }

char Token::Lexer::peek()
{
    this->index++;
    return this->previous();
}

void Token::Lexer::unexpectedToken(size_t pos, Token *token)
{
    throw std::invalid_argument(
        std::string(2 + pos - token->value.length(), ' ') +
        "^" + std::string(token->value.length() - 1, '~') +
        "\nUnexpected token \"" + token->value + "\"");
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
        type = "[  NUMBER  ]";
        break;

    case Token::Type::Operator:
        type = "[ OPERATOR ]";
        break;
    }

    std::cout << type << " " << token->value << std::endl;
}