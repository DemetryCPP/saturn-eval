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

# Catch errors

`Eval::Interpreter::eval` throws `Eval::Error`.
It has five types (type specified in `Eval::Error::type`):

- `UnexpectedToken`: unexpected token, it is specified in field `token`.
- `IsNotAFunction`: trying to call function, whose name is not known by the interpreter (its name is specified in field `token`).
- `IsNotDefined`: trying to get value of variable, whose name is not known by the interpreter (its name is specified in field `token`).
- `TooManyArgs`: trying to call function with extra arguments (function name is specified in field `token`).
- `TooFewArgs`: trying to call function without required amount of arguments (function name is specified in field `token`).

Also `Eval::Error` contains index on which the error occured.
