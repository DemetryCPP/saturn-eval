# Welcome to the Saturn Eval!
Saturn Eval is a simple calculator.
It supports common operations like addition, subtraction, multiplication and division.
Also, it supports functions like `sin(pi)` and `pow(3, 2)`.

# How to compile
```sh
chmod +x compile.sh
./compile.sh REPL.cpp
```

# Usage
1. include eval.hpp
2. Create an environment:
```cpp
map<string, Function *> functions;
map<string, double> variables;
// ...
Eval::Environment *env = new Eval::Environment(functions, variables);
```
3. Create an instance of the interpreter:
```cpp
Eval::Interpreter *interpreter = new Eval::Interpreter(env);
```
4. Usage: `interpreter.eval(expression)`.
