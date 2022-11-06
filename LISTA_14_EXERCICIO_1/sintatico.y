%{
#include <stdio.h>
#include <string.h>

/* Variáveis da ferramenta */
extern int yylex();
void yyerror(char *s);
extern char* yytext;
/* Variáveis de contole */
extern char* error_line_ptr,
           * prev_line_ptr;
extern int flag;
extern unsigned long count,
                     line,
                     col,
                     prev_line_num,
                     prev_col,
                     error_count;
extern const int ERROR_DISPLAY_LINE_SIZE;

void get_remaining_line();

%}

%token ID
%token NUM_INTEIRO
%token NUM_REAL
%token L_PAREN
%token R_PAREN
%token SEN
%token COS
%token TAN
%token ABS
%token PLUS
%token MINUS
%token MULTIPLY
%token DIV
%token POW
%token REMAINDER
%token END_OF_LINE
%token END_OF_FILE

%start S

%%

S
    : Expressao END_OF_LINE { printf("EXPRESSAO CORRETA"); return 0; }
    ;

Expressao
    : L_PAREN Expressao R_PAREN { }
    | Expressao OperadorBinario Expressao { }
    | Sinal Expressao { }
    | Funcao L_PAREN Expressao R_PAREN { }
    | Numero { }
    ;

OperadorBinario
    : PLUS { }
    | MINUS { }
    | MULTIPLY { }
    | DIV { }
    | POW { }
    | REMAINDER { }
    ;

Sinal
    : PLUS { }
    | MINUS { }
    ;

Funcao
    : SEN { }
    | COS { }
    | TAN { }
    | ABS { }
    ;

Numero
    : NUM_INTEIRO { }
    | NUM_REAL { }
    | ID { }
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