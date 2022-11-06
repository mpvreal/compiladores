%option noyywrap

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sintatico.tab.h"

#define ERROR_LINE_DISPLAY_SIZE 4096

char error_line[ERROR_LINE_DISPLAY_SIZE],
     prev_line[ERROR_LINE_DISPLAY_SIZE];

char* error_line_ptr = error_line,
    * prev_line_ptr = prev_line;

unsigned long count = 0,
              line = 1,
              col = 1,
              prev_line_num = 1,
              prev_col = 1;

static void comment();

%}

%%
      
"void"      { col += strlen(yytext); strncat(error_line, yytext, strlen(yytext)); return VOID; }
"int"       { col += strlen(yytext); strncat(error_line, yytext, strlen(yytext)); return INT; }
"char"      { col += strlen(yytext); strncat(error_line, yytext, strlen(yytext)); return CHAR; }
"return"    { col += strlen(yytext); strncat(error_line, yytext, strlen(yytext)); return RETURN; }
"break"     { col += strlen(yytext); strncat(error_line, yytext, strlen(yytext)); return BREAK; }
"switch"    { col += strlen(yytext); strncat(error_line, yytext, strlen(yytext)); return SWITCH; }
"case"      { col += strlen(yytext); strncat(error_line, yytext, strlen(yytext)); return CASE; }
"default"   { col += strlen(yytext); strncat(error_line, yytext, strlen(yytext)); return DEFAULT; }
"do"        { col += strlen(yytext); strncat(error_line, yytext, strlen(yytext)); return DO; }
"while"     { col += strlen(yytext); strncat(error_line, yytext, strlen(yytext)); return WHILE; }
"for"       { col += strlen(yytext); strncat(error_line, yytext, strlen(yytext)); return FOR; }
"if"        { col += strlen(yytext); strncat(error_line, yytext, strlen(yytext)); return IF; }
"else"      { col += strlen(yytext); strncat(error_line, yytext, strlen(yytext)); return ELSE; }
"typedef"   { col += strlen(yytext); strncat(error_line, yytext, strlen(yytext)); return TYPEDEF; }
"struct"    { col += strlen(yytext); strncat(error_line, yytext, strlen(yytext)); return STRUCT; }
"/*"        { col += 2; strncat(error_line, yytext, strlen(yytext)); comment(line, col - 2); }
"//"[^\n]*  { strncat(error_line, yytext, strlen(yytext)); }
"++"        { col += strlen(yytext); strncat(error_line, yytext, strlen(yytext)); return INC; }
"+"         { col += strlen(yytext); strncat(error_line, yytext, strlen(yytext)); return PLUS; }
"--"        { col += strlen(yytext); strncat(error_line, yytext, strlen(yytext)); return DEC; }
"-"         { col += strlen(yytext); strncat(error_line, yytext, strlen(yytext)); return MINUS; }
"->"        { col += strlen(yytext); strncat(error_line, yytext, strlen(yytext)); return POINTER; }
"+="        { col += strlen(yytext); strncat(error_line, yytext, strlen(yytext)); return ADD_ASSIGN; }
"-="        { col += strlen(yytext); strncat(error_line, yytext, strlen(yytext)); return MINUS_ASSIGN; }
"*"         { col += strlen(yytext); strncat(error_line, yytext, strlen(yytext)); return MULTIPLY; }
"/"         { col += strlen(yytext); strncat(error_line, yytext, strlen(yytext)); return DIV; }
"%"         { col += strlen(yytext); strncat(error_line, yytext, strlen(yytext)); return REMAINDER; }
"&&"        { col += strlen(yytext); strncat(error_line, yytext, strlen(yytext)); return LOGICAL_AND; }
"&"         { col += strlen(yytext); strncat(error_line, yytext, strlen(yytext)); return BITWISE_AND; }
"||"        { col += strlen(yytext); strncat(error_line, yytext, strlen(yytext)); return LOGICAL_OR; }
"|"         { col += strlen(yytext); strncat(error_line, yytext, strlen(yytext)); return BITWISE_OR; }
"=="        { col += strlen(yytext); strncat(error_line, yytext, strlen(yytext)); return EQUAL; }
"="         { col += strlen(yytext); strncat(error_line, yytext, strlen(yytext)); return ASSIGN; }
">>"        { col += strlen(yytext); strncat(error_line, yytext, strlen(yytext)); return R_SHIFT; }
"<<"        { col += strlen(yytext); strncat(error_line, yytext, strlen(yytext)); return L_SHIFT; }
"~"         { col += strlen(yytext); strncat(error_line, yytext, strlen(yytext)); return BITWISE_NOT; }
"^"         { col += strlen(yytext); strncat(error_line, yytext, strlen(yytext)); return BITWISE_XOR; }
"!="        { col += strlen(yytext); strncat(error_line, yytext, strlen(yytext)); return NOT_EQUAL; }
"<="        { col += strlen(yytext); strncat(error_line, yytext, strlen(yytext)); return LESS_EQUAL; }
">="        { col += strlen(yytext); strncat(error_line, yytext, strlen(yytext)); return GREATER_EQUAL; }
"!"         { col += strlen(yytext); strncat(error_line, yytext, strlen(yytext)); return NOT; }
"<"         { col += strlen(yytext); strncat(error_line, yytext, strlen(yytext)); return LESS_THAN; }
">"         { col += strlen(yytext); strncat(error_line, yytext, strlen(yytext)); return GREATER_THAN; }
";"         { col += strlen(yytext); strncat(error_line, yytext, strlen(yytext)); return SEMICOLON; }
","         { col += strlen(yytext); strncat(error_line, yytext, strlen(yytext)); return COMMA; }
":"         { col += strlen(yytext); strncat(error_line, yytext, strlen(yytext)); return COLON; }
"("         { col += strlen(yytext); strncat(error_line, yytext, strlen(yytext)); return L_PAREN; }
")"         { col += strlen(yytext); strncat(error_line, yytext, strlen(yytext)); return R_PAREN; }
"{"         { col += strlen(yytext); strncat(error_line, yytext, strlen(yytext)); return L_CURLY_BRACKET; }
"}"         { col += strlen(yytext); strncat(error_line, yytext, strlen(yytext)); return R_CURLY_BRACKET; }
"["         { col += strlen(yytext); strncat(error_line, yytext, strlen(yytext)); return L_SQUARE_BRACKET; }
"]"         { col += strlen(yytext); strncat(error_line, yytext, strlen(yytext)); return R_SQUARE_BRACKET; }
"?"	        { col += strlen(yytext); strncat(error_line, yytext, strlen(yytext)); return TERNARY_CONDITIONAL; }
"#"         { col += strlen(yytext); strncat(error_line, yytext, strlen(yytext)); return NUMBER_SIGN; }
"printf"    { col += strlen(yytext); strncat(error_line, yytext, strlen(yytext)); return PRINTF; }
"scanf"     { col += strlen(yytext); strncat(error_line, yytext, strlen(yytext)); return SCANF; }
"define"    { col += strlen(yytext); strncat(error_line, yytext, strlen(yytext)); return DEFINE; }
"exit"      { col += strlen(yytext); strncat(error_line, yytext, strlen(yytext)); return EXIT; }

