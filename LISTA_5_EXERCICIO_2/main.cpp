/* ALUNO:   MATHEUS PIRES VILA REAL
 * Nº:      202000560352
 */
#include <iostream>

#include "lexer.hpp"
#include "automaton.hpp"

int main(){

    struct state states[] = {
        {"dead state", false}, {"init", false}, {"ID", true}, 
        {"IF", true}, {"ID", true}, {"error", true}, 
        {"REAL", true}, {"NUM", true}, {"REAL", true}, 
        {"error", true}, {"10", false}, {"comment", true}, 
        {"white space", true}, {"error", true}
    };

    lexer analisador_lexico(transitions, states, STATES);

    std::string str;
    char ch = 0;

    while((ch = getc(stdin))){
        
        str.append(1, ch);

        if(ch == EOF)
            break;
    }
    
    analisador_lexico.tokenize(str);

    return 0;
}