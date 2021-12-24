# Welcome to the Saturn Eval!
Saturn Eval is simple calculator.
He have four operators: sum, difference, multiply, division and unary minus.
Also he have functions, for example `sin(pi)` or `pow(3, 2)`.

# Compiling
```sh
chmod +x compile.sh
./compile.sh REPL.cpp
```

# Using
1. inclide eval.hpp
2. Create environment:
```cpp
map<string, Function *> functions;
map<string, double> variables;
// ...
Eval::Environment *env = new Eval::Environment(functions, variables);
```
3. Create interpreter instance:
```cpp
Eval::Interpreter *interpreter = new Eval::Interpreter(env);
```
4. Use he: `interpreter.eval(expression)`.