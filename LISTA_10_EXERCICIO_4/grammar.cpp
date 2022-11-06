#include "parser.hpp"

/************************* NÃO TERMINAIS *************************/

token_t parser::S(lexeme& l){
	switch(l.get_tok() ){
		case ID:
            symbols.push(&parser::eof_tok);
            symbols.push(&parser::E);
			break;
		default:
			error(l, "id");
			break;
	}
	return NULO;
}

token_t parser::E(lexeme& l){
	switch(l.get_tok() ){
		case ID:
			symbols.push(&parser::E_prime);
			symbols.push(&parser::T);
			break;
		case L_PAREN:
			symbols.push(&parser::E_prime);
			symbols.push(&parser::T);
			break;
		default:
			error(l, "id, (");
			break;
	}
	return NULO;
}

token_t parser::E_prime(lexeme& l){
	switch(l.get_tok() ){
		case ADD:
			symbols.push(&parser::E_prime);
			symbols.push(&parser::T);
			symbols.push(&parser::add);
			break;
		case R_PAREN:
		case EOF_TOK:
			break;
		default:
			error(l, "+, ), $");
			break;
	}
	return NULO;
}

token_t parser::T(lexeme& l){
	switch(l.get_tok() ){
		case ID:
			symbols.push(&parser::T_prime);
			symbols.push(&parser::F);
			break;
		case L_PAREN:
			symbols.push(&parser::T_prime);
			symbols.push(&parser::F);
			break;
		default:
			error(l, "id, (");
			break;
	}
	return NULO;
}

token_t parser::T_prime(lexeme& l){
	switch(l.get_tok() ){
		case MUL:
			symbols.push(&parser::T_prime);
			symbols.push(&parser::F);
			symbols.push(&parser::mul);
			break;
		case ADD:
		case R_PAREN:
		case EOF_TOK:
			break;
		default:
			error(l, "*, +, ), $");
			break;
	}
	return NULO;
}

token_t parser::F(lexeme& l){
	switch(l.get_tok() ){
		case ID:
			symbols.push(&parser::id);
			break;
		case L_PAREN:
			symbols.push(&parser::r_paren);
			symbols.push(&parser::E);
			symbols.push(&parser::l_paren);
			break;
		default:
			error(l, "id, (");
			break;
	}
	return NULO;
}

/************************* TERMINAIS *************************/
token_t parser::id(lexeme& l){
	if(l.get_tok() != ID)
		error(l, "id");

	return ID;
}

token_t parser::add(lexeme& l){
	if(l.get_tok() != ADD)
		error(l, "+");

	return ADD;
}

token_t parser::mul(lexeme& l){
	if(l.get_tok() != MUL)
		error(l, "*");

	return MUL;
}

token_t parser::l_paren(lexeme& l){
	if(l.get_tok() != L_PAREN)
		error(l, "(");

	return L_PAREN;
}

token_t parser::r_paren(lexeme& l){
	if(l.get_tok() != R_PAREN)
		error(l, ")");

	return R_PAREN;
}

token_t parser::eof_tok(lexeme& l){
	if(l.get_tok() != EOF_TOK)
		error(l, "$");

	return EOF_TOK;
}