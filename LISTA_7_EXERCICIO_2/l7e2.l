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

"if" {

    if(tokens) std::cout << '\n'; 
    std::cout << yytext << ' ' << "IF"; 
    tokens++;
}
[a-z][a-z0-9]* {

    if(tokens) std::cout << '\n'; 
    std::cout << yytext << ' ' << "ID"; 
    tokens++;
}
[0-9]+ {

    if(tokens) std::cout << '\n'; 
    std::cout << yytext << ' ' << "NUM"; 
    tokens++;
}
([0-9]*"."[0-9]+)|([0-9]+"."[0-9]*) {

    if(tokens) std::cout << '\n'; 
    std::cout << yytext << ' ' << "REAL"; 
    tokens++;
}
--[a-z]+\n {

    yytext[strlen(yytext) - 1] = '\0';

    if(tokens) std::cout << '\n'; 
    std::cout << yytext << ' ' << "comment"; 
    tokens++;
}
[ \t\a] {

    if(tokens) std::cout << '\n'; 
    std::cout << "white space"; 
    tokens++;
}
. {
    if(tokens) std::cout << '\n'; 
    std::cout << yytext << ' ' << "error"; 
    tokens++;
}

%%

int main(int argc, char* argv[]){

    yylex();

    return 0;
}