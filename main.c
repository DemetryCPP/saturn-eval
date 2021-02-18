#include <stdio.h>
#include <stdlib.h>

#include "lexer/lexer.h"
#include "lexer/data.h"

#define TEXT_SIZE 100

int main(int argc, char const *argv[]) {
    char expression[TEXT_SIZE];
    size_t lexemsCount;

    printf("write expression: ");
    fgets(expression, TEXT_SIZE, stdin);
    printf("\nLexing...\n\n");

    Lexem_s **lexems = lexer(expression, &lexemsCount);

    printf("\nlexing result: '");
    for (int i = 0; i < lexemsCount; i++) printf("%c", lexems[i]->Data);
    printf("', lexems count: %ld\n", lexemsCount);

    for (int i = 0; i < lexemsCount; i++) free(lexems[i]);
    free(lexems);

    return 0;
}