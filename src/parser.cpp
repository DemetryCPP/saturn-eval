#include <vector>
#include <string>
#include <iostream>

#include "parser.hpp"
#include "lexer.hpp"

Node::Node(std::vector<Node> nodes, std::vector<Token*> value) : nodes(nodes), value(value) {}
Node::Node(std::vector<Token*> value) : value(value) {}

bool Node::check_brackets()
{
    if (this->value[0]->value != "(" || this->value[this->value.size() - 1]->value != ")")
        return false;

    int brackets = 0;

    for (size_t i = 0; i < this->value.size(); i++)
    {
        Token *current = this->value[0];

        if (current->type == Token::Type::Open_Bracket)
            brackets++;
        else if (current->type == Token::Type::Closing_Bracket)
            brackets--;

        if (brackets == 0 && i != this->value.size() - 1)
            return false;
    }

    return true;
}

void Node::parse(Environment env)
{
    int brackets = 0;
    int priority = 4;

    while (this->check_brackets())
    {
        this->value.erase(this->value.begin());
        this->value.erase(this->value.end());
    }

    for (size_t i = 0; i < this->value.size(); i++)
    {
        Token *current = this->value[i];

        if (current->type == Token::Type::Open_Bracket)
            brackets++;
        else if (current->type == Token::Type::Closing_Bracket)
            brackets--;

        if (brackets != 0 || current->type != Token::Type::Operator)
            continue;

        int current_priority = env.getOperator(current->value[0]).priority;

        if (current_priority < priority)
            priority = current_priority;
    }

    if (priority == 4)
        return;

    std::vector<Token*> newvalue;

    brackets = 0;

    for (size_t i = 0; i < this->value.size(); i++)
    {
        Token *current = this->value[i];

        if (current->type == Token::Type::Open_Bracket)
            brackets++;
        else if (current->type == Token::Type::Closing_Bracket)
            brackets--;

        if (current->type == Token::Type::Operator && env.getOperator(current->value[0]).priority == priority && brackets == 0)
        {
            this->nodes.push_back(Node(std::vector<Node>(), newvalue));
            this->operators.push_back(current->value[0]);

            newvalue.clear();
        }
        else
            newvalue.push_back(current);
    }

    this->nodes.push_back(Node(std::vector<Node>(), newvalue));

    for (auto &&i : this->nodes)
        i.parse(env);
}