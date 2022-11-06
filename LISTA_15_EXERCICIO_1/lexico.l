%{
#include <stdio.h>
#include <stdlib.h>
#include <sintatico.tab.h>

%}

%%

[a-z]+ { return ID; }
"int" { return INT; }
"float" { return FLOAT; }
"char" { return CHAR; }
<<EOF>> { return END;}
.

%%