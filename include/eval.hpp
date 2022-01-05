#include <string>
#include <map>
#include "nodes.hpp"
#pragma once

namespace Eval
{
    using namespace std;

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
            : Error(pos, string(1, token), type) {};
        Error(size_t pos, string token, Type type)
            : pos(pos)
            , token(token)
            , type(type) {};

        string token;
        size_t pos;
        Type type;
    };

    class Function
    {
    public:
        using Action = double (*)(vector<double>);

        Function(Action action, size_t argsCount)
            : action(action)
            , argsCount(argsCount) {};

        Action action;
        size_t argsCount;
    };

    class Interpreter
    {
    private:
        double solve(AST::Base *);
        
        double solveNode(AST::Node *);
        double solveCall(AST::Call *);
        double solveUnary(AST::Unary *);
        double solveLiteral(AST::Literal *);

        double call(Token *name, vector<double> args);
        double get(Token *name);

    public:
        Interpreter(map<string, double> variables,
                    map<string, Function *> functions)
            : variables(variables)
            , functions(functions) {};

        map<string, double> variables;
        map<string, Function *> functions;

        double eval(string);
    };

    inline const string version = "5.2.0";
}