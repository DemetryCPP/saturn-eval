#!/bin/bash

CC="g++"
FLAGS="-Isrc/headers -o eval"
FILES=" src/lexer.cpp
        src/parser.cpp
        src/solver.cpp
        src/eval.cpp"

$CC $FLAGS $FILES $1