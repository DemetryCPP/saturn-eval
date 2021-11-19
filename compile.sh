#!/bin/bash

CC="g++"
FLAGS="-Isrc/headers -o eval -lm"
FILES=" src/lexer.cpp
        src/parser.cpp
        src/solver.cpp
        src/eval.cpp
        src/environment.cpp"

$CC $FLAGS $FILES $1