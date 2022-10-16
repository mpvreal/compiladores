/* ALUNO:   MATHEUS PIRES VILA REAL
 * Nº:      202000560352
 */
#include <iostream>

#include "parser.hpp"

int main(int argc, char* argv[]){

    std::string input = "";
    char ch;

    while((ch = getc(stdin))){
        
        input.append(1, ch);

        if(ch == EOF)
            break;
    }

    parser sintatico(input);

    sintatico.parse();
    // sintatico.show_tokens();

    return 0;
}