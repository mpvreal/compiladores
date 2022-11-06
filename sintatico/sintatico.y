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
extern unsigned long count,
                     line,
                     col,
                     prev_line_num,
                     prev_col;
extern const int ERROR_DISPLAY_LINE_SIZE;

void get_remaining_line();

%}
%token IDENTIFIER
%token NUM_INTEGER
%token NUM_OCTAL
%token NUM_HEXA
%token STRING
%token CHARACTER
%token VOID
%token INT
%token CHAR
%token RETURN
%token BREAK
%token SWITCH
%token CASE
%token DEFAULT
%token DO
%token WHILE
%token FOR
%token IF
%token ELSE
%token TYPEDEF
%token STRUCT
%token PLUS
%token MINUS
%token MULTIPLY
%token DIV
%token REMAINDER
%token INC
%token DEC
%token BITWISE_AND
%token BITWISE_OR
%token BITWISE_NOT
%token BITWISE_XOR
%token NOT
%token LOGICAL_AND
%token LOGICAL_OR
%token EQUAL
%token NOT_EQUAL
%token LESS_THAN
%token GREATER_THAN
%token LESS_EQUAL
%token GREATER_EQUAL
%token R_SHIFT
%token L_SHIFT
%token ASSIGN
%token ADD_ASSIGN
%token MINUS_ASSIGN
%token SEMICOLON
%token COMMA
%token COLON
%token L_PAREN
%token R_PAREN
%token L_CURLY_BRACKET
%token R_CURLY_BRACKET
%token L_SQUARE_BRACKET
%token R_SQUARE_BRACKET
%token TERNARY_CONDITIONAL
%token NUMBER_SIGN
%token POINTER
%token PRINTF
%token SCANF
%token DEFINE
%token EXIT
%token END_OF_FILE

%start Programa

%%

Programa
    : Declaracoes Programa_prime END_OF_FILE {
        if(count > 0)
            putchar('\n');
        printf("SUCCESSFUL COMPILATION."); 
        
        return 0; 
    }
    | Funcao Programa_prime END_OF_FILE { 
        if(count > 0)
            putchar('\n');
        printf("SUCCESSFUL COMPILATION."); 
        
        return 0; 
    }
    ;

Programa_prime
    : Programa { }
    | /* vazio */ { }
    ;

Declaracoes
    : NUMBER_SIGN DEFINE IDENTIFIER Expressao { }
    | DeclaraVariaveis { }
    | DeclaraPrototipos { }
    ;

Funcao
    : Tipo Estrela IDENTIFIER Parametros L_CURLY_BRACKET SecaoVariaveis Comandos R_CURLY_BRACKET { }
    ;

SecaoVariaveis
    : DeclaraVariaveis SecaoVariaveis { }
    | /* vazio */ { }
    ;

DeclaraVariaveis
    : Tipo ListaVariaveis SEMICOLON { }
    ;

ListaVariaveis 
    : Estrela IDENTIFIER Dimensao Inicializacao VariaveisContinuacao { }
    ;

Inicializacao
    : ASSIGN ExprAtrib { }
    | /* vazio */ { }
    ;

VariaveisContinuacao
    : COMMA ListaVariaveis { }
    | /* vazio */ { }
    ;

Estrela
    : MULTIPLY Estrela { }
    | /* vazio */ { }
    ;

Dimensao 
    : L_SQUARE_BRACKET Expressao R_SQUARE_BRACKET Dimensao { }
    | /* vazio */
    ;

DeclaraPrototipos
    : Tipo Estrela IDENTIFIER Parametros SEMICOLON { }
    ;

Parametros
    : L_PAREN ListaParametros R_PAREN { }
    ;

ListaParametros
    : Tipo Estrela IDENTIFIER Dimensao ParametrosContinuacao { }
    | /* vazio */ { }
    ;

ParametrosContinuacao
    : COMMA Tipo Estrela IDENTIFIER Dimensao ParametrosContinuacao { }
    | /* vazio */
    ;

Tipo
    : INT { }
    | CHAR { }
    | VOID { }
    ;

Bloco
    : L_CURLY_BRACKET Comandos R_CURLY_BRACKET { }
    ;

Comandos
    : Comando ComandosContinuacao { }
    ;

ComandosContinuacao
    : Comando ComandosContinuacao { }
    | /* vazio */ { }
    ;

Comando
    : DO Bloco WHILE L_PAREN Expressao R_PAREN SEMICOLON { }
    | IF L_PAREN Expressao R_PAREN Bloco Else { }
    | WHILE L_PAREN Expressao R_PAREN Bloco { }
    | FOR L_PAREN ExprOmitivel SEMICOLON ExprOmitivel SEMICOLON ExprOmitivel R_PAREN Bloco { }
    | PRINTF L_PAREN STRING ExprPrintf R_PAREN SEMICOLON   { }
    | SCANF L_PAREN STRING COMMA BITWISE_AND IDENTIFIER R_PAREN SEMICOLON { }
    | EXIT L_PAREN Expressao R_PAREN SEMICOLON { }
    | RETURN ExprOmitivel SEMICOLON { }
    | Expressao SEMICOLON { }
    | Bloco { }
    | SEMICOLON { }
    ;

