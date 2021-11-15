#include <string>
#pragma once

class Token
{
public:
    static bool isNumber(char);
    static std::string toString(std::vector<Token> tokens);

    using Type = enum Type
    {
        Number,
        Additive_Operator,
        Multiplicative_Operator,
        Null
    };

    Token(Token::Type type, std::string value);

    Token::Type type;
    std::string value;

    class Lexer
    {
    private:
        int index = 0;
        
        char current() {
            return this->expression[this->index];
        }

        char previous() {
            return this->expression[this->index - 1];
        }

        char peek() {
            this->index++;
            return this->previous();
        }

    public:
        Lexer(std::string expression);
        
        Token next();
        std::vector<Token> allTokens();

        static void log(Token *token);
        
        std::string expression;
    };
};