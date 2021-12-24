#!/bin/bash

CC="g++"
FLAGS="-Isrc/headers -o repl -std=c++17"
FILES="src/lexer.cpp
       src/parser.cpp
       src/interpreter.cpp"

$CC $FLAGS $FILES $1