#include <iostream>
#include "lexer.hpp"
#include "eval.hpp"

using namespace std;
using enum Eval::Error::Type;

#define COLOR_RED     "\x1b[31m"
#define COLOR_RESET   "\x1b[0m"
#define COLOR_BRIGHT  "\x1b[1m"

void Token::log() const
{
    string types[] = { 
        "[ Operator ]", 
        "[ SpecialC ]",
        "[  Number  ]",
        "[   Null   ]",
        "[    Id    ]" 
    };

    cout << types[(int)type] << " " << value << endl;
};

bool operator==(Token *token, Token::Type type)
{ return token->type == type; }

string Eval::Error::format()
{
    string error;
    auto prefix = COLOR_BRIGHT COLOR_RED "Error at " + to_string(pos) + ": " COLOR_RESET;
    auto token = "\"" + this->token + "\"";

    switch (type)
    {
        case UnexpectedToken: error = "Unexpected token " + token;  break;
        case IsNotAFunction:  error = token + " is not a function"; break;
        case IsNotDefined:    error = token + " is not defined";    break;
        case TooManyArgs:     error = "too many args for " + token; break;
        case TooFewArgs:      error = "too few args for " + token;  break;
    }

    return prefix + error;
}