#include "lexer.hpp"
#pragma once

namespace Eval::AST
{
    struct Base
    {
        enum class Type
        { Node, Fact } type;
    };

    struct Fact : Base
    {
        enum class Type
        {
            Brackets, Call,
            Literal, Unary,
        } type;

        Fact(Type type) : type(type), Base{Base::Type::Fact} {}
    };

    struct Node : Base
    {
        Node(std::vector<Base *> nodes, std::vector<Operator *> operators)
            : nodes(nodes), operators(operators)
            , Base{Base::Type::Node} {};

        std::vector<Base *> nodes;
        std::vector<Operator *> operators;
    };

    struct Call : Fact
    {
        Call(Token *name, std::vector<Base *> args)
            : name(name), args(args)
            , Fact(Fact::Type::Call) {};

        Token *name;
        std::vector<Base *> args;
    };

    struct Unary : Fact
    {
        Unary(Fact *fact)
            : fact(fact)
            , Fact(Fact::Type::Unary) {};

        Fact *fact;
    };

    struct Literal : Fact
    {
        Literal(Token *token)
            : token(token)
            , Fact(Fact::Type::Literal) {};

        Token *token;
    };

    struct Brackets : Fact
    {
        Brackets(Base *expr)
            : expr(expr)
            , Fact(Fact::Type::Brackets) {};

        Base *expr;
    };
}