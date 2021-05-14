#include <stdio.h>
#include <stdlib.h>

#include "parser_types.h"
#include "parser.h"
#include "solve_types.h"
#include "status.h"

void parser(Node_s *node, Status_s *status, Operator_s **operators)
{
    if (node->length == 0)
    {
        if (node->tokens[-1]->value != '-') status->code = sc_unexped_end_of_line;
        return;
    }
    node->divider_pos = find_divider_pos(node->tokens, node->length, operators);

    if (node->divider_pos == -1)
    {
        remove_brackets(node);
        node->divider_pos = find_divider_pos(node->tokens, node->length, operators);
    }

    if (status->code != sc_ok) return;
    if (node->divider_pos == -1) return;

    node->operator_sign = node->tokens[node->divider_pos]->value;

    node->left = new_node(node->tokens, node->divider_pos, NULL, NULL, '\0', 0);
    node->right = new_node(node->tokens + node->divider_pos + 1, node->length - node->divider_pos - 1, NULL, NULL, '\0', 0);

    if (node->operator_sign == '(')
    {
        node->operator_sign = 'f';
        node->right->tokens--;
        node->right->length++;
    }

    parser(node->left, status, operators);
    parser(node->right, status, operators);
}