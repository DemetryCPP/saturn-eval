#include <vector>
#include <string>
#include <iostream>

#include "parser.hpp"
#include "lexer.hpp"

void Node::parse(Environment env)
{
    if (this->value.size() == 1)
        return;

    this->remove_brackets();
    size_t priority = this->get_priority(env);
    std::vector<Token*> newvalue;
    Token *current = new Token(), *prev;

    int brackets = 0;

    for (size_t i = 0; i < this->value.size(); i++)
    {
        prev = current;
        current = this->value[i];

        if (current->type == Token::Type::Open_Bracket)         brackets++;
        else if (current->type == Token::Type::Closing_Bracket) brackets--;

        if (brackets == 0 && current->type == Token::Type::Operator && env.getOperator(current->value[0]).priority == priority)
        {
            this->nodes.push_back(Node(newvalue));
            this->operators.push_back(current->value[0]);

            newvalue.clear();
        }
        else if (priority == 4 && prev->type == Token::Type::Id && current->type == Token::Type::Open_Bracket)
        {
            this->nodes.push_back(Node(newvalue));
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