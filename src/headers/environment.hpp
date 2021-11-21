#include <vector>
#include <stdexcept>
#pragma once

class Environment
{
public:
    class Operator
    {
    public:
        using Action_t = double (*)(double a, double b);

        Operator(size_t priority, char symbol, Environment::Operator::Action_t action);
        Operator();

        size_t priority;
        char symbol;
        Action_t action;

        double operator()(double a, double b);
    };

    class UnexpectedToken : public std::invalid_argument 
    {
    public:
        UnexpectedToken(size_t pos, std::string token);

        std::string token;
        size_t pos;
    };

    Environment(std::vector<Environment::Operator> operators);
    std::vector<Environment::Operator> operators;

    Environment::Operator getOperator(char symbol);
    bool isOperator(char symbol);

    void stdinit();
};

extern Environment env;