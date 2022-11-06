#include <iostream>

#include "lexeme.hpp"

static const char* token_names[]{	
	"NULO",
	"ID",
	"ADD",
	"MUL",
	"L_PAREN",
	"R_PAREN",
	"WHITESPACE"
	"EOF_TOK"
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

		if(tok == ID)
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