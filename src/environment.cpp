#include <vector>
#include <cmath>
#include <stdexcept>

#include "environment.hpp"

Environment::Operator::Operator() : symbol('\0'){}
Environment::Environment(std::vector<Environment::Operator> operators) : operators(operators){}

Environment::Operator::Operator(size_t priority, char symbol, Environment::Operator::Action_t action)
    : priority(priority), symbol(symbol), action(action){};

Environment::UnexpectedToken::UnexpectedToken(size_t pos, std::string token) 
    : invalid_argument("Unexpected token '" + token + "' at " + std::to_string(pos)), pos(pos), token(token) {};

double Environment::Operator::operator()(double a, double b)
{ return this->action(a, b); }

bool Environment::isOperator(char symbol)
{ return this->getOperator(symbol).symbol != '\0'; }

Environment::Operator Environment::getOperator(char symbol)
{
    for (auto &&o : this->operators)
        if (o.symbol == symbol)
            return o;

    return Environment::Operator();
}

Environment env{std::vector<Environment::Operator>()};

void Environment::stdinit()
{
    this->operators.push_back(Environment::Operator(1, '+', [](double a, double b) { return a + b; }));
    this->operators.push_back(Environment::Operator(1, '-', [](double a, double b) { return a - b; }));

    this->operators.push_back(Environment::Operator(2, '*', [](double a, double b) { return a * b; }));
    this->operators.push_back(Environment::Operator(2, '/', [](double a, double b) { return a / b; }));
    this->operators.push_back(Environment::Operator(2,'\\', [](double a, double b) { return (a - fmod(a, b)) / b; }));
    this->operators.push_back(Environment::Operator(2, '%', fmod));

    this->operators.push_back(Environment::Operator(3, '^', pow));
}