#include <stdio.h>
#include <stdlib.h>
#define __USE_MISC 1
#include <math.h>
#include <string.h>
#include "eval.h"

void REPL(Constant_s **constants);

int main(int argc, char *argv[])
{
    Constant_s **constants = malloc((argc + 2) * sizeof(Constant_s *));
    size_t constants_count = 2;

    if (!constants)
    {
        puts("memory allocation error.");
        exit(1);
    }   

    constants[0] = new_constant("e", M_E);
    constants[1] = new_constant("pi", M_PI);

    for (size_t i = 1; i < argc; i++)
    {
        char *current = argv[i];
        if (current[0] != '-') continue;
        switch (current[1])
        {
        case 'd':
        {
            char *copy = malloc(strlen(current + 2) * sizeof(char)), 
                 *name;

            if (current[2] == '=')
            {
                puts("Const name must be no null!");
                exit(1);
            }
            
            if (!copy)
            {
                puts("memory allocation error.");
                exit(1);
            }

            strcpy(copy, current + 2);
            name = strtok(copy, "=");
            if (!name)
            {
                puts("invalid -d flag usage.");
                exit(1);
            }

            if (strcmp(name, "e") == 0 || strcmp(name, "pi") == 0)
            {
                puts("name of constant cannot coincide with standard.");
                exit(1);
            }

            for (size_t i = 2; i < constants_count; i++)
                if (strcmp(constants[i]->name, name) == 0) 
                {
                    puts("names of constants cannot coincide");
                    exit(1);
                }

            double value = atof(strtok(NULL, "="));
            Constant_s *new_const = new_constant(name, value);
            new_const->name = name;
            new_const->value = value;
            constants[constants_count++] = new_const;

            break;
        }
        }
    }

    constants[constants_count] = new_constant("", 0);

    REPL(constants);
}