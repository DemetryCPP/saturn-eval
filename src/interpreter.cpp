#include "utils.hpp"
#include "eval.hpp"
#include "parser.hpp"

using namespace std;
using namespace Eval;

double Interpreter::eval(string expr)
{
    Lexer *lexer = new Lexer(expr);
    Parser *parser = new Parser(lexer->tokens);
    return solveExpr(parser->expr());
}

double Interpreter::solveExpr(Node::Expr *expr)
{
    double result = solveTerm(expr->nodes[0]);

    for (size_t i = 0; i < expr->operators.size(); i++)
    {
        if (expr->operators[i] == "+")
            result += solveTerm(expr->nodes[i + 1]);
        else if (expr->operators[i] == "-")
            result -= solveTerm(expr->nodes[i + 1]);
    }

    return result;
}

double Interpreter::solveTerm(Node::Term *term)
{
    double result = solveFact(term->nodes[0]);

    for (size_t i = 0; i < term->operators.size(); i++)
    {
        if (term->operators[i] == "*")
            result *= solveFact(term->nodes[i + 1]);
        else if (term->operators[i] == "/")
            result /= solveFact(term->nodes[i + 1]);
    }

    return result;
}

double Interpreter::solveFact(Node::Fact *fact)
{
    double result;
    switch (fact->type)
    {
    case Node::Fact::Type::Call:
    {
        auto call = static_cast<Node::Call *>(fact);
        
        std::vector<double> args;
        for (auto &&a : call->args)
            args.push_back(solveExpr(a));

        result = this->call(call->name, args);
        break;
    }

    case Node::Fact::Type::Unary:
    {
        auto unary = static_cast<Node::Unary *>(fact);
        result = -solveFact(unary->fact);
        break;
    }

    case Node::Fact::Type::Literal:
    {
        auto literal = static_cast<Node::Literal *>(fact);

        if (literal->token->type == Token::Type::Number) 
             result = stod(literal->token->value);
        else result = get(literal->token);
        break;
    }

    case Node::Fact::Type::Brackets:
    {
        auto brackets = static_cast<Node::Brackets *>(fact);
        result = solveExpr(brackets->expr);
        break;
    }
    }
    return result;
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