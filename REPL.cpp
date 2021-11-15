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

        std::cout << eval(input) << std::endl;
    }
}