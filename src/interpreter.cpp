#include "utils.hpp"
#include "eval.hpp"
#include "parser.hpp"

using namespace std;
using namespace Eval;
using namespace AST;

using enum Error::Type;

using T = Token::Type;
using E = AST::Base::Type;

double Interpreter::eval(string expr)
{
    auto lexer = new Lexer(expr);
    auto parser = new Parser(lexer->tokens);
    return solve(parser->expr());
}

double Interpreter::solve(Base *node)
{
    switch (node->type)
    {
        case E::Literal: return solveLiteral(static_cast<Literal *>(node));
        case E::Unary:   return solveUnary  (static_cast<Unary   *>(node));
        case E::Node:    return solveNode   (static_cast<Node    *>(node));
        case E::Call:    return solveCall   (static_cast<Call    *>(node));
    }
}

double Interpreter::solveNode(Node *expr)
{
    double result = solve(expr->nodes[0]);

    for (size_t i = 0; i < expr->operators.size(); i++)
        result = expr->operators[i]->action(result, solve(expr->nodes[i + 1]));

    return result;
}

double Interpreter::solveCall(Call *call)
{
    vector<double> args;
    for (auto &&a : call->args)
        args.push_back(solve(a));

    return this->call(call->name, args);
}

double Interpreter::solveUnary(Unary *unary)
{ return -solve(unary->fact); }

double Interpreter::solveLiteral(Literal *literal)
{
    if (literal->token->type == T::Number)
        return stod(literal->token->value);
    
    return get(literal->token);
}

double Interpreter::call(Token *name, vector<double> args)
{
    if (!contains<string, Function *>(functions, name->value))
        throw new Error(name->pos, name->value, IsNotAFunction);

    auto function = functions[name->value];

    if (args.size() > function->argsCount) throw new Error(name->pos, name->value, TooManyArgs);
    if (args.size() < function->argsCount) throw new Error(name->pos, name->value, TooFewArgs);

    return function->action(args);
}

double Interpreter::get(Token *name)
{
    if (!contains<string, double>(variables, name->value))
        throw new Error(name->pos, name->value, IsNotDefined);

    return variables[name->value];
}