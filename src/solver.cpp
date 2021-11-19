#include <vector>
#include <string>

#include "parser.hpp"
#include "lexer.hpp"
#include "environment.hpp"

double solve(Node node, Environment env)
{
    if (node.operators.size() == 0)
        return std::stod(node.value[0].value);

    double result = solve(node.nodes[0], env);

    for (size_t i = 1; i <= node.operators.size(); i++)
        result = env.getOperator(node.operators[i - 1])(result, solve(node.nodes[i], env));

    return result;
}