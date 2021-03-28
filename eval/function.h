#include <string.h>
#include <math.h>

#define isf(name) strcmp(fname, name) == 0 

double function(char *fname, double arg)
{
    if (isf("sin")) return sin(arg);
    if (isf("cos")) return cos(arg);
}