[_a-zA-Z][_a-zA-Z0-9]* {
    if(strlen(yytext) > 255){
        if(count > 0)
            putchar('\n');
        printf("error:lexical:%d:%d: identifier too long", line, 
            col);
    }
    else{
        col += strlen(yytext); strncat(error_line, yytext, strlen(yytext));
        return IDENTIFIER;
    }
}

"0"[xX][a-fA-F0-9]+ { col += strlen(yytext); strncat(error_line, yytext, strlen(yytext)); return NUM_HEXA; }
"0"[1-7][0-7]*      { col += strlen(yytext); strncat(error_line, yytext, strlen(yytext)); return NUM_OCTAL; }
[0-9][0-9]*         { col += strlen(yytext); strncat(error_line, yytext, strlen(yytext)); return NUM_INTEGER; }
["]([^"\\\n]|\\.|\\\n)*["] { col += strlen(yytext); strncat(error_line, yytext, strlen(yytext)); return STRING; }
'([^'\\\n]|\\.)'    { col += strlen(yytext); strncat(error_line, yytext, strlen(yytext)); return CHARACTER; }
\n+                 { prev_line_num = line; prev_col = col;
                      line += strlen(yytext); col = 1;
                      strcpy(prev_line, error_line);
                      strcpy(error_line, ""); 
                    }
[ \t]               { col += strlen(yytext); strncat(error_line, yytext, strlen(yytext)); }
[\r\v\f\b\a\0]+     /* white space */
<<EOF>>             { return END_OF_FILE;}
. { 
    printf("error:lexical:%d:%d: %s", line, col, yytext);
    ++col;
    exit(EXIT_FAILURE);
}

%%

void get_remaining_line(){
    char ch;
    
    while( (ch = input()) != EOF && ch != '\n' && 
        strlen(error_line) < ERROR_LINE_DISPLAY_SIZE){
        strncat(error_line, &ch, 1);
    }
}

static void comment(int start_line, int start_col){
    int ch,
        prev = '*';
    
    while( (ch = input()) > 0){
        strncat(error_line, &ch, 1);
        col++;
        switch(ch){

            case '*':
                if( (ch = input()) == '/'){
                    col += 1;
                    strncat(error_line, &ch, 1);
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
                prev_line_num = line; prev_col = col;
                strcpy(prev_line, error_line);
                strcpy(error_line, "");
                break;

            default:
                break;
        }
        prev = ch;
    }

    ++count;

    printf("error:lexical:%d:%d: unterminated comment", 
        start_line, start_col);
    exit(EXIT_FAILURE);
}