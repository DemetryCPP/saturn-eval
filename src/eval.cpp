#include <string>
#include <vector>
#include <iostream>

#include "lexer.hpp"
#include "parser.hpp"

double solve(Node node);

double eval(std::string expr)
{
    Token::Lexer lexer{expr};
    std::vector<Token> tokens = lexer.allTokens();

    Node head = Node{tokens};
    head.parse();

    return solve(head);
}