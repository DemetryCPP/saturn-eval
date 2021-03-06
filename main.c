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

#define TEXT_SIZE 100

double eval(char* expression)
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


    double result = solve(Head);

    for (int i = 0; i < lexemsCount; i++) free(lexems[i]);
    free(lexems);
    free_tree(Head);

    return result;
}

int main(int argc, char const *argv[]) 
{
    char expression[TEXT_SIZE];

    printf("Eval Mathematic Expressions 2.0\nType \".exit\" for exit.\n");

    while (1)
    {
        printf("> ");
        fgets(expression, TEXT_SIZE, stdin);

        if (strcmp(expression, ".exit\n") == 0) exit(1);
        if (strcmp(expression, "\n\0") == 0) continue;

        double result = eval(expression);   

        if (result == (unsigned)-1) continue;

        printf("%lf\n", result);
    }
    
    return 0;
}