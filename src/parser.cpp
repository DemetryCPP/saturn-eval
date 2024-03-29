#include "utils.hpp"
#include "parser.hpp"
#include "eval.hpp"

using namespace std;
using namespace Eval::AST;

using enum Token::Type;
using enum Eval::Error::Type;

Base *Parser::expr()
{ return parse(1); }

Base *Parser::parse(size_t priority)
{
    if (priority == OperatorToken::maxPriority + 1)
        return fact();

    return node(priority);
}

Node *Parser::node(size_t priority)
{
    vector<Base *> nodes;
    vector<OperatorToken *> operators;

    nodes.push_back(parse(priority + 1));
    while (checkOperator(priority))
    {
        operators.push_back(static_cast<OperatorToken *>(match()));
        nodes.push_back(parse(priority + 1));
    }

    return new Node(nodes, operators);
}

Base *Parser::fact()
{
    if (current() == Number) 
        return new Literal(match());

    if (current()->value == "-") return unary();
    if (current()->value == "(") return brackets();

    if (current() == Id)
    {
        auto id = match();

        if (current()->value == "(") 
            return call(id);

        return new Literal(id);
    }

    error();
}

Call *Parser::call(Token *id)
{
    vector<Base *> args;

    match("(");

    args.push_back(expr());
    while (current()->value == ",")
        args.push_back(( match(","), expr() ));

    match(")");

    return new Call(id, args);
}

Unary *Parser::unary()
{ return new Unary(( match("-"), fact() )); }

Base *Parser::brackets()
{
    match("(");
    auto expr = this->expr();
    match(")");

    return expr;
}

void Parser::match(string value)
{
    if (current()->value == value)
    {
        match();
        return;
    }
    
    error();
}

Token *Parser::match(Token::Type type)
{
    if (current() == type)
        return match();
    
    error();
}

Token *Parser::match()
{ return tokens[index++]; }

Token *Parser::current()
{ 
    if (index >= tokens.size())
        return new Token(index);

    return tokens[index];
}

void Parser::error()
{ throw new Eval::Error(current()->pos, current()->value, UnexpectedToken); }

bool Parser::checkOperator(size_t priority)
{ 
    return current() == Operator 
        && static_cast<OperatorToken *>(current())->priority == priority;
}