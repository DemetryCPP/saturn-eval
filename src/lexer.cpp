#include <iostream>
#include <cmath>

#include "lexer.hpp"
#include "utils.hpp"
#include "eval.hpp"

using namespace std;
using enum Token::Type;

Lexer::Lexer(string expr) : expr(expr)
{
    Token *newToken = next();
    while (newToken != Null)
    {
        tokens.push_back(newToken);
        // newToken->log();
        newToken = next();
    }
};

Token *Lexer::next()
{
    if (index >= expr.length())
        return new Token(index);

    skipSpaces();

    if (isNumber()) return number();
    if (isText())   return id();

    return single();
}

Token *Lexer::number()
{
    bool isDouble = false;
    string buffer;
    buffer += match();
    size_t pos = index;

    while (isNumber())
    {
        if (current() == '.')
            if (isDouble) error();
            else isDouble = true;

        buffer += match(); 
    }

    return new Token(pos, buffer, Number);
}

#define o_case(id, action, priority) case id: return new OperatorToken([](double a, double b) {return action;}, index, match(), priority)

Token *Lexer::single()
{
    if (contains(enlist("(),"), current()))
        return new Token(index, match(), Special);
    
    switch (current())
    {
        o_case('+', a + b, 1);
        o_case('-', a - b, 1);
        o_case('*', a * b, 2);
        o_case('/', a / b, 2);

        o_case('\\', floor(a / b), 2);
        o_case('%', a - b * floor(a / b), 2);

        o_case('^', pow(a, b), 3);
    }

    error();
}

Token *Lexer::id()
{
    string buffer;
    buffer += match();
    size_t pos = index;

    while (isText())
        buffer += match();

    return new Token(pos, buffer, Id);
}

void Lexer::skipSpaces()
{ while (isVoid()) match(); }

char Lexer::current()
{ return expr[index]; }

char Lexer::match()
{ return expr[index++]; }

bool Lexer::isNumber()
{
    return current() >= '0'
        && current() <= '9'
        || current() == '.';
}

bool Lexer::isText()
{
    return current() >= 'a'
        && current() <= 'z'
        || current() >= 'A'
        && current() <= 'Z';
}

bool Lexer::isVoid()
{ return current() <= ' '; }

void Lexer::error()
{ throw new Eval::Error(index, current(), Eval::Error::Type::UnexpectedToken); }