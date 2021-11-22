#include <string>
#include <vector>
#include <iostream>

#include "lexer.hpp"
#include "environment.hpp"

Token::Token(Token::Type type, std::string value) : type(type), value(value){};
Token::Token() : type(Token::Type::Null), value(""){};
Lexer::Lexer(std::string expression, Environment env) : expression(expression), env(env){};

char Lexer::current() 
{ return this->expression[this->index]; }

char Lexer::previous() 
{ return this->expression[this->index - 1]; }

bool Token::isNumber(char c)
{ return c >= '0' && c <= '9'; }

bool Token::isText(char c) 
{ return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'); }

char Lexer::peek()
{
    this->index++;
    return this->previous();
}

void Token::log()
{
    std::string type;

    switch (this->type)
    {
    case Token::Type::Number:
        type = "[  NUMBER  ]";
        break;

    case Token::Type::Operator:
        type = "[ OPERATOR ]";
        break;

    case Token::Type::Closing_Bracket:
        type = "[ CLOS_BRK ]";
        break;

    case Token::Type::Open_Bracket:
        type = "[ OPEN_BRK ]";
        break;
    }

    std::cout << type << " " << this->value << std::endl;
}