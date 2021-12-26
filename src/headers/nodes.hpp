#include "lexer.hpp"
#pragma once

namespace Node
{
    class Base
    {
    public:
        enum class Type
        { Node, Fact };
        
        Base(Type type) : type(type) {};

        Type type;
    };

    class Fact : public Base
    {
    public:
        enum class Type
        {
            Brackets, Call,
            Literal, Unary,
        };

        Fact(Type type)
            : type(type)
            , Base(Base::Type::Fact) {};

        Type type;
    };

    class Node : public Base
    {
    public:
        Node(std::vector<Base *> nodes, std::vector<Operator *> operators)
            : nodes(nodes)
            , operators(operators)
            , Base(Base::Type::Node) {};

        std::vector<Base *> nodes;
        std::vector<Operator *> operators;
    };

    class Call : public Fact
    {
    public:
        Call(Token *name, std::vector<Base *> args)
            : name(name)
            , args(args)
            , Fact(Fact::Type::Call) {};

        Token *name;
        std::vector<Base *> args;
    };

    class Unary : public Fact
    {
    public:
        Unary(Fact *fact)
            : fact(fact)
            , Fact(Fact::Type::Unary) {};

        Fact *fact;
    };

    class Literal : public Fact
    {
    public:
        Literal(Token *token)
            : token(token)
            , Fact(Fact::Type::Literal) {};

        Token *token;
    };

    class Brackets : public Fact
    {
    public:
        Brackets(Base *expr)
            : expr(expr)
            , Fact(Fact::Type::Brackets) {};

        Base *expr;
    };
}