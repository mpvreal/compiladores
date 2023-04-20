%option noyywrap

%{
#include <cstdio>
#include "ast.hh"
#include "sintatico.yy.hh"
extern YYSTYPE yylval;
%}

%%

"void"                      { return VOID; }
"char"                      { return CHAR; }
"int"                       { return INT; }
"CONSTANT"                  { return CONSTANT; }
"GLOBAL VARIABLE"           { return GLOBAL_VAR; }
"VARIABLE"                  { return VAR; }
"TYPE"                      { return TYPE; }
"FUNCTION"                  { return FUNCTION; }
"END_FUNCTION"              { return END_FUNCTION; }
"PARAMETER"                 { return PARAMETER; }
"VALUE"                     { return VALUE; }
"DO_WHILE"                  { return DO_WHILE; }
"IF"                        { return IF; }
"WHILE"                     { return WHILE; }
"FOR"                       { return FOR; }
"EXIT"                      { return EXIT; }
"RETURN"                    { return RETURN; }
"RETURN_TYPE"               { return RETURN_TYPE; }
"AST -->"                   { return AST; }
"+"                         { return PLUS; }
"-"                         { return MINUS; }
"*"                         { return MULTIPLY; }
"/"                         { return DIV; }
"%"                         { return REMAINDER; }
"&"                         { return BITWISE_AND; }
"|"                         { return BITWISE_OR; }
"^"                         { return BITWISE_XOR; }
"&&"                        { return LOGICAL_AND; }
"||"                        { return LOGICAL_OR; }
"=="                        { return EQUAL; }
"!="                        { return NOT_EQUAL; }
"<"                         { return LESS_THAN; }
">"                         { return GREATER_THAN; }
"<="                        { return LESS_EQUAL; }
">="                        { return GREATER_EQUAL; }
">>"                        { return R_SHIFT; }
"<<"                        { return L_SHIFT; }
"="                         { return ASSIGN; }
"+="                        { return ADD_ASSIGN; }
"-="                        { return MINUS_ASSIGN; }
"++"                        { return INC; }
"--"                        { return DEC; }
"~"                         { return BITWISE_NOT; }
"!"                         { return NOT; }
"?"                         { return TERNARY; }
"("                         { return L_PAREN; }
")"                         { return R_PAREN; }
"["                         { return L_BRACKET; }
"]"                         { return R_BRACKET; }
":"                         { return COLON; }
","                         { return COMMA; }

[_a-zA-Z][_a-zA-Z0-9]*      { strcpy(yylval.string, yytext); return ID;}
[0-9]+                      { yylval.number = std::atoi(yytext); return NUMBER; }
["]([^"\\\n]|\\.|\\\n)*["]  { strcpy(yylval.string, yytext); return STRING; }
'([^'\\\n]|\\.)'            { yylval.character = 0; return CHARACTER; }

[\t\f\h ]+                  {  }
[;\n\r\v\t\f\h ]+           { return SEPARATOR; }

.                           { exit(-1); }

%%
