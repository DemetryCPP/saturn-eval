#include <iostream>
#include <string>
#include <stdexcept>

#include "eval.hpp"

int main(int argc, char const *argv[])
{
    std::cout 
        << "Welcome to the SaturnEval v" VERSION ".\n"
        << "Write .exit to exit.\n";

    std::string input;

    Environment env;
    env.stdinit();

    while (true)
    {
        std::cout << "> ";
        std::getline(std::cin, input);

        if (input == ".exit") break;
        double result;    

        try
        {
            result = eval(input, env);
        }
        catch(const Environment::UnexpectedToken& e)
        {
            std::cout << std::string(2 + e.pos - e.token.length(), ' ')
                      << "^" + std::string(e.token.length() - 1, '~') << std::endl
                      << e.what() << std::endl;
            continue;
        }
        catch(const std::invalid_argument& e)
        {
            std::cout << e.what() << std::endl;
            continue;
        }

        std::cout << result << std::endl;
    }
}