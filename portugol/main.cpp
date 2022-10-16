#include <iostream>

#include "lexer.hpp"
#include "automaton.hpp"

int main(){
    std::vector<lexeme> tokens;

    lexer lexer(transitions, states);
    lexer.start_lexing(std::cin);
    
    lexer.get_tokens(tokens);
    
    // imprima vetor tokens
    for(int i = 0; i < tokens.size(); i++){
        tokens[i].print();
    }

    return 0;
}