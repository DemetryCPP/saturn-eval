#include "lexer.hpp"
#pragma once

namespace Node
{
    class Fact
    {
    public:
        enum class Type
        {
            Brackets,
            Literal,
            Unary,
            Call,
        };

        Fact(Type type) : type(type) {};

        Type type;
    };

    class Term
    {
    public:
        Term(std::vector<Fact *> nodes, std::vector<std::string> operators)
            : nodes(nodes)
            , operators(operators) {};

        std::vector<Fact *> nodes;
        std::vector<std::string> operators;
    };

    class Expr
    {
    public:
        Expr(std::vector<Term *> nodes, std::vector<std::string> operators)
            : nodes(nodes)
            , operators(operators) {};

        std::vector<Term *> nodes;
        std::vector<std::string> operators;
    };

    class Call : public Fact
    {
    public:
        Call(Token *name, std::vector<Expr *> args)
            : name(name)
            , args(args)
            , Fact(Fact::Type::Call) {};

        Token *name;
        std::vector<Expr *> args;
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
        Brackets(Expr *expr)
            : expr(expr)
            , Fact(Fact::Type::Brackets) {};

        Expr *expr;
    };
}