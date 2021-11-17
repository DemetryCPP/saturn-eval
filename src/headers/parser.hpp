#include <vector>
#include <string>

#include "lexer.hpp"

#pragma once

class Node
{
private:
    bool check_brackets();

public:
    Node(std::vector<Node> nodes, std::vector<Token> value);
    Node(std::vector<Token> value);

    std::vector<Node> nodes;
    std::vector<Token> value;
    std::vector<char> operators;

    void parse();
};