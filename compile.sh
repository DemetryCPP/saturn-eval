#!/bin/bash

CC="g++"
FLAGS="-Isrc/headers -o eval -lm"

FILES=" src/lexer/allTokens.cpp
        src/lexer/nextToken.cpp
        src/lexer/utils.cpp

        src/parser/parse.cpp
        src/parser/utils.cpp

        src/solver.cpp
        src/eval.cpp
        src/environment.cpp"

$CC $FLAGS $FILES $1