#ifndef AST_HH
#define AST_HH

#include "ast_node.hh"

namespace gerador {
    class ast {
        ast_node* program;

        public:
        ast() {};
        ~ast() { delete program; };

        void set_program(ast_node* p);

        void draw();

        void compile(gerador::instruction_set& is);
    };
}

#endif