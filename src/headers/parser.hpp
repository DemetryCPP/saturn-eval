#include "nodes.hpp"
#pragma once

class Parser
{
private:
    Node::Base *parse(size_t priority);

    Node::Node *node(size_t priority);
    Node::Fact *fact();

    Node::Brackets *brackets();
    Node::Literal  *literal();
    Node::Unary    *unary();
    Node::Call     *call(Token *id);

    Token *current();
    Token *match(Token::Type);
    Token *match();
    void match(std::string);

    bool checkOperator(size_t priority);
    void error();

    size_t index = 0;


public:
    Parser(std::vector<Token *> tokens) : tokens(tokens) {};

    Node::Base *expr();
    std::vector<Token *> tokens;
};