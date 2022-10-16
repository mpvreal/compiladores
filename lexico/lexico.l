%option noyywrap

%{
/* ALUNO:   MATHEUS PIRES VILA REAL
 * Nº:      202000560352
 */

#include <stdio.h>
#include <string.h>

int tokens = 0;

int line = 1;
int column = 1;

static void comment();

%}

%%
      
"void" { 

    if(tokens > 0)
        putchar('\n');

    tokens++;
    printf("VOID");
    column += strlen(yytext);
}
"int" { 

    if(tokens > 0)
        putchar('\n');

    tokens++;
    printf("INT");
    column += strlen(yytext);
}
"char" { 

    if(tokens > 0)
        putchar('\n');

    tokens++;
    printf("CHAR");
    column += strlen(yytext);
}
"return" { 

    if(tokens > 0)
        putchar('\n');

    tokens++;
    printf("RETURN");
    column += strlen(yytext);
}
"break" { 

    if(tokens > 0)
        putchar('\n');

    tokens++;
    printf("BREAK");
    column += strlen(yytext);
}
"switch" { 

    if(tokens > 0)
        putchar('\n');

    tokens++;
    printf("SWITCH");
    column += strlen(yytext);
}
"case" { 

    if(tokens > 0)
        putchar('\n');

    tokens++;
    printf("CASE");
    column += strlen(yytext);
}
"default" { 

    if(tokens > 0)
        putchar('\n');

    tokens++;
    printf("DEFAULT");
    column += strlen(yytext);
}
"do" { 

    if(tokens > 0)
        putchar('\n');

    tokens++;
    printf("DO");
    column += strlen(yytext);
}
"while" { 

    if(tokens > 0)
        putchar('\n');

    tokens++;
    printf("WHILE");
    column += strlen(yytext);
}
"for" { 

    if(tokens > 0)
        putchar('\n');

    tokens++;
    printf("FOR");
    column += strlen(yytext);
}
"if" { 

    if(tokens > 0)
        putchar('\n');

    tokens++;
    printf("IF");
    column += strlen(yytext);
}
"else" { 

    if(tokens > 0)
        putchar('\n');

    tokens++;
    printf("ELSE");
    column += strlen(yytext);
}
"typedef" { 

    if(tokens > 0)
        putchar('\n');

    tokens++;
    printf("TYPEDEF");
    column += strlen(yytext);
}
"struct" { 

    if(tokens > 0)
        putchar('\n');

    tokens++;
    printf("STRUCT");
    column += strlen(yytext);
}
"/*" {

    column += 2;
    comment(line, column - 2);
}
"//"[^\n]*
"++" { 

    if(tokens > 0)
        putchar('\n');

    tokens++;
    printf("INC");
    column += strlen(yytext);
}
"+" { 

    if(tokens > 0)
        putchar('\n');

    tokens++;
    printf("PLUS");
    column += strlen(yytext);
}
"--" { 

    if(tokens > 0)
        putchar('\n');

    tokens++;
    printf("DEC");
    column += strlen(yytext);
}
"-" { 

    if(tokens > 0)
        putchar('\n');

    tokens++;
    printf("MINUS");
    column += strlen(yytext);
}
"->" { 

    if(tokens > 0)
        putchar('\n');

    tokens++;
    printf("POINTER");
    column += strlen(yytext);
}
"+=" { 

    if(tokens > 0)
        putchar('\n');

    tokens++;
    printf("ADD_ASSIGN");
    column += strlen(yytext);
}
"-=" { 

    if(tokens > 0)
        putchar('\n');

    tokens++;
    printf("MINUS_ASSIGN");
    column += strlen(yytext);
}
"*" { 

    if(tokens > 0)
        putchar('\n');

    tokens++;
    printf("MULTIPLY");
    column += strlen(yytext);
}
"/" { 

    if(tokens > 0)
        putchar('\n');

    tokens++;
    printf("DIV");
    column += strlen(yytext);
}
"%" { 

    if(tokens > 0)
        putchar('\n');

    tokens++;
    printf("REMAINDER");
    column += strlen(yytext);
}
"&&" { 

    if(tokens > 0)
        putchar('\n');

    tokens++;
    printf("LOGICAL_AND");
    column += strlen(yytext);
}
"&" { 

    if(tokens > 0)
        putchar('\n');

    tokens++;
    printf("BITWISE_AND");
    column += strlen(yytext);
}
"||" { 

    if(tokens > 0)
        putchar('\n');

    tokens++;
    printf("LOGICAL_OR");
    column += strlen(yytext);
}
"|" { 

    if(tokens > 0)
        putchar('\n');

    tokens++;
    printf("BITWISE_OR");
    column += strlen(yytext);
}
"==" { 

    if(tokens > 0)
        putchar('\n');

    tokens++;
    printf("EQUAL");
    column += strlen(yytext);
}
"=" { 

    if(tokens > 0)
        putchar('\n');

    tokens++;
    printf("ASSIGN");
    column += strlen(yytext);
}
">>" { 

    if(tokens > 0)
        putchar('\n');

    tokens++;
    printf("R_SHIFT");
    column += strlen(yytext);
}
"<<" { 

    if(tokens > 0)
        putchar('\n');

    tokens++;
    printf("L_SHIFT");
    column += strlen(yytext);
}
"~" { 

    if(tokens > 0)
        putchar('\n');

    tokens++;
    printf("BITWISE_NOT");
    column += strlen(yytext);
}
"^" { 

    if(tokens > 0)
        putchar('\n');

    tokens++;
    printf("BITWISE_XOR");
    column += strlen(yytext);
}
"!=" { 

    if(tokens > 0)
        putchar('\n');

    tokens++;
    printf("NOT_EQUAL");
    column += strlen(yytext);
}
"<=" { 

    if(tokens > 0)
        putchar('\n');

    tokens++;
    printf("LESS_EQUAL");
    column += strlen(yytext);
}
">=" { 

    if(tokens > 0)
        putchar('\n');

    tokens++;
    printf("GREATER_EQUAL");
    column += strlen(yytext);
}
"!" { 

    if(tokens > 0)
        putchar('\n');

    tokens++;
    printf("NOT");
    column += strlen(yytext);
}
"<" { 

    if(tokens > 0)
        putchar('\n');

    tokens++;
    printf("LESS_THAN");
    column += strlen(yytext);
}
">" { 

    if(tokens > 0)
        putchar('\n');

    tokens++;
    printf("GREATER_THAN");
    column += strlen(yytext);
}
";" { 

    if(tokens > 0)
        putchar('\n');

    tokens++;
    printf("SEMICOLON");
    column += strlen(yytext);
}
"," { 

    if(tokens > 0)
        putchar('\n');

    tokens++;
    printf("COMMA");
    column += strlen(yytext);
}
":" { 

    if(tokens > 0)
        putchar('\n');

    tokens++;
    printf("COLON");
    column += strlen(yytext);
}
"(" { 

    if(tokens > 0)
        putchar('\n');

    tokens++;
    printf("L_PAREN");
    column += strlen(yytext);
}
")" { 

    if(tokens > 0)
        putchar('\n');

    tokens++;
    printf("R_PAREN");
    column += strlen(yytext);
}
"{" { 

    if(tokens > 0)
        putchar('\n');

    tokens++;
    printf("L_CURLY_BRACKET");
    column += strlen(yytext);
}
"}" { 

    if(tokens > 0)
        putchar('\n');

    tokens++;
    printf("R_CURLY_BRACKET");
    column += strlen(yytext);
}
"[" { 

    if(tokens > 0)
        putchar('\n');

    tokens++;
    printf("L_SQUARE_BRACKET");
    column += strlen(yytext);
}
"]" { 

    if(tokens > 0)
        putchar('\n');

    tokens++;
    printf("R_SQUARE_BRACKET");
    column += strlen(yytext);
}
"?"	{ 

    if(tokens > 0)
        putchar('\n');

    tokens++;
    printf("TERNARY_CONDITIONAL");
    column += strlen(yytext);
}
"#" { 

    if(tokens > 0)
        putchar('\n');

    tokens++;
    printf("NUMBER_SIGN");
    column += strlen(yytext);
}
"printf" { 

    if(tokens > 0)
        putchar('\n');

    tokens++;
    printf("PRINTF");
    column += strlen(yytext);
}
"scanf" { 

    if(tokens > 0)
        putchar('\n');

    tokens++;
    printf("SCANF");
    column += strlen(yytext);
}
"define" { 

    if(tokens > 0)
        putchar('\n');

    tokens++;
    printf("DEFINE");
    column += strlen(yytext);
}
"exit" { 

    if(tokens > 0)
        putchar('\n');

    tokens++;
    printf("EXIT");
    column += strlen(yytext);
}
[_a-zA-Z][_a-zA-Z0-9]* {

    if(tokens > 0)
        putchar('\n');

    tokens++;

    if(strlen(yytext) > 255)
        printf("error:lexical:%d:%d: identifier too long", line, 
            column);
    else
        printf("IDENTIFIER(%s)", yytext);
    column += strlen(yytext);
}
"0"[xX][a-fA-F0-9]+ {

    if(tokens > 0)
        putchar('\n');

    tokens++;
    printf("NUM_HEXA(%s)", yytext);
    column += strlen(yytext);
}
"0"[1-7][0-7]* { 

    if(tokens > 0)
        putchar('\n');

    tokens++;
    printf("NUM_OCTAL(%s)", yytext);
    column += strlen(yytext);
}
[0-9][0-9]* { 

    if(tokens > 0)
        putchar('\n');

    tokens++;
    printf("NUM_INTEGER(%s)", yytext);
    column += strlen(yytext);
}
["]([^"\\\n]|\\.|\\\n)*["] {

    if(tokens > 0)
        putchar('\n');

    tokens++;
    printf("STRING(");
    for(int ch = 1; ch < strlen(yytext) - 1; ch++)
        printf("%c", yytext[ch]);
    printf(")");
    column += strlen(yytext);
}
'([^'\\\n]|\\.)' {

    if(tokens > 0)
        putchar('\n');

    tokens++;
    printf("CHARACTER(");
    for(int ch = 1; ch < strlen(yytext)-1;ch++)
        printf("%c", yytext[ch]);
    printf(")");
    column += strlen(yytext);
}
\n { 

    line++;
    column = 1;
}
[ \t]+ {

    column += strlen(yytext);
}
[\r\v\f\b\a\0]+ /* white space */
. { 

    if(tokens > 0)
        putchar('\n');

    tokens++;
    printf("error:lexical:%d:%d: %s", line, column, yytext);
    column++;
}

%%

static void comment(int start_line, int start_column){

    int ch,
        prev = '*';
    
    while( (ch = input()) > 0){
        
        column++;
        switch(ch){

            case '*':
                if( (ch = input()) == '/'){
                    column += 1;
                    return;
                }
                unput(ch);
                ch = '*';

                if(prev == '/'){
                    if(tokens > 0)
                        putchar('\n');
                    tokens++;    
                    printf("warning:%d:%d: \'/*\' within block comment"
                        , line, column - 2);
                }
                break;

            case '\n':
                line++;
                column = 1;
                break;

            default:
                break;
        }
        prev = ch;
    }

    if(tokens > 0)
        putchar('\n');
    tokens++;

    printf("error:lexical:%d:%d: unterminated comment", 
        start_line, start_column);
}

int main(int argc, char* argv[]){

	yylex();
    return 0;
}