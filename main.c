#include <stdio.h>
#include <stdlib.h>

#include "lexer/lexer.h"
#include "lexer/data.h"

#define TEXT_SIZE 100

int main(int argc, char const *argv[]) {
    char text[TEXT_SIZE];

    printf("write expression:");
    scanf("%s\n", text);

    lexer();

    return 0;
}
