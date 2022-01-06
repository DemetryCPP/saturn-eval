#include <vector>
#include <string>
#pragma once

class Token
{
public:
    enum class Type
    {
        Operator,
        Special,
        Number,
        Null,
        Id,
    };

    Token(size_t pos) : Token(pos, "", Type::Null) {};
    Token(size_t pos, char value, Type type) 
        : Token(pos, std::string(1, value), type) {};
    Token(size_t pos, std::string value, Type type)
        : pos(pos)
        , value(value)
        , type(type) {};

    size_t pos;
    std::string value;
    Type type;

    void log() const;

    friend bool operator==(Token *, Type);
};

class Lexer
{
public:
    Lexer(std::string expr);

    std::string expr;
    std::vector<Token *> tokens;

private:
    Token *next();

    Token *number();
    Token *single();
    Token *id();

    void skipSpaces();

    char current();
    char match();

    bool isNumber();
    bool isText();

    [[noreturn]] void error();

    size_t index = 0;
};

class OperatorToken : public Token
{
public:
    using Action = double (*)(double a, double b);

    OperatorToken(Action action, size_t pos, char id, size_t priority)
        : action(action)
        , id(id)
        , priority(priority)
        , Token(pos, id, Token::Type::Operator) {};

    size_t priority;
    Action action;
    char id;

    static const size_t maxPriority = 3;
};