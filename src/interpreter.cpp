#include "utils.hpp"
#include "eval.hpp"
#include "parser.hpp"

using namespace std;
using namespace Eval;

double Interpreter::eval(string expr)
{
    Lexer *lexer = new Lexer(expr);
    Parser *parser = new Parser(lexer->tokens);
    return solve(parser->expr(), 1);
}

double Interpreter::solve(Node::Base *node, size_t priority)
{
    if (priority <= Operator::maxPriority)
    {
        auto expr = static_cast<Node::Node *>(node);
        double result = solve(expr->nodes[0], priority + 1);

        for (size_t i = 0; i < expr->operators.size(); i++)
            result = expr->operators[i]->action(result, solve(expr->nodes[i + 1], priority + 1));
        
        return result;
    }
    else
    {
        auto fact = static_cast<Node::Fact *>(node);
        double result;

        switch (fact->type)
        {
        case Node::Fact::Type::Call:
        {
            auto call = static_cast<Node::Call *>(fact);
            
            vector<double> args;
            for (auto &&a : call->args)
                args.push_back(solve(a, 1));

            result = this->call(call->name, args);
            break;
        }

        case Node::Fact::Type::Unary:
        {
            auto unary = static_cast<Node::Unary *>(fact);
            result = -solve(unary->fact, 3);
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
            result = solve(brackets->expr, 1);
            break;
        }
        }
        return result;
    }
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