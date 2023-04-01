#include <list>
#include <string>

#include "ast.hh"

int main() {
    // gerador::ast_node* node = new gerador::ast_node(gerador::ast_node_types::ID, std::string("teste"));
    // delete node;

    std::list<void*> l = { NULL, NULL, NULL };

    gerador::ast_node* node = new gerador::ast_node(gerador::ast_node_types::WHILE, NULL, l);
    delete node;

    return 0;
}