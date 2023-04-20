#include <iostream>

#include "ast.hh"

void gerador::ast::set_program(gerador::ast_node* p) {
    program = p;
}

void gerador::ast::compile(gerador::instruction_set& is) {
    program->generate_code(is);
}

void gerador::ast::draw() {
    std::cout << "digraph ast {" << std::endl;
    program->visit(declare_node_dot);
    reset_index();
    declare_edge_dot(*program, "");
    std::cout << "}" << std::endl;
}