#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "eval.h"

#define BUFF_SIZE 100

void REPL(Constant_s **constants)
{
    printf("Welcome to REPL for Saturn Eval v%s\nType \".exit\" to exit, \".help\" to more information\n", VERSION);

    char *input = malloc(BUFF_SIZE * sizeof(char));
    Status_s *status = malloc(sizeof(Status_s));
    while (1)
    {
        memset(input, 0, BUFF_SIZE);
        memset(status, 0, sizeof(Status_s));

        printf("> ");
        fgets(input, BUFF_SIZE, stdin);

        if (strcmp(input, "\n") == 0)
            continue;
        
        if (input[0] == '.')
        {
            if (strcmp(input, ".exit\n") == 0) break;
            else if (strcmp(input, ".help") == 0) 
                printf("Git repository: https://github.com/DemetryF/Saturn-Eval\n\n7 operators: +, -, /, *, %%, \\, ^.\nBrackets: \"()\"\nDouble numbers: 2.1\nFunctions: sin(12). use .funcs in REPL to check functions list.\n");
            else if (strcmp(input, "funcs")) 
            {
                FILE *fptr = fopen("eval/functions_list.txt", "r");
                char *text = (char *)calloc(400, sizeof(char));

                if (!fptr || !text)
                {
                    printf("an error occurred while opening the file\n");
                    exit(1);
                }

                fread(text, 400, 200, fptr);
                fclose(fptr);
                puts(text);
                free(text);
            }
            else printf("\"%s\" is not REPL command.\n", input);

            continue;
        }

        double result = eval(input, status, constants);

        switch (status->code)
        {
        case sc_unexped_token:
            printf("Unexped token '%c' at %ld\n", status->data3, status->data1 + 1);
            break;
        
        case sc_brackets_error:
            printf("Brackets error\n");
            break;

        case sc_is_not_defined:
            printf("'%s' is not defined\n", status->data2);
            break;

        case sc_is_not_a_function:
            printf("'%s' is not a function\n", status->data2);
            break;

        case sc_unexped_end_of_line:
            printf("Unexped end of input\n");
            break;

        case sc_zero_tokens:
            continue;

        case sc_ok:
            printf("%g\n", result);
            break;
        }
    }

    free(input);
    free(status);
}