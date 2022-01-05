#include "lexer.hpp"
#pragma once

namespace Eval::AST
{
    using namespace std;

    struct Base
    {
        enum class Type
        { 
            Node, Literal,
            Call, Unary,
        } type;
    };

    struct Node : Base
    {
        Node(vector<Base *> nodes, vector<OperatorToken *> operators)
            : nodes(nodes), operators(operators)
            , Base{Base::Type::Node} {};

        vector<Base *> nodes;
        vector<OperatorToken *> operators;
    };

    struct Call : Base
    {
        Call(Token *name, vector<Base *> args)
            : name(name), args(args)
            , Base{Base::Type::Call} {};

        Token *name;
        vector<Base *> args;
    };

    struct Unary : Base
    {
        Unary(Base *fact) : fact(fact)
            , Base{Base::Type::Unary} {};

        Base *fact;
    };

    struct Literal : Base
    {
        Literal(Token *token)
            : token(token)
            , Base{Base::Type::Literal} {};

        Token *token;
    };
}