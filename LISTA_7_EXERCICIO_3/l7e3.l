%option noyywrap

%{
/* ALUNO:   MATHEUS PIRES VILA REAL
 * Nº:      202000560352
 */
#include <iostream>
#include <string.h>

int tokens = 0;

%}

%%

(aba)+ {

    if(tokens) std::cout << '\n'; 
    std::cout << yytext << ' ' << "(action 1)"; 
    tokens++;
}
ab*a {

    if(tokens) std::cout << '\n'; 
    std::cout << yytext << ' ' << "(action 2)"; 
    tokens++;
}
a|b {

    if(tokens) std::cout << '\n'; 
    std::cout << yytext << ' ' << "(action 3)"; 
    tokens++;
}

%%

int main(int argc, char* argv[]){

    yylex();

    return 0;
}