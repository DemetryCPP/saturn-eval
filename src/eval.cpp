#include <string>
#include <vector>
#include <iostream>

#include "lexer.hpp"
#include "parser.hpp"
#include "environment.hpp"

double solve(Node node, Environment env);

double eval(std::string expr, Environment env)
{
    env.stdinit();

    Token::Lexer lexer{expr, env};
    std::vector<Token*> tokens = lexer.allTokens();

    Node head = Node{tokens};
    head.parse(env);

    return solve(head, env);
}