#include "nodes.hpp"
#pragma once

class Parser
{
private:
    Node::Base *parse(size_t priority);

    Node::Brackets *brackets();
    Node::Literal  *literal();
    Node::Unary    *unary();
    Node::Call     *call(Token *id);

    Token *match(Token::Type);
    Token *match();
    void match(std::string);

    Token *current();

    size_t index = 0;

public:
    Parser(std::vector<Token *> tokens);

    Node::Base *expr();
    std::vector<Token *> tokens;
};