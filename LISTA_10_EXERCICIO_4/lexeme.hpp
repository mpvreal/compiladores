#ifndef LEXEME_H
#define LEXEME_H

#include <string>

#include "defs.hpp"

typedef enum tokens{	
	NULO,
	ID,
	ADD,
	MUL,
	L_PAREN,
	R_PAREN,
	WHITESPACE,
	EOF_TOK
} token_t;

class lexeme{
    public:
        lexeme(std::string& content, token_t tok, 
			size_t line, size_t column);
		lexeme(token_t tok, size_t line, size_t column);
		lexeme(){};
		std::string get_content();
		token_t get_tok();
		size_t get_line();
		size_t get_column();
		void set_content(std::string& content);
		void set_tok(token_t tok);
		void set_line(size_t line);
		void set_column(size_t column);
        void print(bool print_whitespaces = false);
    
    private:
        std::string content;
		size_t line,
			   column;
        token_t tok;
};

#endif