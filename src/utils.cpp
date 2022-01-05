#include "lexer.hpp"

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