#include <iostream>
#include <string>
#include <cmath>
#include <map>
#include "eval.hpp"

#define function(name, argcount, code) functions.insert({ name, new Eval::Function([](std::vector<double> args) { return code ; }, argcount) })

int main(int argc, char const *argv[])
{
    std::map<std::string, double> variables;
    std::map<std::string, Eval::Function *> functions; 

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

    Eval::Interpreter *interpreter = new Eval::Interpreter(variables, functions);
    std::string input;

    std::cout
        << "Welcome to the SaturnEval v" + Eval::version + "." << std::endl
        << "Write .exit to exit." << std::endl;

    while (true)
    {
        std::cout << "> ";
        std::getline(std::cin, input);

        if (input == ".exit")
            break;

        try {
            std::cout << std::to_string(interpreter->eval(input)) << std::endl;
        } catch (Eval::Error *e) {
            std::cout << std::string(e->pos + 2, ' ')
                      << '^' << std::string(e->token.length() - 1, '~')
                      << std::endl;

            switch (e->type)
            {
            case Eval::Error::Type::UnexpectedToken:
                std::cout << "Unexpected token \"" + e->token + "\" at " << std::to_string(e->pos) << std::endl;
                break;

            case Eval::Error::Type::IsNotAFunction:
                std::cout << e->token << "is not a function" << std::endl;
                break;

            case Eval::Error::Type::IsNotDefined:
                std::cout << e->token << "is not defined" << std::endl;
                break;

            case Eval::Error::Type::TooManyArgs:
                std::cout << "too many args for " << e->token << std::endl;
                break;

            case Eval::Error::Type::TooFewArgs:
                std::cout << "too few args for " << e->token << std::endl;
                break;
            }
        }
    }

    return 0;
}