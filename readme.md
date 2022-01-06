# Welcome to the Saturn Eval!
Saturn Eval is a simple calculator.
It supports common operations like addition, subtraction, multiplication, whole, modulo and common division and exponentiation.
Also, it supports functions like `sin(pi)` and `pow(3, 2)`.

# How to compile
```sh
chmod +x compile.sh
./compile.sh REPL.cpp
```

warning: requires C++20. (use 11 version of g++ or 13 of clang).

# Usage
1. include eval.hpp
2. Create an environment:
```cpp
map<string, Eval::Function *> functions;
map<string, double> variables;
// ...

```
3. Create an instance of the interpreter:
```cpp
auto interpreter = new Eval::Interpreter(variables, functions);
```
4. Usage: `interpreter.eval(expression)`.
