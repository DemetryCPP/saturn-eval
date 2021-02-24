#include <stdio.h>
#include <stdlib.h>

#include "lexer/lexer.h"
#include "lexer/data.h"

#include "parser/data.h"
#include "parser/parser.h"
#include "parser/free_tree.h"

#include "solve/solve.h"

#define TEXT_SIZE 100

double eval(char* expression)
{
    printf("\nLexing...\n\n");

    size_t lexemsCount;
    Lexem_s **lexems = lexer(expression, &lexemsCount);

    char* lx_result = lexems_to_text(lexems, lexemsCount);

    printf("\nlexing result: '%s', lexems count: %ld\n", lx_result, lexemsCount);
    free(lx_result);

    printf("\nparsing...\n\n");

    Node_s *Head = new_node(lexems, lexemsCount, -1, '\0', 0x0, 0x0);
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

    printf("write expression: ");
    fgets(expression, TEXT_SIZE, stdin);

    printf("result: %lf\n", eval(expression));

    return 0;
}