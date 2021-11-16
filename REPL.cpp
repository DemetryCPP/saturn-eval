#include <iostream>
#include <string>

#include "eval.hpp"

int main(int argc, char const *argv[])
{
    std::cout 
        << "Welcome to the SaturnEval v" VERSION ".\n"
        << "Write .exit to exit.\n";

    std::string input;

    while (true)
    {
        std::cout << "> ";
        std::getline(std::cin, input);

        if (input == ".exit")
            break;

        double result;    

        try
        {
            result = eval(input);
        }
        catch(const std::exception& e)
        {
            std::cout << e.what() << std::endl;
            continue;
        }

        std::cout << result << std::endl;
    }
}