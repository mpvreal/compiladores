#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum token_value{
    ERROR, ALGORITMO, ATE, CARACTERE, DE, DIV, E, ENQUANTO, ENTAO,
    FACA, FALSO, FIM, FUNCAO, IMPRIMA, INICIO, INTEIRO, LEIA,
    LOGICO, MATRIZ, NAO, OU, PARA, PASSO, PROCEDIMENTO, REAL,
    REPITA, SE, SENAO, TIPO, VARIAVEIS, VERDADEIRO, VETOR, ID, 
    NUMERO_INTEIRO, NUMERO_REAL, LINE_COMMENT, BLOCK_COMMENT
};

typedef struct token{
    enum token_value id;
    std::string lexeme;
} token;

#endif