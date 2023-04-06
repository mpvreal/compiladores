#include <iostream>

#include "ast_node.hh"

static const char* node_labels[] = {
    "PROGRAM",
    "CONSTANT",
    "FUNCTION",
    "VAR",
    "PARAM",
    "FOR",
    "WHILE",
    "DO_WHILE",
    "IF",
    "CALL",
    "PRINTF",
    "SCANF",
    "TERNARY",
    "+",
    "-",
    "*",
    "/",
    "%",
    "&",
    "|",
    "^",
    "&&",
    "||",
    "==",
    "!=",
    "<",
    ">",
    "<=",
    ">=",
    ">>",
    "<<",
    "=",
    "+=",
    "-=",
    "++_",
    "--_",
    "_++",
    "_--",
    "~",
    "&",
    "*",
    "-",
    "+",
    "!",
    "EXIT",
    "RETURN",
    "ID",
    "NUMBER",
    "STRING",
    "CHARACTER" 
};

static int node_index = 0;

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

void gerador::ast_node::visit(void (*routine)(gerador::ast_node&)) {
    routine(*this);
    switch(label) {
        case gerador::ast_node_types::PROGRAM:
            for(const void*& i : rep._ast_program.commands) {
                ((gerador::ast_node*) i)->visit(routine);
            }
            break;
        case gerador::ast_node_types::FUNCTION:
            for(const void*& i : rep._ast_function.params) {
                ((gerador::ast_node*) i)->visit(routine);
            }
            for(const void*& i : rep._ast_function.body) {
                ((gerador::ast_node*) i)->visit(routine);
            }
            break;
        case gerador::ast_node_types::FOR:
            ((gerador::ast_node*) rep._ast_for.init)->visit(routine);
            ((gerador::ast_node*) rep._ast_for.condition)->visit(routine);
            ((gerador::ast_node*) rep._ast_for.increment)->visit(routine);
            for(const void*& i : rep._ast_for.loop) {
                ((gerador::ast_node*) i)->visit(routine);
            }
            break;
        case gerador::ast_node_types::WHILE:
        case gerador::ast_node_types::DO_WHILE:
            ((gerador::ast_node*) rep._ast_while.condition)->visit(routine);
            for(const void*& i : rep._ast_while.loop) {
                ((gerador::ast_node*) i)->visit(routine);
            }
            break;
        case gerador::ast_node_types::IF:
            ((gerador::ast_node*) rep._ast_if.condition)->visit(routine);

            for(const void*& i : rep._ast_if.then_body) {
                ((gerador::ast_node*) i)->visit(routine);
            }
            for(const void*& i : rep._ast_if.else_body) {
                ((gerador::ast_node*) i)->visit(routine);
            }
            break;
        case gerador::ast_node_types::CALL:
        case gerador::ast_node_types::PRINTF:
        case gerador::ast_node_types::SCANF:
            for(const void*& i : rep._ast_call.params) {
                ((gerador::ast_node*) i)->visit(routine);
            }
            break;  
        case gerador::ast_node_types::TERNARY:
            ((gerador::ast_node*) rep._ast_ternary.condition)->visit(routine);
            ((gerador::ast_node*) rep._ast_ternary.then_body)->visit(routine);
            ((gerador::ast_node*) rep._ast_ternary.else_body)->visit(routine);
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
            ((gerador::ast_node*) rep._ast_binary.left)->visit(routine);
            ((gerador::ast_node*) rep._ast_binary.right)->visit(routine);
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
            ((gerador::ast_node*) rep._ast_unary.operand)->visit(routine);
            break;
        default:
            break;
    }
}

inline const char* gerador::ast_node::to_string() {
    return node_labels[label];
}

void gerador::declare_node_dot(gerador::ast_node& node) {
    std::string l = "";
    if(node.get_label() == gerador::ast_node_types::ID) {
        std::cout << "    n" << std::to_string(node_index++) 
        << " [label=\"" << node.to_string() << ": " << node.get_rep()._ast_text.id << "\"]" 
        << std::endl;
    } else if(node.get_label() == gerador::ast_node_types::STRING) {
        std::cout << "    n" << std::to_string(node_index++) 
        << " [label=" << node.get_rep()._ast_text.id << "]" 
        << std::endl;
    } else if(node.get_label() == gerador::ast_node_types::NUMBER) {
        std::cout << "    n" << std::to_string(node_index++) 
        << " [label=\"" << std::to_string(node.get_rep()._ast_decimal.value) << "\"]" 
        << std::endl;
    } else if(node.get_label() == gerador::ast_node_types::CALL) {
        std::cout << "    n" << std::to_string(node_index++) 
        << " [label=\"" << "CALL: " << node.get_rep()._ast_call.id << "()" << "\"]" 
        << std::endl;
    } else if(node.get_label() == gerador::ast_node_types::VAR) {
        std::cout << "    n" << std::to_string(node_index++) 
        << " [label=\"" << "VAR: " << node.get_rep()._ast_var.id << "\"]" 
        << std::endl;
    } else {
        std::cout << "    n" << std::to_string(node_index++) 
        << " [label=\"" << node.to_string() << "\"]" 
        << std::endl;
    }
}

