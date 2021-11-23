#include <string>
#include "environment.hpp"
#pragma once

class Token
{
public:
    static bool isNumber(char);
    static bool isText(char);

    static void checkStartValid(Token*, size_t index);
    static void checkValidForOpenBracket(Token *last, Token *token, size_t index);
    static void checkValidForClosingBracket(Token *last, Token *token, size_t index);
    static void checkSameTokens(Token *last, Token *token, size_t index);

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