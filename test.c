#include <stdio.h>
#include <stdlib.h>
#include "eval/eval.h"

void test(char *expression, double should_result, Constant_s **constants)
{
    size_t status = 0;
    double result = eval(expression, &status, constants);

    if (should_result != result)
        printf("Test \x1b[31mfailed\x1b[0m:\ninput: \"%s\"\nactual: %g\nexpected: %g\n\n", expression, should_result, result);
    else
        printf("Test for \"%s\"\n \x1b[32mpassed\x1b[0m\n\n", expression);
}

int main()
{
    Constant_s **constants = (Constant_s **)malloc(3 * sizeof(Constant_s *));

    constants[0] = new_constant("e", M_E);
    constants[1] = new_constant("pi", M_PI);
    constants[3] = new_constant("", 0);

    test("1 + 2 + 3", 6, constants);            // basic test
    test("2 * 6 / 3", 4, constants);            // division and product
    test("2 ^ 10", 1024, constants);            // exponentation
    test("1 + (2 + 3) + 4", 10, constants);     // brackets
    test("21 * -1 + 19 * -1", -40, constants);  // unary minus

    return 0;
}