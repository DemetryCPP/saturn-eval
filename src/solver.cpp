#include <vector>
#include <string>

#include "parser.hpp"
#include "lexer.hpp"

double solve(Node node)
{
    if (node.operators.size() == 0)
        return std::stof(node.value[0].value);

    double result = solve(node.nodes[0]);

    for (size_t i = 1; i <= node.operators.size(); i++)
    {
        switch (node.operators[i - 1])
        {
        case '+':
            result += solve(node.nodes[i]);
            break;

        case '-':
            result -= solve(node.nodes[i]);
            break;

        case '*':
            result *= solve(node.nodes[i]);
            break;

        case '/':
            result /= solve(node.nodes[i]);
            break;
        }
    }

    return result;
}