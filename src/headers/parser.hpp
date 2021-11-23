#include <vector>
#include <string>

#include "lexer.hpp"
#include "environment.hpp"

#pragma once

class Node
{
private:
    bool check_brackets();
    void remove_brackets();
    size_t get_priority(Environment env);

public:
    Node(std::vector<Node> nodes, std::vector<Token*> value);
    Node(std::vector<Token*> value);

    std::vector<Node> nodes;
    std::vector<Token*> value;
    std::vector<char> operators;

    void parse(Environment env);
};