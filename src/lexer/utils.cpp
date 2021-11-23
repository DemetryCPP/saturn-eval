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
{ return c >= '0' && c <= '9' || c == '.'; }

bool Token::isText(char c) 
{ return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'); }


void Token::checkStartValid(Token *token, size_t index)
{ 
    if (token->type == Token::Type::Closing_Bracket 
     || token->type == Token::Type::Operator)
        throw Environment::UnexpectedToken(index, token->value);
}

void Token::checkValidForOpenBracket(Token *last, Token *token, size_t index)
{
    if (last->type != Token::Type::Operator 
     && last->type != Token::Type::Open_Bracket 
     && last->type != Token::Type::Id)
        throw Environment::UnexpectedToken(index, token->value);
}

void Token::checkValidForClosingBracket(Token *last, Token *token, size_t index)
{
    if (last->type != Token::Type::Number 
     && last->type != Token::Type::Id 
     && last->type != Token::Type::Closing_Bracket)
        throw Environment::UnexpectedToken(index, token->value);
}

void Token::checkSameTokens(Token *last, Token *token, size_t index)
{
    if (((token->type == Token::Type::Number 
       || token->type == Token::Type::Id 
       || token->type == Token::Type::Operator) 
       && last->type == token->type))
        throw Environment::UnexpectedToken(index, token->value);
}


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
    
    case Token::Type::Id:
        type = "[    ID    ]";
        break;
    }

    std::cout << type << " " << this->value << std::endl;
}