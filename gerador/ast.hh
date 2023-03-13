#ifndef AST_HH
#define AST_HH

#include "ast_node.hh"

namespace gerador {
    class ast {
        std::list<ast_node> program;

        public:
        ast() {};
        ~ast() {};
    };
}

#endif