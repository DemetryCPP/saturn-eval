#include <iostream>
#include <string>
#include <stdexcept>
#include <cstring>

#include "eval.hpp"

int main(int argc, char const *argv[])
{
    std::cout
        << "Welcome to the SaturnEval v" VERSION ".\n"
        << "Write .exit to exit.\n";

    std::string input;

    Environment env;
    env.stdinit();

    for (size_t i = 1; i < argc; i++)
    {
        if (argv[i][0] == '-' && argv[i][1] == 'd')
        {
            size_t length = strlen(argv[i]) - 2;
            char *copy = (char *)malloc(length * sizeof(char));

            strcpy(copy, argv[i] + 2);

            std::string value = std::string(copy);

            size_t r = 1;   // 1 - name
                            // 2 - value 
            
            std::string name;
            std::string svalue;

            for (size_t i = 0; i < value.length(); i++)
            {
                char current = value[i];
                if (current == '=') {
                    r = 2;
                    continue;
                }

                if (r == 1)         name += current;
                else if (r == 2)  svalue += current;
            }

            env.variables.push_back(Environment::Variable(name, std::stod(svalue)));
        }
    }

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
        catch (const Environment::UnexpectedToken &e)
        {
            std::cout << std::string(2 + e.pos - e.token.length(), ' ')
                      << "^" + std::string(e.token.length() - 1, '~') << std::endl
                      << e.what() << std::endl;
            continue;
        }
        catch (const std::invalid_argument &e)
        {
            std::cout << e.what() << std::endl;
            continue;
        }

        std::cout << result << std::endl;
    }
}