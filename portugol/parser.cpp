#include <iostream>

#include "parser.hpp"

inline void parser::error(lexeme& l){
    std::cout << "ERRO DE SINTAXE. Linha: " << l.get_line() 
        << " Coluna: " << l.get_column() << " -> '" << 
        l.get_content() << '\'';

    exit(1);
}