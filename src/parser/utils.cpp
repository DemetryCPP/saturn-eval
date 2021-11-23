#include <vector>
#include <string>
#include <iostream>

#include "parser.hpp"
#include "lexer.hpp"

Node::Node(std::vector<Node> nodes, std::vector<Token*> value) : nodes(nodes), value(value) {}
Node::Node(std::vector<Token*> value) : value(value) {}

bool Node::check_brackets()
{
    if (this->value[0]->type != Token::Type::Open_Bracket 
     || this->value[this->value.size() - 1]->type != Token::Type::Closing_Bracket)
        return false;

    int brackets = 0;

    for (size_t i = 0; i < this->value.size(); i++)
    {
        Token *current = this->value[i];

        if (current->type == Token::Type::Open_Bracket)         brackets++;
        else if (current->type == Token::Type::Closing_Bracket) brackets--;

        if (brackets == 0 && i != this->value.size() - 1)
            return false;
    }

    return true;
}

void Node::remove_brackets()
{
    while (this->check_brackets())
    {
        this->value.erase(this->value.begin());
        this->value.erase(this->value.end() - 1);
    }
}

size_t Node::get_priority(Environment env)
{
    int brackets = 0, priority = 4;

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

    return priority;
}