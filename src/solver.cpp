#include <vector>
#include <string>
#include <iostream>

#include "parser.hpp"
#include "lexer.hpp"
#include "environment.hpp"

double solve(Node node, Environment env)
{
    if (node.operators.size() == 0)
    {
        Token *value = node.value[0];

        if (value->type == Token::Type::Number)
            return std::stod(value->value);

        if (value->type == Token::Type::Id)
            return env.getVariable(value->value).value;
    }

    double result = solve(node.nodes[0], env);

    for (size_t i = 1; i <= node.operators.size(); i++)
        result = env.getOperator(node.operators[i - 1])(result, solve(node.nodes[i], env));

    return result;
}