CC="gcc"
FLAGS="-lm -o calc -Ieval/headers/"
FILES="eval/lexer/utils.c 
       eval/lexer/lexer.c 
       eval/parser/find_divider_pos.c 
       eval/parser/remove_brackets.c 
       eval/parser/utils.c 
       eval/parser/parser.c 
       eval/solve/constants.c 
       eval/solve/functions.c 
       eval/solve/operators.c 
       eval/solve/solve.c 
       eval/free.c 
       eval/eval.c 
       test_program/main.c"

$CC $FILES $FLAGS