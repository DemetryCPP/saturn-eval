#include <iostream>
#include <string>
#include <cmath>
#include <map>
#include "eval.hpp"

#define function(name, argcount, code) functions.insert({ name, new Eval::Function([](std::vector<double> args) { return code ; }, argcount) })

#define COLOR_RED     "\x1b[31m"
#define COLOR_RESET   "\x1b[0m"
#define COLOR_BRIGHT  "\x1b[1m"

using namespace Eval;

int main(int argc, char const *argv[])
{
    map<string, double> variables;
    map<string, Function *> functions; 

    variables.insert({ "pi", M_PI });
    variables.insert({ "e",  M_E  });

    function("abs",   1, (double)fabs(args[0]));
    function("ceil",  1, ceil(args[0]));
    function("floor", 1, floor(args[0]));
    function("pow",   2, pow(args[0], args[1]));

    function("acos",  1, acos(args[0]));
    function("asin",  1, asin(args[0]));
    function("atan",  1, atan(args[0]));

    function("cos",   1, cos(args[0]));
    function("sin",   1, sin(args[0]));

    function("ln",    1, log(args[0]));
    function("lg",    1, log10(args[0]));
    function("sqrt",  1, sqrt(args[0]));

    auto interpreter = new Interpreter(variables, functions);
    string input;

    cout << "Welcome to the SaturnEval v" + version + "." << endl
         << "Write .exit to exit." << endl;

    while (true)
    {
        cout << "> ";
        getline(cin, input);

        if (input == ".exit")
            break;

        input += " ";

        try
        { cout << to_string(interpreter->eval(input)) << endl; }
        catch (Error *e)
        {
            cout << COLOR_BRIGHT COLOR_RED + string(e->pos + 1, ' ') << '^' << string(e->token.length() - 1, '~') + COLOR_RESET << endl;
            cout << e->format() << endl;
        }
    }

    return 0;
}