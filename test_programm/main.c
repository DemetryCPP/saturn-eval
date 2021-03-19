#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../eval/eval.h"

#define BUFF_SIZE 100
#define VERSION "3.0.0"

int main(size_t argc, char *argv[])
{
    printf("Welcome to Evaluate Mathematic Expression v%s\nType \".exit\" to exit, \".help\" to more information.\n", VERSION);

    char *input = calloc(BUFF_SIZE, sizeof(char));

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

        double result = eval(input, &status);
        if (status) continue;

        printf("%lf\n", result);
    }

    free(input);
    return 0;
}