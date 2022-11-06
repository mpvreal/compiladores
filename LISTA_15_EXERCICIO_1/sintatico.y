%{
#include <stdio.h>
#include <string.h>

#include "hashtable.h"

HashTable ht = newHashTable(100);


%}

%token ID
%token INT
%token FLOAT
%token CHAR
%token END

%start S

%%

S
    : D D_prime END
    ;

D
    : T I
    ;

D_prime
    : D D_prime
    | /* empty */
    ;

T
    : INT
    | FLOAT
    | CHAR
    ;

I
    : ID
    | I ',' ID
    ;

%%

void yyerror(char *s) {
    col -= strlen(yytext);

    if(count > 0)
        putchar('\n');

    if(yychar == END_OF_FILE || yychar == END_OF_LINE){
        printf("A expressao terminou de forma inesperada.");
    }
    else{
        printf("Erro de sintaxe na coluna [%d]: %s", col, yytext);
    }
    ++count;
    /* get_remaining_line(); */
}

int main(int argc, char *argv[]){
    yylex();

    if(error_count > 0){
        putchar(']');
        return 1;
    }
    
    flag = 1;
    
    while(yychar != END_OF_FILE)
        yyparse();

    return 0;
}