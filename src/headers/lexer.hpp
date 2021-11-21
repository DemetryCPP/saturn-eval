#include <string>
#include "environment.hpp"
#pragma once

class Token
{
public:
    static bool isNumber(char);
    static std::string toString(std::vector<Token> tokens);

    using Type = enum Type
    {
        Number,
        Operator,
        Open_Bracket,
        Closing_Bracket,
        Null
    };

    Token(Token::Type type, std::string value);
    Token();

    Token::Type type;
    std::string value;

    class Lexer
    {
    private:
        int index = 0;
        
        char current();
        char previous();
        char peek();

    public:
        Lexer(std::string expression, Environment env);
        
        Token *next();
        std::vector<Token*> allTokens();

        static void log(Token *token);
        static void unexpectedToken(size_t pos, Token *token);
        
        std::string expression;
        Environment env;
    };
};