#include <stdbool.h>
#include <stdlib.h>
#define __USE_MISC 1
#include <math.h>
#include "eval.h"

#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_RESET   "\x1b[0m"

bool test(char *expression, double expected)
{
    Status_t *status = malloc(sizeof(Status_t));
    Constant_t **constants = malloc(3 * sizeof(Status_t));
    constants[0] = new_constant("e", M_E);
    constants[1] = new_constant("pi", M_PI);
    constants[2] = new_constant("", 0);
    double eval_result = eval(expression, status, constants);
    bool result = status->code == sc_ok && eval_result == expected;
    if (result)
        printf(COLOR_GREEN "Passed test " COLOR_RESET "for \"%s\"\n\n", expression);
    else
        printf(COLOR_RED "Failed test " COLOR_RESET "for \"%s\":\nexpected: %g\nreceived: %g\n\n", expression, expected, eval_result);
    return result;
}

int main()
{
    printf("Start tests for Saturn Eval v%s\n\n", VERSION);
    test("2 * 2 + (1 - -1)", 6);
    test("2^5", 32);
    test("cos(12)^2 + sin(12)^2", 1);
    test("ln(e^10)", 10);
    test("-1 - sin(-pi)", -1);
}
