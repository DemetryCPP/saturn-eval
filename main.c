#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer/lexer.h"
#include "lexer/data.h"
#include "lexer/check_valid.h"

#include "parser/data.h"
#include "parser/parser.h"
#include "parser/free_tree.h"

#include "solve/solve.h"

#include "constant.h"

#define TEXT_SIZE 100

double eval(char* expression, constant_s **constants, size_t constants_count, short show_solve)
{
    // printf("\nLexing...\n\n");

    size_t lexemsCount;
    Lexem_s **lexems = lexer(expression, &lexemsCount);

    if ((unsigned)lexems == 1) return (unsigned)-1;

    char* lx_result = lexems_to_text(lexems, lexemsCount);

    // printf("\nlexing result: '%s', lexems count: %ld\n", lx_result, lexemsCount);
    free(lx_result);

    // printf("\nparsing...\n\n");

    Node_s *Head = new_node(lexems, lexemsCount, -1, '\0', 0x0, 0x0);
    if (check_valid(Head->lexems, Head->length)) return (unsigned)-1;
    parser(Head);

    double result = solve(Head, constants, constants_count, show_solve);

    if (show_solve) printf("\n");

    for (int i = 0; i < lexemsCount; i++) free(lexems[i]);
    free(lexems);
    free_tree(Head);

    return result;
}

int main(int argc, char const *argv[]) 
{
    char expression[TEXT_SIZE];
    constant_s **constants = (constant_s **)malloc(argc * sizeof(constant_s *));
    size_t constant_count = 0;
    short show_solve = 0;

    printf("Evaluate Mathematic Expressions 2.3\nType \".exit\" for exit, \"help\" for more information.\n");

    for (size_t i = 1; i < argc; i++)
    {
        if (argv[i][0] == '-')
        {
            switch (argv[i][1])
            {
                case 'd': {
                    char *copy = malloc(strlen(argv[i] + 2) * sizeof(char));
                    strcpy(copy, argv[i] + 2);

                    char *name = strtok(copy, "=");
                    if (name == NULL)
                    {
                        printf("invalid -d flag use.\n");
                        return 1;
                    }
                    double value = atof(strtok(NULL, "="));

                    constants[constant_count] = (constant_s *)malloc(sizeof(constant_s *));

                    constants[constant_count]->name = name;
                    constants[constant_count]->value = value;

                    constant_count++;
                } break;
                case 's': show_solve = 1;
            }
        }
    }

    constants = realloc(constants, constant_count);

    while (1)
    {
        printf("> ");
        fgets(expression, TEXT_SIZE, stdin);

        if (strcmp(expression, ".exit\n") == 0) exit(0);
        if (strcmp(expression, ".help\n") == 0)
        {
            printf("\t7 operators: '+', '-', '*', '/', '\\', '%%'\n\tbracketing: ()\n\treal numbers: 1.2\n\tconstants: e and pi\n\tcustom constants, for define use -d flag: -dname=value.\n");
            continue;
        }
        if (strcmp(expression, "\n\0") == 0) continue;

        double result = eval(expression, constants, constant_count, show_solve);

        if (result == big_num) continue;

        printf("%lf\n", result);
    }
    
    for (size_t i = 0; i < constant_count; i++) free(constants[i]);
    free(constants);

    return 0;
}