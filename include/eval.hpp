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
        double solve(AST::Base *, size_t priority);
        
        double solveNode(AST::Node *, size_t priority);
        double solveFact(AST::Fact *);

        double solveCall(AST::Call *);
        double solveUnary(AST::Unary *);
        double solveLiteral(AST::Literal *);
        double solveBrackets(AST::Brackets *);

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