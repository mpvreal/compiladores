#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <stack>
#include <vector>
#include <functional>
#include <cstdlib>

#include "lexeme.hpp"

class parser{
    public:
        parser(){ symbols.push(&parser::S); };
		inline bool done_parsing() { return symbols.empty(); };
		void parse(lexeme& l);
        void start_parsing(std::vector<lexeme> token_stream);

    private:
		inline void error(lexeme& l, const char* expected){
			std::cout << "ERRO SINTATICO EM: " << l.get_line() 
				<< " ESPERADO: " << expected;

			exit(1);
		};
        std::stack<token_t (parser::*)(lexeme&)> symbols;
		// std::stack<std::string> debug;
        std::vector<lexeme>::iterator cursor;
		
		token_t S(lexeme& l),
				E(lexeme& l),
				T(lexeme& l),
				F(lexeme& l),
				E_prime(lexeme& l),
				T_prime(lexeme& l),
				id(lexeme& l),
				add(lexeme& l),
				mul(lexeme& l),
				l_paren(lexeme& l),
				r_paren(lexeme& l),
				whitespace(lexeme& l),
				eof_tok(lexeme& l);
};

#endif  