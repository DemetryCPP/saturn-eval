#include "utils.hpp"
#include "eval.hpp"
#include "parser.hpp"

using namespace std;
using namespace Eval;
using namespace AST;

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
        case Node::Type::Literal: return solveLiteral(static_cast<Literal *>(node));
        case Node::Type::Unary:   return solveUnary  (static_cast<Unary   *>(node));
        case Node::Type::Node:    return solveNode   (static_cast<Node    *>(node));
        case Node::Type::Call:    return solveCall   (static_cast<Call    *>(node));
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
    if (literal->token->type == Token::Type::Number) 
        return stod(literal->token->value);
    
    return get(literal->token);
}

double Interpreter::call(Token *name, std::vector<double> args)
{
    if (!contains<std::string, Function *>(functions, name->value))
        throw new Error(name->pos, name->value, Eval::Error::Type::IsNotAFunction);

    auto function = functions[name->value];

    if (args.size() > function->argsCount)
        throw new Error(name->pos, name->value, Eval::Error::Type::TooManyArgs);

    if (args.size() < function->argsCount)
        throw new Error(name->pos, name->value, Eval::Error::Type::TooFewArgs);

    return function->action(args);
}

double Interpreter::get(Token *name)
{
    if (!contains<std::string, double>(variables, name->value))
        throw new Error(name->pos, name->value, Error::Type::IsNotDefined);

    return variables[name->value];
}