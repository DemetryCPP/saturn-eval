#include "utils.hpp"
#include "parser.hpp"
#include "eval.hpp"

using namespace std;
using namespace Node;

Parser::Parser(vector<Token *> tokens)
    : tokens(tokens) {};

Expr *Parser::expr()
{
    vector<Term *> nodes;
    std::vector<Operator *> operators;

    nodes.push_back(term());
    while (static_cast<Operator *>(current())->priority == 1)
    {
        operators.push_back(static_cast<Operator *>(match()));
        nodes.push_back(term());
    }

    return new Expr(nodes, operators);
}

Term *Parser::term()
{
    vector<Fact *> nodes;
    std::vector<Operator *> operators;

    nodes.push_back(fact());
    while (static_cast<Operator *>(current())->priority == 2)
    {
        operators.push_back(static_cast<Operator *>(match()));
        nodes.push_back(fact());
    }

    return new Term(nodes, operators);
}

Fact *Parser::fact()
{
    if (current()->type == Token::Type::Number) return literal();
    else if (current()->type == Token::Type::Id)
    {
        Token *id = match();
        if (current()->value == "(") return call(id);
        return new Literal(id);
    }
    else if (current()->value == "-") return unary();
    else if (current()->value == "(") return brackets();

    throw new Eval::Error(current()->pos, current()->value, Eval::Error::Type::UnexpectedToken);
}

Call *Parser::call(Token *id)
{
    vector<Expr *> args;

    match("(");
    args.push_back(expr());
    while (current()->value == ",")
    {
        match();
        args.push_back(expr());
    }
    match(")");

    return new Call(id, args);
}

Unary *Parser::unary()
{
    match("-");
    return new Unary(fact());
}

Literal *Parser::literal()
{ return new Literal(match()); }

Brackets *Parser::brackets()
{
    match("(");
    Expr *expr = this->expr();
    match(")");

    return new Brackets(expr);
}

void Parser::match(string value)
{
    if (current()->value == value) match();
    else throw new Eval::Error(current()->pos, current()->value, Eval::Error::Type::UnexpectedToken);
}

Token *Parser::match(Token::Type type)
{
    if (current()->type == type) return match();
    else throw new Eval::Error(current()->pos, current()->value, Eval::Error::Type::UnexpectedToken);
}

Token *Parser::match()
{ return tokens[index++]; }

Token *Parser::current()
{ 
    if (index >= tokens.size())
        return new Token(index);
    return tokens[index];
}