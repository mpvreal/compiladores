#include <iostream>

#include "lexer.hpp"
#include "parser.hpp"
#include "automaton.hpp"

int main(){
    std::vector<lexeme> tokens;
    lexer lexico = lexer(transitions, states);
    parser sintatico = parser();

    lexico.start_lexing(std::cin);
    lexico.get_tokens(tokens);
    
    // imprima vetor tokens
    // for(int i = 0; i < tokens.size(); i++){
    //     tokens[i].print();
    // }

    sintatico.start_parsing(tokens);

    return 0;
}