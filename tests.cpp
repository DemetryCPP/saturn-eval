#include <iostream>
#include "include/eval.hpp"

#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_RESET   "\x1b[0m"

using namespace Eval;
using enum Error::Type;

void success()
{ cout << COLOR_GREEN "test passed successfully" COLOR_RESET << endl; };

void header(string h)
{ cout << endl << COLOR_CYAN + h + COLOR_RESET << endl; }

string errors[] {
    "Unexpected token",
    "Is not a function",
    "Is not defined",
    "Too many args",
    "Too few args",
};

void assertEqual(Interpreter *i, string expr, double validvalue)
{
    auto result = i->eval(expr);
    if (result == validvalue)
        succes();
    else
        cout << COLOR_RED "failed " COLOR_RESET + expr + ": expected " << validvalue << ", but got " << result << endl;
}

void assertEqual(Interpreter *i, string expr, Error::Type type)
{
    double result;
    try
    { result = i->eval(expr); }
    catch (Error *e)
    { 
        if (e->type == type)
            success();
        else
            cout << COLOR_RED "failed " COLOR_RESET + expr + ": expected error \"" + errors[(int)type] + "\", but got \"" + errors[(int)e->type] + "\"" << endl;
        
        return;
    }

    cout << COLOR_RED "failed " COLOR_RESET + expr + ": expected throwing error \"" + errors[(int)type] + "\", but nothing throw away" << endl;
}

int main(int argc, char const *argv[])
{
    map<string, Function *> functions;
    map<string, double> variables;

    functions["test"] = new Function([](vector<double>){return 0.0;}, 2);
    variables["test"] = 3;

    auto interpreter = new Interpreter(variables, functions);

    header("simple expression");
    assertEqual(interpreter, "2 * (2 + 2)", 8);
    assertEqual(interpreter, "2 + + 2", UnexpectedToken);

    header("variables");
    assertEqual(interpreter, "test", 3);
    assertEqual(interpreter, "id", IsNotDefined);

    header("functions");
    assertEqual(interpreter, "test(2, 2)", 0);
    assertEqual(interpreter, "test(2)", TooFewArgs);
    assertEqual(interpreter, "test(2, 2, 2)", TooManyArgs);
    assertEqual(interpreter, "id(2)", IsNotAFunction);

    return 0;
}