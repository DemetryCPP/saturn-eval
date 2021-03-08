#include <math.h>

double mini(double left, double right, short oper)
{
    switch (oper)
    {
        case '+': return left + right;
        case '-': return left - right;
        case '*': return left * right;
        case '/': return left / right;
        case '%': return left - right  * floor(left / right);
        case '\\': return (int)left / (int)right;
        case '^': return pow(left, right);
    }
}