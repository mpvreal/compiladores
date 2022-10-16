%option noyywrap

%{
/* ALUNO:   MATHEUS PIRES VILA REAL
 * Nº:      202000560352
 */
    #include <stdio.h>
    #include <string.h>

    int total_lines = 1,
        blank_lines = 0,
        lines_w_comments = 0,
        nb_nc_lines = 0,
        semicolons = 0,
        preproc = 0;

    int content = 0,
        block_comment = 0;

    void reset_stats();
%}

%x COMMENT

%%

<INITIAL>{
"#".+\n {
    // puts("Diretiva pré-proc");
    total_lines += 1;
    preproc += 1;
}
"//"[^\n]* {
    block_comment = 0;
    total_lines += 1;
    lines_w_comments += 1;
}
"/*" {
    block_comment = 1;
    lines_w_comments += 1;
    total_lines += 1;
    BEGIN(COMMENT);
}
; {
    content = 1;
    semicolons += 1;
}
\n {
    if(block_comment == 0){
        if(content)
            nb_nc_lines += 1;
        else
            blank_lines += 1;
        
        total_lines += 1;
    }
    block_comment = 0;
    content = 0;
}
[ \r\t\a]
. {
    content = 1;
}
}

<COMMENT>{
\n {
    total_lines += 1;
    lines_w_comments += 1;
}
"*/" {

    BEGIN(INITIAL);
}
. 
}

%%

void reset_stats(){

    total_lines = 1;
    blank_lines = 0;
    lines_w_comments = 0;
    nb_nc_lines = 0;
    semicolons = 0;
    preproc = 0;

    block_comment = 0;
    content = 0;
}

int main(int argc, char* argv[]){

    FILE* file = NULL;
    int i = 1;

    printf("%6s%9s%9s%9s%9s%9s%5s\n", "total", "blank", "lines w/",
        "nb, nc", "semi-", "preproc.", "file");
    printf("%6s%9s%9s%9s%9s%9s\n", "lines", "lines", "comments",
        "lines", "colons", "direct");
    puts("------+--------+--------+--------+--------+--------+----");

    if(argc < 2){
        yylex();
        printf("%6d%9d%9d%9d%9d%9d -%s\n", total_lines, blank_lines,
            lines_w_comments, nb_nc_lines, semicolons, preproc, 
            argv[i]);

    } else{
        for(i = 1; i < argc; i++){
            file = fopen(argv[i], "r");

            if(file == NULL){
                perror(argv[i]);
                return 1;
            }

            yyrestart(file);
            reset_stats();
            yylex();

            printf("%6d%9d%9d%9d%9d%9d %-s\n", total_lines, 
                blank_lines, lines_w_comments, nb_nc_lines, 
                semicolons, preproc, argv[i]);

            fclose(file);
        }
    }

    return 0;
}