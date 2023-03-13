#include "ast_node.hh"

gerador::ast_node::ast_node(ast_node_types label, ast_node_representation& rep) {
    label = label;

    switch(label) {
        case ast_node_types::CONSTANT:
            this->rep._ast_constant.id = rep._ast_constant.id;
            this->rep._ast_constant.value = rep._ast_constant.value;
            break;

        case ast_node_types::GLOBAL_VAR:
            this->rep._ast_global_var.id = rep._ast_global_var.id;
            this->rep._ast_global_var.value = rep._ast_global_var.value;
            break;

        case ast_node_types::FUNCTION:
            this->rep._ast_function.id = rep._ast_function.id;
            this->rep._ast_function.return_type = rep._ast_function.return_type;
            this->rep._ast_function.params = rep._ast_function.params;
            this->rep._ast_function.body = rep._ast_function.body;
            break;

        case ast_node_types::VAR:
            this->rep._ast_var.id = rep._ast_var.id;
            this->rep._ast_var.type = rep._ast_var.type;
            break;

        case ast_node_types::FOR:
            this->rep._ast_for.init = rep._ast_for.init;
            this->rep._ast_for.condition = rep._ast_for.condition;
            this->rep._ast_for.increment = rep._ast_for.increment;
            this->rep._ast_for.loop = rep._ast_for.loop;
            break;

        case ast_node_types::WHILE:
            this->rep._ast_while.condition = rep._ast_while.condition;
            this->rep._ast_while.loop = rep._ast_while.loop;
            break;

        case ast_node_types::DO_WHILE:
            this->rep._ast_while.condition = rep._ast_while.condition;
            this->rep._ast_while.loop = rep._ast_while.loop;
            break;

        case ast_node_types::IF:
            this->rep._ast_if.condition = rep._ast_if.condition;
            this->rep._ast_if.then_body = rep._ast_if.then_body;
            this->rep._ast_if.else_body = rep._ast_if.else_body;
            break;
        
        case ast_node_types::PRINTF:
            this->rep._ast_variadic.format = rep._ast_variadic.format;
            this->rep._ast_variadic.params = rep._ast_variadic.params;
            break;

        case ast_node_types::SCANF:
            this->rep._ast_variadic.format = rep._ast_variadic.format;
            this->rep._ast_variadic.params = rep._ast_variadic.params;
            break;

        case ast_node_types::TERNARY:
            this->rep._ast_ternary.condition = rep._ast_ternary.condition;
            this->rep._ast_ternary.then_body = rep._ast_ternary.then_body;
            this->rep._ast_ternary.else_body = rep._ast_ternary.else_body;
            break;

        case ast_node_types::PLUS:
        case ast_node_types::MINUS:
        case ast_node_types::MULTIPLY:
        case ast_node_types::DIV:
        case ast_node_types::REMAINDER:
        case ast_node_types::BITWISE_AND:
        case ast_node_types::BITWISE_OR:
        case ast_node_types::BITWISE_XOR:
        case ast_node_types::LOGICAL_AND:
        case ast_node_types::LOGICAL_OR:
        case ast_node_types::EQUAL:
        case ast_node_types::NOT_EQUAL:
        case ast_node_types::LESS_THAN:
        case ast_node_types::GREATER_THAN:
        case ast_node_types::LESS_EQUAL:
        case ast_node_types::GREATER_EQUAL:
        case ast_node_types::R_SHIFT:
        case ast_node_types::L_SHIFT:
        case ast_node_types::ASSIGN:
        case ast_node_types::ADD_ASSIGN:
        case ast_node_types::MINUS_ASSIGN:
            this->rep._ast_binary.left = rep._ast_binary.left;
            this->rep._ast_binary.right = rep._ast_binary.right;
            break;
        
        case ast_node_types::PRE_INC:
        case ast_node_types::PRE_DEC:
        case ast_node_types::POST_INC:
        case ast_node_types::POST_DEC:
        case ast_node_types::BITWISE_NOT:
        case ast_node_types::NOT:
        case ast_node_types::REFERENCE:
        case ast_node_types::DEFERENCE:
        case ast_node_types::NEGATIVE:
        case ast_node_types::POSITIVE:
        case ast_node_types::EXIT:
        case ast_node_types::RETURN:
            this->rep._ast_unary.operand = rep._ast_unary.operand;
            break;

        case ast_node_types::CALL:
            this->rep._ast_call.id = rep._ast_call.id;
            this->rep._ast_call.params = rep._ast_call.params;
            break;

        case ast_node_types::ID:
            this->rep._ast_id.id = std::string(rep._ast_id.id);
            this->rep._ast_id.ptr_level = rep._ast_id.ptr_level;
            break;

        case ast_node_types::DECIMAL:
            this->rep._ast_decimal.value = rep._ast_decimal.value;
            break;

        case ast_node_types::STRING:
            this->rep._ast_string.value = rep._ast_string.value;
            break;

        case ast_node_types::CHARACTER:
            this->rep._ast_character.value = rep._ast_character.value;
            break;

        default:
            break;
    }
}