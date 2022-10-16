/* ALUNO:   MATHEUS PIRES VILA REAL
 * Nº:      202000560352
 */
#include <iostream>

#include "lexer.hpp"
#include "automaton.hpp"

int main(){

    lexer analisador_lexico(transitions, finals, STATES);

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