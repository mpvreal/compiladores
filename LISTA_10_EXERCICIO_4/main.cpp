#include <iostream>

#include "lexer.hpp"
#include "parser.hpp"
#include "automaton.hpp"

int main(){
    lexeme teste;
    lexer lex = lexer(transitions, states);
    parser sintatico = parser();

    while(!sintatico.done_parsing()){
        lex.tokenize(std::cin, teste);
        sintatico.parse(teste);
    }

    std::cout << "CADEIA ACEITA";

    return 0;
}