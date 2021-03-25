#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../eval/eval.h"
#include "../eval/constants.h"

#define BUFF_SIZE 100
#define VERSION "3.0.0"

#define M_E        2.71828182845904523536
#define M_PI       3.14159265358979323846

int main(size_t argc, char *argv[])
{
    printf("Welcome to Evaluate Mathematic Expression v%s\nType \".exit\" to exit, \".help\" to more information.\n", VERSION);

    char *input = calloc(BUFF_SIZE, sizeof(char));
    Constant_s **constants = (Constant_s **)malloc((argc + 2) * sizeof(Constant_s *));
    size_t constant_count = 0;

    constants[constant_count++] = new_constant("e", M_E);
    constants[constant_count++] = new_constant("pi", M_PI);

    for (size_t i = 1; i < argc; i++)
    {
        char *current = argv[i];

        if (current[0] == '-')
        {
            switch (current[1])
            {
            case 'd':
            {
                char *copy = malloc(strlen(argv[i] + 2) * sizeof(char));
                strcpy(copy, argv[i] + 2);

                char *name = strtok(copy, "=");

                if (name == NULL)
                {
                    printf("invalid -d flag use.\n");
                    return 1;
                }
                
                double value = atof(strtok(NULL, "="));

                constants[constant_count] = new_constant(name, value);

                constants[constant_count]->name = name;
                constants[constant_count]->value = value;

                constant_count++;
            } break;
            }
        }
    }

    constants[constant_count] = new_constant("", 0);

    while (1)
    {
        memset(input, 0, BUFF_SIZE);
        size_t status = 0;
        printf("> ");
        fgets(input, BUFF_SIZE, stdin);     

        if (strcmp(input, "\n") == 0)
            continue;

        if (input[0] == '.')
        {
            if (strcmp(input + 1, "exit\n") == 0) break;
            if (strcmp(input + 1, "help\n") == 0) printf("Git repository: https://github.com/DemetryF/evaluate-mathematic-expressions\n\n7 operators: +, -, /, *, %%, \\, ^.\nBrackets: \"()\"\nDouble numbers: 2.1\n");

            continue;
        }

        double result = eval(input, &status, constants);
        if (status) continue;

        printf("%lf\n", result);
    }

    free(input);
    return 0;
}