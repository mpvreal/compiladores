%option noyywrap

%{
/* ALUNO:   MATHEUS PIRES VILA REAL
 * Nº:      202000560352
 */
#include <iostream>

int tokens = 0;

%}

%%

"+" {
    if(tokens) std::cout << '\n'; std::cout << yytext; 
    tokens++;
    }
"-" { 
    if(tokens) std::cout << '\n'; std::cout << yytext; 
    tokens++; 
    }
[a-z][a-z0-9]* { 
               if(tokens) std::cout << '\n'; std::cout << yytext;
               tokens++;
               }
[0-9]+ { 
       if(tokens) std::cout << '\n'; std::cout << yytext; 
       tokens++; 
       }
[0-9]+e("+"|-)?[0-9]+ {
                      if(tokens) std::cout << '\n'; std::cout 
                        << yytext;
                      tokens++; 
                      }
\n { 
   tokens++;
   }
. { 
  if(tokens) std::cout << '\n'; std::cout << ("ERRO"); 
  tokens++; 
  }

%%

int main(int argc, char* argv[]){

    yylex();
    return 0;
}