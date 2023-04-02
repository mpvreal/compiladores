#include "ast_node.hh"

gerador::ast_node& gerador::ast_node::operator=(const ast_node& node) {
    switch(node.label) {
        case gerador::ast_node_types::PROGRAM:
            rep._ast_program = node.rep._ast_program;
            break;
        case gerador::ast_node_types::CONSTANT:
            rep._ast_constant = node.rep._ast_constant;
            break;
        case gerador::ast_node_types::FUNCTION:
            rep._ast_function = node.rep._ast_function;
            break;
        case gerador::ast_node_types::VAR:
            rep._ast_var = node.rep._ast_var;
            break;
        case gerador::ast_node_types::FOR:
            rep._ast_for = node.rep._ast_for;
            break;
        case gerador::ast_node_types::WHILE:
        case gerador::ast_node_types::DO_WHILE:
            rep._ast_while = node.rep._ast_while;
            break;
        case gerador::ast_node_types::IF:
            rep._ast_if = node.rep._ast_if;
            break;
        case gerador::ast_node_types::CALL:
        case gerador::ast_node_types::PRINTF:
        case gerador::ast_node_types::SCANF:
            rep._ast_call = node.rep._ast_call;
            break;  
        case gerador::ast_node_types::TERNARY:
            rep._ast_ternary = node.rep._ast_ternary;
            break;
        case gerador::ast_node_types::PLUS:
        case gerador::ast_node_types::MINUS:
        case gerador::ast_node_types::MULTIPLY:
        case gerador::ast_node_types::DIV:
        case gerador::ast_node_types::REMAINDER:
        case gerador::ast_node_types::BITWISE_AND:
        case gerador::ast_node_types::BITWISE_OR:
        case gerador::ast_node_types::BITWISE_XOR:
        case gerador::ast_node_types::LOGICAL_AND:
        case gerador::ast_node_types::LOGICAL_OR:
        case gerador::ast_node_types::EQUAL:
        case gerador::ast_node_types::NOT_EQUAL:
        case gerador::ast_node_types::LESS_THAN:
        case gerador::ast_node_types::GREATER_THAN:
        case gerador::ast_node_types::LESS_EQUAL:
        case gerador::ast_node_types::GREATER_EQUAL:
        case gerador::ast_node_types::R_SHIFT:
        case gerador::ast_node_types::L_SHIFT:
        case gerador::ast_node_types::ASSIGN:
        case gerador::ast_node_types::ADD_ASSIGN:
        case gerador::ast_node_types::MINUS_ASSIGN:
            rep._ast_binary = node.rep._ast_binary;
            break;
        case gerador::ast_node_types::PRE_INC:
        case gerador::ast_node_types::PRE_DEC:
        case gerador::ast_node_types::POST_INC:
        case gerador::ast_node_types::POST_DEC:
        case gerador::ast_node_types::BITWISE_NOT:
        case gerador::ast_node_types::REFERENCE:
        case gerador::ast_node_types::DEFERENCE:
        case gerador::ast_node_types::NEGATIVE:
        case gerador::ast_node_types::POSITIVE:
        case gerador::ast_node_types::NOT:
        case gerador::ast_node_types::EXIT:
        case gerador::ast_node_types::RETURN:
            rep._ast_unary = node.rep._ast_unary;
            break;
        case gerador::ast_node_types::ID:
        case gerador::ast_node_types::STRING:
            rep._ast_text.id = node.rep._ast_text.id;
            break;
        case gerador::ast_node_types::NUMBER:
        case gerador::ast_node_types::CHARACTER:
            rep._ast_decimal.value = node.rep._ast_decimal.value;
            break;
        default:
            break;
    }
        label = node.label;

        return *this;
}