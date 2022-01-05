#include "lexer.hpp"
#pragma once

namespace Eval::AST
{
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
        Node(std::vector<Base *> nodes, std::vector<Operator *> operators)
            : nodes(nodes), operators(operators)
            , Base{Base::Type::Node} {};

        std::vector<Base *> nodes;
        std::vector<Operator *> operators;
    };

    struct Call : Base
    {
        Call(Token *name, std::vector<Base *> args)
            : name(name), args(args)
            , Base{Base::Type::Call} {};

        Token *name;
        std::vector<Base *> args;
    };

    struct Unary : Base
    {
        Unary(Base *fact)
            : fact(fact)
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