#include "nodes.hpp"
#pragma once

namespace Eval::AST
{
    class Parser
    {
    public:
        Parser(std::vector<Token *> tokens) : tokens(tokens) {};

        Node::Base *expr();
        std::vector<Token *> tokens;

    private:
        Base *parse(size_t priority);

        Node *node(size_t priority);
        Base *fact();

        Literal *literal();
        Unary   *unary();
        Call    *call(Token *id);
        Base    *brackets();

        Token *current();
        Token *match(Token::Type);
        Token *match();
        void match(std::string);

        bool checkOperator(size_t priority);
        [[noreturn]] void error();

        size_t index = 0;
    };
}