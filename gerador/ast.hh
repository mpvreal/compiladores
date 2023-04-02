#ifndef AST_HH
#define AST_HH

#include "ast_node.hh"

namespace gerador {
    class ast {
        ast_node* program;

        public:
        ast() {};
        ~ast() {};

        void set_program(ast_node* p);
    };
}

#endif