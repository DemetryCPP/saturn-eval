#!/bin/bash

CC="g++-11"
FLAGS="-Iinclude/ -o repl -std=c++2a"
FILES="src/lexer.cpp
       src/parser.cpp
       src/interpreter.cpp"

$CC $FLAGS $FILES $1