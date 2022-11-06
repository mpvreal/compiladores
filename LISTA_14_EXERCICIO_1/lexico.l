%option noyywrap

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sintatico.tab.h"

#define ERROR_LINE_DISPLAY_SIZE 4096

int flag = 0;

char error_line[ERROR_LINE_DISPLAY_SIZE],
     prev_line[ERROR_LINE_DISPLAY_SIZE];

char* error_line_ptr = error_line,
    * prev_line_ptr = prev_line;

unsigned long count = 0,
              line = 1,
              col = 1,
              prev_line_num = 1,
              prev_col = 1,
              error_count = 0;

static void comment();

%}

%%

"("         { col += strlen(yytext); return L_PAREN; }
")"         { col += strlen(yytext); return R_PAREN; }
"sen"       { col += strlen(yytext); return SEN; }
"cos"       { col += strlen(yytext); return COS; }
"tan"       { col += strlen(yytext); return TAN; }
"abs"       { col += strlen(yytext); return ABS; }
"+"         { col += strlen(yytext); return PLUS; }
"-"         { col += strlen(yytext); return MINUS; }
"*"         { col += strlen(yytext); return MULTIPLY; }
"/"         { col += strlen(yytext); return DIV; }
"^"         { col += strlen(yytext); return POW; }
"%"         { col += strlen(yytext); return REMAINDER; }

[_a-zA-Z][_a-zA-Z0-9]*              { col += strlen(yytext); return ID; }
[0-9][0-9]*                         { col += strlen(yytext); return NUM_INTEIRO; }
([0-9]+\.[0-9]*)|([0-9]*\.[0-9]+)   { col += strlen(yytext); return NUM_REAL; }
[ \t]                               { col += strlen(yytext); }
[\r\v\f\b\a\0]+     /* white space */
\n                                  { col = 1; return END_OF_LINE; }
<<EOF>>                             { return END_OF_FILE;}
. { 
    if(flag){
        if(error_count < 1){
            if(count > 0)
                putchar('\n');
            printf("Caractere(s) invalido(s) -> [%s", yytext);
        }
        else {
            printf(",%s", yytext);
        }
        ++error_count;
    }
}

%%

void get_remaining_line(){
    char ch;
    
    while( (ch = input()) != EOF && ch != '\n' && 
        strlen(error_line) < ERROR_LINE_DISPLAY_SIZE){
        continue;
    }
}

static void comment(int start_line, int start_col){
    int ch,
        prev = '*';
    
    while( (ch = input()) > 0){
        
        col++;
        switch(ch){

            case '*':
                if( (ch = input()) == '/'){
                    col += 1;
                    return;
                }
                unput(ch);
                ch = '*';

                if(prev == '/'){
                    if(count > 0)
                        putchar('\n');
                    printf("warning:%d:%d: \'/*\' within block comment"
                        , line, col - 2);
                    ++count;
                }
                break;

            case '\n':
                line++;
                col = 1;
                break;

            default:
                break;
        }
        prev = ch;
    }

    ++count;

    printf("error:lexical:%d:%d: unterminated comment", 
        start_line, start_col); 
}