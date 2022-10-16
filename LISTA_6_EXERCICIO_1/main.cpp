/* ALUNO:   MATHEUS PIRES VILA REAL
 * Nº:      202000560352
 */
#include <iostream>

#include "lexer.hpp"
#include "automaton.hpp"

int main(){

    struct state states[STATES] = {{"ERRO", false}, 
        {"1", false}, {"2", false}, {"ELE", true}, 
        {"4", false}, {"5", false}, {"ELA", true}, 
        {"7", false}, {"DELE", true}, {"9", false}, 
        {"DELA", true}, {"11", false}, {"12", false}, 
        {"GATO", true}, {"CARRO", true}, {"GATOS", true}, 
        {"CARROS", true}, {"MAIS", true}, {"MENOS", true}, 
        {"INTEIRO", true}, {"20", false}, {"21", false}, 
        {"REAL", true}
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