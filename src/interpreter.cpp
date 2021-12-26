#include "utils.hpp"
#include "eval.hpp"
#include "parser.hpp"

using namespace std;
using namespace Eval;

double Interpreter::eval(string expr)
{
    auto lexer = new Lexer(expr);
    auto parser = new Parser(lexer->tokens);
    return solve(parser->expr(), 1);
}

double Interpreter::solve(Node::Base *node, size_t priority)
{
    if (priority == Operator::maxPriority + 1)
        return solveFact(static_cast<Node::Fact *>(node));

    return solveNode(static_cast<Node::Node *>(node), priority);
}

double Interpreter::solveNode(Node::Node *expr, size_t priority)
{
    double result = solve(expr->nodes[0], priority + 1);

    for (size_t i = 0; i < expr->operators.size(); i++)
        result = expr->operators[i]->action(result, solve(expr->nodes[i + 1], priority + 1));

    return result;
}

double Interpreter::solveFact(Node::Fact *fact)
{
    switch (fact->type)
    {
        case Node::Fact::Type::Call: return solveCall(static_cast<Node::Call *>(fact));
        case Node::Fact::Type::Unary: return solveUnary(static_cast<Node::Unary *>(fact));
        case Node::Fact::Type::Literal: return solveLiteral(static_cast<Node::Literal *>(fact));
        case Node::Fact::Type::Brackets: return solveBrackets(static_cast<Node::Brackets *>(fact));
    }
}

double Interpreter::solveCall(Node::Call *call)
{
    vector<double> args;
    for (auto &&a : call->args)
        args.push_back(solve(a, 1));

    return this->call(call->name, args);
}

double Interpreter::solveUnary(Node::Unary *unary)
{ return -solveFact(unary->fact); }

double Interpreter::solveLiteral(Node::Literal *literal)
{
    if (literal->token->type == Token::Type::Number) 
        return stod(literal->token->value);
    
    return get(literal->token);
}

double Interpreter::solveBrackets(Node::Brackets *brackets)
{ return solve(brackets->expr, 1); }

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