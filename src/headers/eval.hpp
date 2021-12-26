#include <string>
#include <map>
#include "nodes.hpp"
#pragma once

namespace Eval
{
    class Error
    {
    public:
        enum class Type
        {
            UnexpectedToken,
            IsNotAFunction,
            IsNotDefined,
            TooManyArgs,
            TooFewArgs,
        };

        Error(size_t pos, char token, Type type)
            : Error(pos, std::string(1, token), type) {};
        Error(size_t pos, std::string token, Type type)
            : pos(pos)
            , token(token)
            , type(type) {};

        std::string token;
        size_t pos;
        Type type;

    };

    class Function
    {
    public:
        using Action = double (*)(std::vector<double>);

        Function(Action action, size_t argsCount)
            : action(action)
            , argsCount(argsCount) {};

        Action action;
        size_t argsCount;
    };

    class Interpreter
    {
    private:
        double solve(Node::Base *, size_t priority);
        
        double solveNode(Node::Node *, size_t priority);
        double solveFact(Node::Fact *);

        double solveCall(Node::Call *);
        double solveUnary(Node::Unary *);
        double solveLiteral(Node::Literal *);
        double solveBrackets(Node::Brackets *);

        double call(Token *name, std::vector<double> args);
        double get(Token *name);

    public:
        Interpreter(std::map<std::string, double> variables,
                    std::map<std::string, Function *> functions)
            : variables(variables)
            , functions(functions) {};

        std::map<std::string, double> variables;
        std::map<std::string, Function *> functions;

        double eval(std::string);
    };

    inline const std::string version = "5.2.0";
}