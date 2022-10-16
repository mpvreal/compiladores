#include "parser.hpp"

token_t parser::S(lexeme& l){
	switch(l.get_tok() ){
		case ALGORITMO:
            symbols.push(&eof_tok);
            symbols.push(&Programa);
			break;
		default:
			break;
	}
	return NULO;
}