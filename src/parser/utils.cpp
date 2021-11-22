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

        if (current->type == Token::Type::Open_Bracket)         brackets++;
        else if (current->type == Token::Type::Closing_Bracket) brackets--;

        if (brackets == 0 && i != this->value.size() - 1)
            return false;
    }

    return true;
}