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

    class Variable
    {
    public:
        Variable(std::string name, double value);

        std::string name;
        double value;
    };

    class UnexpectedToken : public std::invalid_argument 
    {
    public:
        UnexpectedToken(size_t pos, std::string token);

        std::string token;
        size_t pos;
    };

    Environment();
    Environment(std::vector<Environment::Operator> operators,
                std::vector<Environment::Variable> variables);

    std::vector<Environment::Operator> operators;
    std::vector<Environment::Variable> variables;

    Environment::Operator getOperator(char symbol);
    Environment::Variable getVariable(std::string name);

    bool isOperator(char symbol);
    bool isValidVariable(std::string name);

    void stdinit();
};

extern Environment env;