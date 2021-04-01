#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../headers/solve_types.h"
#include "../headers/status.h"

double function(char *fname, double arg, Status_s *status)
{
    if (isf("sin")) return sin(arg);
    if (isf("cos")) return cos(arg);
    if (isf("abs")) return fabs(arg);
    if (isf("acos")) return acos(arg);
    if (isf("asin")) return asin(arg);
    if (isf("atan")) return atan(arg);
    if (isf("ch") || isf("cosh")) return cosh(arg);
    if (isf("sh") || isf("sinh")) return sinh(arg);
    if (isf("exp")) return exp(arg);
    if (isf("ln")) return log(arg);
    if (isf("lg")) return log10(arg);
    if (isf("sqrt")) return sqrt(arg);
    if (isf("tan")) return tan(arg);
    if (isf("tanh")) return tanh(arg);

    // printf("\"%s\" is not a function\n", fname);
    status->code = sc_is_not_a_function;
    status->data2 = malloc(strlen(fname) * sizeof(char));
    strcpy(status->data2, fname);

    return -1;
}