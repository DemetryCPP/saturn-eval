#include <vector>
#include <string>
#include <iostream>

#include "parser.hpp"
#include "lexer.hpp"

Node::Node(std::vector<Node> nodes, std::vector<Token> value) : nodes(nodes), value(value) {}
Node::Node(std::vector<Token> value) : value(value) {}

bool Node::check_brackets()
{
    if (this->value[0].value != "(" || this->value[this->value.size() - 1].value != ")")
        return false;

    int brackets = 0;

    for (size_t i = 0; i < this->value.size(); i++)
    {
        Token current = this->value[0];

        if (current.type == Token::Type::Open_Bracket)
            brackets++;
        else if (current.type == Token::Type::Closing_Bracket)
            brackets--;

        if (brackets == 0 && i != this->value.size() - 1)
            return false;
    }

    return true;
}

void Node::parse()
{
    Token::Type separator_type = Token::Type::Null;
    int brackets = 0;

    while (this->check_brackets())
    {
        this->value.erase(this->value.begin());
        this->value.erase(this->value.end());
    }

    for (size_t i = 0; i < this->value.size(); i++)
    {
        Token current = this->value[i];

        if (current.type == Token::Type::Open_Bracket)
            brackets++;
        else if (current.type == Token::Type::Closing_Bracket)
            brackets--;

        if (brackets != 0)
            continue;

        if (current.type == Token::Type::Additive_Operator)
            separator_type = Token::Type::Additive_Operator;
        else if (current.type == Token::Type::Multiplicative_Operator && separator_type != Token::Type::Additive_Operator)
            separator_type = Token::Type::Multiplicative_Operator;
    }

    if (separator_type == Token::Type::Null)
        return;

    std::vector<Token> newvalue;

    brackets = 0;

    for (size_t i = 0; i < this->value.size(); i++)
    {
        Token current = this->value[i];

        if (current.type == Token::Type::Open_Bracket)
            brackets++;
        else if (current.type == Token::Type::Closing_Bracket)
            brackets--;

        if (current.type == separator_type && brackets == 0)
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