ExprPrintf
    :  COMMA Expressao { }
    | /* vazio */ { }
    ;

ExprOmitivel
    : Expressao { }
    | /* vazio */
    ;

Else
    : ELSE Bloco { }
    | /* vazio */{ }
    ;

Expressao
    : Expressao COMMA ExprAtrib { }
    | ExprAtrib { }
    ;

ExprAtrib
    : ExprCond { }
    | ExprUnaria Atribuicao ExprAtrib { }

Atribuicao
    : ASSIGN { }
    | ADD_ASSIGN
    | MINUS_ASSIGN
    ;

ExprCond
    : ExprOrLogico OperadorTernario { }

OperadorTernario
    : TERNARY_CONDITIONAL ExprCond COLON ExprCond { }
    | /* vazio */ { }
    ;

ExprOrLogico
    : ExprAndLogico { }
    | ExprOrLogico LOGICAL_OR ExprAndLogico { }
    ;

ExprAndLogico
    : ExprOr { }
    | ExprAndLogico LOGICAL_AND ExprOr { }

ExprOr
    : ExprXor { }
    | ExprOr BITWISE_OR ExprXor { }

ExprXor
    : ExprAnd { }
    | ExprXor BITWISE_XOR ExprAnd { }

ExprAnd
    : ExprIgualdade { }
    | ExprAnd BITWISE_AND ExprIgualdade { }

ExprIgualdade
    : ExprRelacional { }
    | ExprIgualdade OperadorIgualdade ExprRelacional { }
    ;

OperadorIgualdade
    : EQUAL { }
    | NOT_EQUAL { }
    ;

ExprRelacional
    : ExprShift { }
    | ExprRelacional OperadorRelacional ExprShift { }

OperadorRelacional
    : LESS_THAN { }
    | GREATER_THAN { }
    | LESS_EQUAL { }
    | GREATER_EQUAL { }
    ;

ExprShift
    : ExprAditiva { }
    | ExprShift OperadorShift ExprAditiva { }
    ;

OperadorShift
    : L_SHIFT { }
    | R_SHIFT { }
    ;

ExprAditiva
    : ExprMultiplicativa { }
    | ExprAditiva OperadorAditivo ExprMultiplicativa { }
    ;

OperadorAditivo
    : PLUS { }
    | MINUS { }
    ;

ExprMultiplicativa
    : Cast { }
    | ExprMultiplicativa OperadorMultiplicativo ExprUnaria { }
    ;

OperadorMultiplicativo
    : MULTIPLY { }
    | DIV { }
    | REMAINDER { }
    ;

Cast
    : L_PAREN Tipo Estrela R_PAREN Cast { }
    | ExprUnaria { }
    ;

ExprUnaria
    : INC ExprUnaria     { }
    | DEC ExprUnaria { }
    | BITWISE_AND ExprUnaria
    | PLUS ExprUnaria { }
    | MINUS ExprUnaria { }
    | MULTIPLY ExprUnaria { }
    | BITWISE_NOT ExprUnaria
    | NOT ExprUnaria { }
    | ExprPostfix { }
    ;

ExprPostfix
    : ExprPrimaria { }
    | ExprPostfix ExprPostfix_prime { }
    ;

ExprPostfix_prime
    : L_SQUARE_BRACKET Expressao R_SQUARE_BRACKET { }
    | INC { }
    | DEC { }
    | L_PAREN ExprAtrib_prime R_PAREN { }
    ;

ExprAtrib_prime
    : ExprAtrib ExprAtribContinuacao { }
    | /* vazio */ { }

ExprAtribContinuacao
    : COMMA ExprAtrib ExprAtribContinuacao { }
    | /* vazio */ { }

ExprPrimaria
    : IDENTIFIER { }
    | Numero { }
    | CHARACTER { }
    | STRING { }
    | L_PAREN Expressao R_PAREN { }
    ;

Numero
    : NUM_INTEGER { }
    | NUM_OCTAL { }
    | NUM_HEXA { }
    ;
%%

void yyerror(char *s) {
    col -= strlen(yytext);

    if(count > 0)
        putchar('\n');

    if(strlen(error_line_ptr) == 0){
        error_line_ptr = prev_line_ptr;
        line = prev_line_num;
        col = prev_col;
    }

    if(yychar == END_OF_FILE){
        printf("error:syntax:%ld:%ld: expected declaration or statement at end of input\n",
            line, col);
    }
    else{
        printf("error:syntax:%ld:%ld: %s\n", line, col, yytext);
        get_remaining_line();
    }
    puts(error_line_ptr);
    while(--col)
        putchar(' ');
    putchar('^');
}

int main(int argc, char *argv[]){
    yyparse();

    return 0;
}