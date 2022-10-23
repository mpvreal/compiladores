#include <iostream>

#include "lexer.hpp"
#include "parser.hpp"
#include "automaton.hpp"

int main(){
    lexeme teste;
    lexer lexico = lexer(transitions, states);
    parser sintatico = parser();

    while(!sintatico.done_parsing()){
        sintatico.parse(lexico.tokenize(std::cin, teste));
    }

    std::cout << "PROGRAMA CORRETO.";

    return 0;
}