void gerador::declare_edge_dot(gerador::ast_node& node, const std::string& edge_label) {
    std::cout << edge_label << std::endl;

    int current_node = node_index++;

    switch(node.get_label()) {
        case gerador::ast_node_types::PROGRAM:
            for(const void*& i : node.get_rep()._ast_program.commands) {
                declare_edge_dot(*((gerador::ast_node*) i), 
                    "    n" + std::to_string(current_node) + " -> n" + std::to_string(node_index));
            }
            break;
        case gerador::ast_node_types::FUNCTION:
            for(const void*& i : node.get_rep()._ast_function.params) {
                declare_edge_dot(*((gerador::ast_node*) i), 
                    "    n" + std::to_string(current_node) + " -> n" + std::to_string(node_index));
            }
            for(const void*& i : node.get_rep()._ast_function.body) {
                declare_edge_dot(*((gerador::ast_node*) i), 
                    "    n" + std::to_string(current_node) + " -> n" + std::to_string(node_index));
            }
            break;
        case gerador::ast_node_types::FOR:
            // ((gerador::ast_node*) node.get_rep()._ast_for.init)->visit(routine);
            declare_edge_dot(*((gerador::ast_node*) node.get_rep()._ast_for.init), 
                    "    n" + std::to_string(current_node) + " -> n" + std::to_string(node_index));
            declare_edge_dot(*((gerador::ast_node*) node.get_rep()._ast_for.condition), 
                    "    n" + std::to_string(current_node) + " -> n" + std::to_string(node_index));
            declare_edge_dot(*((gerador::ast_node*) node.get_rep()._ast_for.increment), 
                    "    n" + std::to_string(current_node) + " -> n" + std::to_string(node_index));
            for(const void*& i : node.get_rep()._ast_for.loop) {
                declare_edge_dot(*((gerador::ast_node*) i), 
                    "    n" + std::to_string(current_node) + " -> n" + std::to_string(node_index));
            }
            break;
        case gerador::ast_node_types::WHILE:
        case gerador::ast_node_types::DO_WHILE:
            declare_edge_dot(*((gerador::ast_node*) node.get_rep()._ast_while.condition), 
                    "    n" + std::to_string(current_node) + " -> n" + std::to_string(node_index));
            for(const void*& i : node.get_rep()._ast_while.loop) {
                declare_edge_dot(*((gerador::ast_node*) i), 
                    "    n" + std::to_string(current_node) + " -> n" + std::to_string(node_index));
            }
            break;
        case gerador::ast_node_types::IF:
            declare_edge_dot(*((gerador::ast_node*) node.get_rep()._ast_if.condition), 
                    "    n" + std::to_string(current_node) + " -> n" + std::to_string(node_index));

            for(const void*& i : node.get_rep()._ast_if.then_body) {
                declare_edge_dot(*((gerador::ast_node*) i), 
                    "    n" + std::to_string(current_node) + " -> n" + std::to_string(node_index));
            }
            for(const void*& i : node.get_rep()._ast_if.else_body) {
                declare_edge_dot(*((gerador::ast_node*) i), 
                    "    n" + std::to_string(current_node) + " -> n" + std::to_string(node_index));
            }
            break;
        case gerador::ast_node_types::CALL:
        case gerador::ast_node_types::PRINTF:
        case gerador::ast_node_types::SCANF:
            for(const void*& i : node.get_rep()._ast_call.params) {
                declare_edge_dot(*((gerador::ast_node*) i), 
                    "    n" + std::to_string(current_node) + " -> n" + std::to_string(node_index));
            }
            break;  
        case gerador::ast_node_types::TERNARY:
            declare_edge_dot(*((gerador::ast_node*) node.get_rep()._ast_ternary.condition), 
                    "    n" + std::to_string(current_node) + " -> n" + std::to_string(node_index));
            declare_edge_dot(*((gerador::ast_node*) node.get_rep()._ast_ternary.then_body), 
                    "    n" + std::to_string(current_node) + " -> n" + std::to_string(node_index));
            declare_edge_dot(*((gerador::ast_node*) node.get_rep()._ast_ternary.else_body), 
                    "    n" + std::to_string(current_node) + " -> n" + std::to_string(node_index));
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
            declare_edge_dot(*((gerador::ast_node*) node.get_rep()._ast_binary.left), 
                    "    n" + std::to_string(current_node) + " -> n" + std::to_string(node_index));
            declare_edge_dot(*((gerador::ast_node*) node.get_rep()._ast_binary.right), 
                    "    n" + std::to_string(current_node) + " -> n" + std::to_string(node_index));
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
            declare_edge_dot(*((gerador::ast_node*) node.get_rep()._ast_unary.operand), 
                    "    n" + std::to_string(current_node) + " -> n" + std::to_string(node_index));
            break;
        default:
            break;
    }
}

void gerador::reset_index() {
    node_index = 0;
}