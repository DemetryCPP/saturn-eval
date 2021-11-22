#include <string>
#include "environment.hpp"
#pragma once

class Token
{
public:
    static bool isNumber(char);
    static bool isText(char);

    enum Type
    {
        Closing_Bracket,
        Open_Bracket,
        Operator,
        Number,
        Null,
        Id
    };

    Token(Token::Type type, std::string value);
    Token();

    Token::Type type;
    std::string value;

    void log();
};

class Lexer
{
private:
    size_t index = 0;
    
    char current();
    char previous();
    char peek();

public:
    Lexer(std::string expression, Environment env);

    Token *next();
    std::vector<Token*> allTokens();

    std::string expression;
    Environment env;
};