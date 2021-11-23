#include <vector>
#include <string>
#include <iostream>

#include "parser.hpp"
#include "lexer.hpp"

void Node::parse(Environment env)
{
    if (this->value.size() == 1)
        return;

    int brackets = 0, priority = 4;

    while (this->check_brackets())
    {
        this->value.erase(this->value.begin());
        this->value.erase(this->value.end() - 1);
    }

    for (size_t i = 0; i < this->value.size(); i++)
    {
        Token *current = this->value[i];

        if (current->type == Token::Type::Open_Bracket)         brackets++;
        else if (current->type == Token::Type::Closing_Bracket) brackets--;

        if (brackets != 0 || current->type != Token::Type::Operator)
            continue;

        size_t current_priority = env.getOperator(current->value[0]).priority;

        if (current_priority < priority)
            priority = current_priority;
    }

    std::vector<Token*> newvalue;

    Token *current = new Token();
    Token *prev;

    for (size_t i = 0; i < this->value.size(); i++)
    {
        prev = current;
        current = this->value[i];

        if (current->type == Token::Type::Open_Bracket)
            brackets++;
        else if (current->type == Token::Type::Closing_Bracket)
            brackets--;

        if (brackets == 0 && current->type == Token::Type::Operator && env.getOperator(current->value[0]).priority == priority)
        {
            this->nodes.push_back(Node(std::vector<Node>(), newvalue));
            this->operators.push_back(current->value[0]);

            newvalue.clear();
        }
        else if (priority == 4 && prev->type == Token::Type::Id && current->type == Token::Type::Open_Bracket)
        {
            this->nodes.push_back(Node(std::vector<Node>(), newvalue));
            this->operators.push_back('f');

            newvalue.clear();
            newvalue.push_back(current);
        }
        else
            newvalue.push_back(current);
    }

    this->nodes.push_back(Node(std::vector<Node>(), newvalue));

    for (auto &&i : this->nodes)
        i.parse(env);
}