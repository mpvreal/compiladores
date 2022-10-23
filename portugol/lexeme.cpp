#include <iostream>

#include "lexeme.hpp"

static const char* token_names[59]{	
	"NULO",
	"ID",
	"NUM_INTEIRO",
	"NUM_REAL",
	"PONTO",
	"E",
	"ATE",
	"OU",
	"ALGORITMO",
	"PARA",
	"PASSO",
	"PROCEDIMENTO",
	"CARACTERE",
	"REAL",
	"REPITA",
	"DE",
	"DIV",
	"BARRA",
	"SE",
	"SENAO",
	"VARIAVEIS",
	"VERDADEIRO",
	"TIPO",
	"NAO",
	"MATRIZ",
	"FALSO",
	"FACA",
	"FIM",
	"FUNCAO",
	"ENTAO",
	"ENQUANTO",
	"LEIA",
	"LOGICO",
	"IMPRIMA",
	"INTEIRO",
	"MAIOR",
	"MENOR",
	"MAIS",
	"SUB",
	"MUL",
	"MAIOR_IGUAL",
	"MENOR_IGUAL",
	"STRING",
	"BLOCK_COMMENT",
	"LINE_COMMENT",
	"WHITESPACE",
	"DIFERENTE",
	"ATRIBUICAO",
	"IGUAL",
	"PONTO_VIRG",
	"DOIS_PONTOS",
	"INICIO",
	"VIRG",
	"ABRE_COL",
	"FECHA_COL",
	"ABRE_PAR",
	"FECHA_PAR",
	"VETOR",
	"FIM_DE_ARQUIVO"
};

lexeme::lexeme(std::string& content, token_t tok, size_t line,
	size_t column){
	this->content.assign(content);
	this->tok = tok;
	this->line = line;
	this->column = column;
}

lexeme::lexeme(token_t tok, size_t line, size_t column){
	this->content.clear();
	this->tok = tok;
	this->line = line;
	this->column = column;
}

void lexeme::print(bool print_whitespaces){
    if(tok == WHITESPACE){
		if(print_whitespaces)
			std::cout << token_names[tok];
	}
	else{
		std::cout << token_names[tok];

		if(tok == ID || tok == NUM_INTEIRO || 
			tok == NUM_REAL || tok == STRING)
			std::cout << '(' << content << ')';

		std::cout << ':' << line << ':' << column << std::endl;
	}
}
//getters
token_t lexeme::get_tok(){
	return tok;
}

std::string lexeme::get_content(){
	return content;
}

size_t lexeme::get_line(){
	return line;
}

size_t lexeme::get_column(){
	return column;
}
//setters
void lexeme::set_tok(token_t tok){
	this->tok = tok;
}

void lexeme::set_content(std::string& content){
	this->content.assign(content);
}

void lexeme::set_line(size_t line){
	this->line = line;
}

void lexeme::set_column(size_t column){
	this->column = column;
}