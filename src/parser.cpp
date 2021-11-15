#include <vector>
#include <string>
#include <iostream>

#include "parser.hpp"
#include "lexer.hpp"

Node::Node(std::vector<Node> nodes, std::vector<Token> value) : nodes(nodes), value(value) {}
Node::Node(std::vector<Token> value) : value(value) {}

void Node::parse()
{
    Token::Type separator_type = Token::Type::Null;

    for (size_t i = 0; i < this->value.size(); i++)
    {
        Token current = this->value[i];

        if (current.type == Token::Type::Additive_Operator)
        {
            separator_type = Token::Type::Additive_Operator;
            break;
        }
        else if (current.type == Token::Type::Multiplicative_Operator)
            separator_type = Token::Type::Multiplicative_Operator;
    }

    if (separator_type == Token::Type::Null)
        return;

    std::vector<Token> newvalue;

    for (size_t i = 0; i < this->value.size(); i++)
    {
        Token current = this->value[i];

        if (current.type == separator_type)
        {
            this->nodes.push_back(Node(std::vector<Node>(), newvalue));
            this->operators.push_back(current.value[0]);

            newvalue.clear();
        }
        else
            newvalue.push_back(current);
    }

    this->nodes.push_back(Node(std::vector<Node>(), newvalue));

    for (auto &&i : this->nodes)
        i.parse();
}