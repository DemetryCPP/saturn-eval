double mini(double left, double right, short oper)
{
    switch (oper)
    {
        case '+': return left + right;
        case '-': return left - right;
        case '*': return left * right;
        case '/': return left / right;
    }
}