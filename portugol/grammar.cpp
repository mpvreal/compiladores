#include "parser.hpp"

/************************* NÃO TERMINAIS *************************/

token_t parser::S(lexeme& l){
	switch(l.get_tok() ){
		case ALGORITMO:
            symbols.push(&parser::eof_tok);
            symbols.push(&parser::Programa);
			break;
		default:
			error(l);break;
	}
	return NULO;
}

token_t parser::Programa(lexeme& l){
	switch(l.get_tok() ){
		case ALGORITMO:
			symbols.push(&parser::ponto);
			symbols.push(&parser::BlocoComandos);
			symbols.push(&parser::ProcedimentoFuncao);
			symbols.push(&parser::BlocoVariaveis);
			symbols.push(&parser::ponto_virg);
			symbols.push(&parser::id);
			symbols.push(&parser::algoritmo);
			break;
		default:
			error(l);break;
	}
	return NULO;
}

token_t parser::ProcedimentoFuncao(lexeme& l){
	switch(l.get_tok() ){
		case PROCEDIMENTO:
			symbols.push(&parser::ProcedimentoFuncao);
			symbols.push(&parser::DeclaraProcedimento);
			break;
		case FUNCAO:
			symbols.push(&parser::ProcedimentoFuncao);
			symbols.push(&parser::DeclaraFuncao);
			break;
		case INICIO:
			break;
		default:
			error(l);break;
	}
	return NULO;
}

token_t parser::DeclaraProcedimento(lexeme& l){
	switch(l.get_tok() ){
		case PROCEDIMENTO:
			symbols.push(&parser::ponto_virg);
			symbols.push(&parser::BlocoComandos);
			symbols.push(&parser::BlocoVariaveis);
			symbols.push(&parser::DeclaraParametros);
			symbols.push(&parser::ponto_virg);
			symbols.push(&parser::Parametros);
			symbols.push(&parser::id);
			symbols.push(&parser::procedimento);
			break;
		default:
			error(l);break;
	}
	return NULO;
}

token_t parser::DeclaraFuncao(lexeme& l){
	switch(l.get_tok() ){
		case FUNCAO:
			symbols.push(&parser::ponto_virg);
			symbols.push(&parser::BlocoComandos);
			symbols.push(&parser::BlocoVariaveis);
			symbols.push(&parser::DeclaraParametros);
			symbols.push(&parser::ponto_virg);
			symbols.push(&parser::TipoBasico);
			symbols.push(&parser::dois_pontos);
			symbols.push(&parser::Parametros);
			symbols.push(&parser::id);
			symbols.push(&parser::funcao);
			break;
		default:
			error(l);break;
	}
	return NULO;
}

token_t parser::Parametros(lexeme& l){
	switch(l.get_tok() ){
		case PONTO_VIRG:
			break;
		case DOIS_PONTOS:
			break;
		case ABRE_PAR:
			symbols.push(&parser::fecha_par);
			symbols.push(&parser::DeclaraIdentificador);
			symbols.push(&parser::abre_par);
			break;
		default:
			error(l);break;
	}
	return NULO;
}

token_t parser::DeclaraParametros(lexeme& l){
	switch(l.get_tok() ){
		case ID:
			symbols.push(&parser::Declaracoes);
			break;
		case VARIAVEIS:	
			break;
		case TIPO:
			symbols.push(&parser::Declaracoes);
			break;
		case INTEIRO:
			symbols.push(&parser::Declaracoes);
			break;
		case REAL:
			symbols.push(&parser::Declaracoes);
			break;
		case CARACTERE:
			symbols.push(&parser::Declaracoes);
			break;
		case LOGICO:
			symbols.push(&parser::Declaracoes);
			break;
		case INICIO:
			break;
		default:
			error(l);break;
	}
	return NULO;
}

token_t parser::BlocoVariaveis(lexeme& l){
	switch(l.get_tok() ){
		case PROCEDIMENTO:
			break;
		case VARIAVEIS:
			symbols.push(&parser::Declaracoes);
			symbols.push(&parser::variaveis);
			break;
		case INICIO:
			break;
		default:
			error(l);break;
	}
	return NULO;
}

token_t parser::Declaracoes_prime(lexeme& l){
	switch(l.get_tok() ){
		case ID:
			symbols.push(&parser::Declaracoes);
			break;
		case PROCEDIMENTO:
			break;
		case FUNCAO:
			break;
		case VARIAVEIS:
			break;
		case TIPO:
			symbols.push(&parser::Declaracoes);
			break;
		case INTEIRO:
			symbols.push(&parser::Declaracoes);
			break;
		case REAL:
			symbols.push(&parser::Declaracoes);
			break;
		case CARACTERE:
			symbols.push(&parser::Declaracoes);
			break;
		case LOGICO:
			symbols.push(&parser::Declaracoes);
			break;
		case INICIO:
			break;
		default:
			error(l);break;
	}
	return NULO;
}

token_t parser::Declaracoes(lexeme& l){
	switch(l.get_tok() ){
		case ID:
			symbols.push(&parser::Declaracoes_prime);
			symbols.push(&parser::DeclaraVariaveis);
			break;
		case TIPO:
			symbols.push(&parser::Declaracoes_prime);
			symbols.push(&parser::DeclaraTipo);
			break;
		case INTEIRO:
			symbols.push(&parser::Declaracoes_prime);
			symbols.push(&parser::DeclaraVariaveis);
			break;
		case REAL:
			symbols.push(&parser::Declaracoes_prime);
			symbols.push(&parser::DeclaraVariaveis);
			break;
		case CARACTERE:
			symbols.push(&parser::Declaracoes_prime);
			symbols.push(&parser::DeclaraVariaveis);
			break;
		case LOGICO:
			symbols.push(&parser::Declaracoes_prime);
			symbols.push(&parser::DeclaraVariaveis);
			break;
		default:
			error(l);break;
	}
	return NULO;
}

token_t parser::DeclaraTipo(lexeme& l){
	switch(l.get_tok() ){
		case TIPO:
			symbols.push(&parser::ponto_virg);
			symbols.push(&parser::TipoBasico);
			symbols.push(&parser::fecha_col);
			symbols.push(&parser::Dimensao);
			symbols.push(&parser::abre_col);
			symbols.push(&parser::VetorMatriz);
			symbols.push(&parser::igual);
			symbols.push(&parser::id);
			symbols.push(&parser::tipo);
			break;
		default:
			error(l);break;
	}
	return NULO;
}

token_t parser::DeclaraVariaveis(lexeme& l){
	switch(l.get_tok() ){
		case ID:
			symbols.push(&parser::ponto_virg);
			symbols.push(&parser::DeclaraIdentificador);
			symbols.push(&parser::dois_pontos);
			symbols.push(&parser::TipoBasico);
			break;
		case INTEIRO:
			symbols.push(&parser::ponto_virg);
			symbols.push(&parser::DeclaraIdentificador);
			symbols.push(&parser::dois_pontos);
			symbols.push(&parser::TipoBasico);
			break;
		case REAL:
			symbols.push(&parser::ponto_virg);
			symbols.push(&parser::DeclaraIdentificador);
			symbols.push(&parser::dois_pontos);
			symbols.push(&parser::TipoBasico);
			break;
		case CARACTERE:
			symbols.push(&parser::ponto_virg);
			symbols.push(&parser::DeclaraIdentificador);
			symbols.push(&parser::dois_pontos);
			symbols.push(&parser::TipoBasico);
			break;
		case LOGICO:
			symbols.push(&parser::ponto_virg);
			symbols.push(&parser::DeclaraIdentificador);
			symbols.push(&parser::dois_pontos);
			symbols.push(&parser::TipoBasico);
			break;
		default:
			error(l);break;
	}
	return NULO;
}

token_t parser::DeclaraIdentificador_prime(lexeme& l){
	switch(l.get_tok() ){
		case PONTO_VIRG:
			break;
		case FECHA_PAR:
			break;
		case VIRG:
			symbols.push(&parser::DeclaraIdentificador);
			symbols.push(&parser::virg);
			break;
		default:
			error(l);break;
	}
	return NULO;
}

token_t parser::DeclaraIdentificador(lexeme& l){
	switch(l.get_tok() ){
		case ID:
			symbols.push(&parser::DeclaraIdentificador_prime);
			symbols.push(&parser::id);
			break;
		default:
			error(l);break;
	}
	return NULO;
}

token_t parser::VetorMatriz(lexeme& l){
	switch(l.get_tok() ){
		case VETOR:
			symbols.push(&parser::vetor);
			break;
		case MATRIZ:
			symbols.push(&parser::matriz);
			break;
		default:
			error(l);break;
	}
	return NULO;
}

token_t parser::Dimensao_prime(lexeme& l){
	switch(l.get_tok() ){
		case FECHA_COL:
			break;
		case VIRG:
			symbols.push(&parser::Dimensao);
			symbols.push(&parser::virg);
			break;
		default:
			error(l);break;
	}
	return NULO;
}

token_t parser::Dimensao(lexeme& l){
	switch(l.get_tok() ){
		case NUM_INTEIRO:
			symbols.push(&parser::Dimensao_prime);
			symbols.push(&parser::num_inteiro);
			symbols.push(&parser::dois_pontos);
			symbols.push(&parser::num_inteiro);
			break;
		default:
			error(l);break;
	}
	return NULO;
}

token_t parser::TipoBasico(lexeme& l){
	switch(l.get_tok() ){
		case ID:
			symbols.push(&parser::id);
			break;
		case INTEIRO:
			symbols.push(&parser::inteiro);
			break;
		case REAL:
			symbols.push(&parser::real);
			break;
		case CARACTERE:
			symbols.push(&parser::caractere);
			break;
		case LOGICO:
			symbols.push(&parser::logico);
			break;
		default:
			error(l);break;
	}
	return NULO;
}

token_t parser::BlocoComandos(lexeme& l){
	switch(l.get_tok() ){
		case INICIO:
			symbols.push(&parser::fim);
			symbols.push(&parser::ListaComandos);
			symbols.push(&parser::inicio);
			break;
		default:
			error(l);break;
	}
	return NULO;
}

token_t parser::ListaComandos_prime(lexeme& l){
	switch(l.get_tok() ){
		case ID:
			symbols.push(&parser::ListaComandos);
			break;
		case FIM:
			break;
		case SE:
			symbols.push(&parser::ListaComandos);
			break;
		case SENAO:
			break;
		case ENQUANTO:
			symbols.push(&parser::ListaComandos);
			break;
		case PARA:
			symbols.push(&parser::ListaComandos);
			break;
		case ATE:
			break;
		case REPITA:
			symbols.push(&parser::ListaComandos);
			break;
		case LEIA:
			symbols.push(&parser::ListaComandos);
			break;
		case IMPRIMA:
			symbols.push(&parser::ListaComandos);
			break;
		default:
			error(l);break;
	}
	return NULO;
}

token_t parser::ListaComandos(lexeme& l){
	switch(l.get_tok() ){
		case ID:
			symbols.push(&parser::ListaComandos_prime);
			symbols.push(&parser::ponto_virg);
			symbols.push(&parser::Comandos);
			break;
		case SE:
			symbols.push(&parser::ListaComandos_prime);
			symbols.push(&parser::ponto_virg);
			symbols.push(&parser::Comandos);
			break;
		case ENQUANTO:
			symbols.push(&parser::ListaComandos_prime);
			symbols.push(&parser::ponto_virg);
			symbols.push(&parser::Comandos);
			break;
		case PARA:
			symbols.push(&parser::ListaComandos_prime);
			symbols.push(&parser::ponto_virg);
			symbols.push(&parser::Comandos);
			break;
		case REPITA:
			symbols.push(&parser::ListaComandos_prime);
			symbols.push(&parser::ponto_virg);
			symbols.push(&parser::Comandos);
			break;
		case LEIA:
			symbols.push(&parser::ListaComandos_prime);
			symbols.push(&parser::ponto_virg);
			symbols.push(&parser::Comandos);
			break;
		case IMPRIMA:
			symbols.push(&parser::ListaComandos_prime);
			symbols.push(&parser::ponto_virg);
			symbols.push(&parser::Comandos);
			break;
		default:
			error(l);break;
	}
	return NULO;
}

token_t parser::Comandos_prime(lexeme& l){
	switch(l.get_tok() ){
		case PONTO_VIRG:
			break;
		case ABRE_PAR:
			symbols.push(&parser::fecha_par);
			symbols.push(&parser::ExprIter);
			symbols.push(&parser::abre_par);
			break;
		default:
			error(l);break;
	}
	return NULO;
}

token_t parser::ComandosAux(lexeme& l){
	switch(l.get_tok() ){
		case PONTO_VIRG:
			symbols.push(&parser::Comandos_prime);
			break;
		case ABRE_PAR:
			symbols.push(&parser::Comandos_prime);
			break;
		case ABRE_COL:
			symbols.push(&parser::Expressao);
			symbols.push(&parser::atribuicao);
			symbols.push(&parser::Variavel_prime);
			break;
		case ATRIBUICAO:
			symbols.push(&parser::Expressao);
			symbols.push(&parser::atribuicao);
			symbols.push(&parser::Variavel_prime);
			break;
		default:
			error(l);break;
	}
	return NULO;
}

token_t parser::Comandos(lexeme& l){
	switch(l.get_tok() ){
		case ID:
			symbols.push(&parser::ComandosAux);
			symbols.push(&parser::id);
			break;
		case SE:
			symbols.push(&parser::ComandosFimSeSenao);
			symbols.push(&parser::ListaComandos);
			symbols.push(&parser::entao);
			symbols.push(&parser::Expressao);
			symbols.push(&parser::se);
			break;
		case ENQUANTO:
			symbols.push(&parser::enquanto);
			symbols.push(&parser::fim);
			symbols.push(&parser::ListaComandos);
			symbols.push(&parser::faca);
			symbols.push(&parser::Expressao);
			symbols.push(&parser::enquanto);
			break;
		case PARA:
			symbols.push(&parser::ComandosParaPasso);
			symbols.push(&parser::Expressao);
			symbols.push(&parser::ate);
			symbols.push(&parser::Expressao);
			symbols.push(&parser::de);
			symbols.push(&parser::id);
			symbols.push(&parser::para);
			break;
		case REPITA:
			symbols.push(&parser::Expressao);
			symbols.push(&parser::ate);
			symbols.push(&parser::ListaComandos);
			symbols.push(&parser::repita);
			break;
		case LEIA:
			symbols.push(&parser::fecha_par);
			symbols.push(&parser::Variavel);
			symbols.push(&parser::abre_par);
			symbols.push(&parser::leia);
			break;
		case IMPRIMA:
			symbols.push(&parser::fecha_par);
			symbols.push(&parser::ExprIter);
			symbols.push(&parser::abre_par);
			symbols.push(&parser::imprima);
			break;
		default:
			error(l);break;
	}
	return NULO;
}

token_t parser::ComandosFimSeSenao(lexeme& l){
	switch(l.get_tok() ){
		case FIM:
			symbols.push(&parser::se);
			symbols.push(&parser::fim);
			break;
		case SENAO:
			symbols.push(&parser::se);
			symbols.push(&parser::fim);
			symbols.push(&parser::ListaComandos);
			symbols.push(&parser::senao);
			break;
		default:
			error(l);break;
	}
	return NULO;
}

token_t parser::ComandosParaPasso(lexeme& l){
	switch(l.get_tok() ){
		case FACA:
			symbols.push(&parser::para);
			symbols.push(&parser::fim);
			symbols.push(&parser::ListaComandos);
			symbols.push(&parser::faca);
			break;
		case PASSO:
			symbols.push(&parser::para);
			symbols.push(&parser::fim);
			symbols.push(&parser::ListaComandos);
			symbols.push(&parser::faca);
			symbols.push(&parser::Expressao);
			symbols.push(&parser::passo);
			break;
		default:
			error(l);break;
	}
	return NULO;
}

token_t parser::Expressao(lexeme& l){
	switch(l.get_tok() ){
		case ID:
			symbols.push(&parser::Expressao_prime);
			symbols.push(&parser::ExpressaoSimples);
			break;
		case ABRE_PAR:
			symbols.push(&parser::Expressao_prime);
			symbols.push(&parser::ExpressaoSimples);
			break;
		case NUM_INTEIRO:
			symbols.push(&parser::Expressao_prime);
			symbols.push(&parser::ExpressaoSimples);
			break;
		case MAIS:
			symbols.push(&parser::Expressao_prime);
			symbols.push(&parser::ExpressaoSimples);
			break;
		case SUB:
			symbols.push(&parser::Expressao_prime);
			symbols.push(&parser::ExpressaoSimples);
			break;
		case NAO:
			symbols.push(&parser::Expressao_prime);
			symbols.push(&parser::ExpressaoSimples);
			break;
		case NUM_REAL:
			symbols.push(&parser::Expressao_prime);
			symbols.push(&parser::ExpressaoSimples);
			break;
		case VERDADEIRO:
			symbols.push(&parser::Expressao_prime);
			symbols.push(&parser::ExpressaoSimples);
			break;
		case FALSO:
			symbols.push(&parser::Expressao_prime);
			symbols.push(&parser::ExpressaoSimples);
			break;
		case STRING:
			symbols.push(&parser::Expressao_prime);
			symbols.push(&parser::ExpressaoSimples);
			break;
		default:
			error(l);break;
	}
	return NULO;
}

token_t parser::Expressao_prime(lexeme& l){
	switch(l.get_tok() ){
		case PONTO_VIRG:
			break;
		case FECHA_PAR:
			break;
		case IGUAL:
			symbols.push(&parser::Expressao_prime);
			symbols.push(&parser::ExpressaoSimples);
			symbols.push(&parser::igual);
			break;
		case FECHA_COL:
			break;
		case VIRG:
			break;
		case ENTAO:
			break;
		case FACA:
			break;
		case PASSO:
			break;
		case ATE:
			break;
		case DIFERENTE:
			symbols.push(&parser::Expressao_prime);
			symbols.push(&parser::ExpressaoSimples);
			symbols.push(&parser::diferente);
			break;
		case MENOR:
			symbols.push(&parser::Expressao_prime);
			symbols.push(&parser::ExpressaoSimples);
			symbols.push(&parser::menor);
			break;
		case MENOR_IGUAL:
			symbols.push(&parser::Expressao_prime);
			symbols.push(&parser::ExpressaoSimples);
			symbols.push(&parser::menor_igual);
			break;
		case MAIOR_IGUAL:
			symbols.push(&parser::Expressao_prime);
			symbols.push(&parser::ExpressaoSimples);
			symbols.push(&parser::maior_igual);
			break;
		case MAIOR:
			symbols.push(&parser::Expressao_prime);
			symbols.push(&parser::ExpressaoSimples);
			symbols.push(&parser::maior);
			break;
		default:
			error(l);break;
	}
	return NULO;
}

token_t parser::ExpressaoSimples(lexeme& l){
	switch(l.get_tok() ){
		case ID:
			symbols.push(&parser::ExpressaoSimples_prime);
			symbols.push(&parser::Termo);
			break;
		case ABRE_PAR:
			symbols.push(&parser::ExpressaoSimples_prime);
			symbols.push(&parser::Termo);
			break;
		case NUM_INTEIRO:
			symbols.push(&parser::ExpressaoSimples_prime);
			symbols.push(&parser::Termo);
			break;
		case MAIS:
			symbols.push(&parser::ExpressaoSimples_prime);
			symbols.push(&parser::Termo);
			symbols.push(&parser::mais);
			break;
		case SUB:
			symbols.push(&parser::ExpressaoSimples_prime);
			symbols.push(&parser::Termo);
			symbols.push(&parser::sub);
			break;
		case NAO:
			symbols.push(&parser::ExpressaoSimples_prime);
			symbols.push(&parser::Termo);
			break;
		case NUM_REAL:
			symbols.push(&parser::ExpressaoSimples_prime);
			symbols.push(&parser::Termo);
			break;
		case VERDADEIRO:
			symbols.push(&parser::ExpressaoSimples_prime);
			symbols.push(&parser::Termo);
			break;
		case FALSO:
			symbols.push(&parser::ExpressaoSimples_prime);
			symbols.push(&parser::Termo);
			break;
		case STRING:
			symbols.push(&parser::ExpressaoSimples_prime);
			symbols.push(&parser::Termo);
			break;
		default:
			error(l);break;
	}
	return NULO;
}

token_t parser::ExpressaoSimples_prime(lexeme& l){
	switch(l.get_tok() ){
		case PONTO_VIRG:
			break;
		case FECHA_PAR:
			break;
		case IGUAL:
			break;
		case FECHA_COL:
			break;
		case VIRG:
			break;
		case ENTAO:
			break;
		case FACA:
			break;
		case PASSO:
			break;
		case ATE:
			break;
		case DIFERENTE:
			break;
		case MENOR:
			break;
		case MENOR_IGUAL:
			break;
		case MAIOR_IGUAL:
			break;
		case MAIOR:
			break;
		case MAIS:
			symbols.push(&parser::ExpressaoSimples_prime);
			symbols.push(&parser::Termo);
			symbols.push(&parser::mais);
			break;
		case SUB:
			symbols.push(&parser::ExpressaoSimples_prime);
			symbols.push(&parser::Termo);
			symbols.push(&parser::sub);
			break;
		case OU:
			symbols.push(&parser::ExpressaoSimples_prime);
			symbols.push(&parser::Termo);
			symbols.push(&parser::ou);
			break;
		default:
			error(l);break;
	}
	return NULO;
}

token_t parser::Termo(lexeme& l){
	switch(l.get_tok() ){
		case ID:
			symbols.push(&parser::Termo_prime);
			symbols.push(&parser::Fator);
			break;
		case ABRE_PAR:
			symbols.push(&parser::Termo_prime);
			symbols.push(&parser::Fator);
			break;
		case NUM_INTEIRO:
			symbols.push(&parser::Termo_prime);
			symbols.push(&parser::Fator);
			break;
		case NAO:
			symbols.push(&parser::Termo_prime);
			symbols.push(&parser::Fator);
			break;
		case NUM_REAL:
			symbols.push(&parser::Termo_prime);
			symbols.push(&parser::Fator);
			break;
		case VERDADEIRO:
			symbols.push(&parser::Termo_prime);
			symbols.push(&parser::Fator);
			break;
		case FALSO:
			symbols.push(&parser::Termo_prime);
			symbols.push(&parser::Fator);
			break;
		case STRING:
			symbols.push(&parser::Termo_prime);
			symbols.push(&parser::Fator);
			break;
		default:
			error(l);break;
	}
	return NULO;
}

token_t parser::Termo_prime(lexeme& l){
	switch(l.get_tok() ){
		case PONTO_VIRG:
			break;
		case FECHA_PAR:
			break;
		case IGUAL:
			break;
		case FECHA_COL:
			break;
		case VIRG:
			break;
		case ENTAO:
			break;
		case FACA:
			break;
		case PASSO:
			break;
		case ATE:
			break;
		case DIFERENTE:
			break;
		case MAIOR:
			break;
		case MENOR:
			break;
		case MAIOR_IGUAL:
			break;
		case MENOR_IGUAL:
			break;
		case MAIS:
			break;
		case SUB:
			break;
		case OU:
			break;
		case MUL:
			symbols.push(&parser::Termo_prime);
			symbols.push(&parser::Fator);
			symbols.push(&parser::mul);
			break;
		case DIV:
			symbols.push(&parser::Termo_prime);
			symbols.push(&parser::Fator);
			symbols.push(&parser::div);
			break;
		case BARRA:
			symbols.push(&parser::Termo_prime);
			symbols.push(&parser::Fator);
			symbols.push(&parser::barra);
			break;
		case E:
			symbols.push(&parser::Termo_prime);
			symbols.push(&parser::Fator);
			symbols.push(&parser::e);
			break;
		default:
			error(l);break;
	}
	return NULO;
}

token_t parser::Fator(lexeme& l){
	switch(l.get_tok() ){
		case ID:
			symbols.push(&parser::FatorAux);
			symbols.push(&parser::id);
			break;
		case ABRE_PAR:
			symbols.push(&parser::fecha_par);
			symbols.push(&parser::Expressao);
			symbols.push(&parser::abre_par);
			break;
		case NUM_INTEIRO:
			symbols.push(&parser::num_inteiro);
			break;
		case NAO:
			symbols.push(&parser::Fator);
			symbols.push(&parser::nao);
			break;
		case NUM_REAL:
			symbols.push(&parser::num_real);
			break;
		case VERDADEIRO:
			symbols.push(&parser::verdadeiro);
			break;
		case FALSO:
			symbols.push(&parser::falso);
			break;
		case STRING:
			symbols.push(&parser::string);
			break;
		default:
			error(l);break;
	}
	return NULO;
}

token_t parser::FatorAux(lexeme& l){
	switch(l.get_tok() ){
		case PONTO_VIRG:
			symbols.push(&parser::Variavel_prime);
			break;
		case ABRE_PAR:
			symbols.push(&parser::fecha_par);
			symbols.push(&parser::ExprIter);
			symbols.push(&parser::abre_par);
			break;
		case FECHA_PAR:
			symbols.push(&parser::Variavel_prime);
			break;
		case IGUAL:
			symbols.push(&parser::Variavel_prime);
			break;
		case ABRE_COL:
			symbols.push(&parser::Variavel_prime);
			break;
		case FECHA_COL:
			symbols.push(&parser::Variavel_prime);
			break;
		case VIRG:
			symbols.push(&parser::Variavel_prime);
			break;
		case ENTAO:
			symbols.push(&parser::Variavel_prime);
			break;
		case FACA:
			symbols.push(&parser::Variavel_prime);
			break;
		case PASSO:
			symbols.push(&parser::Variavel_prime);
			break;
		case ATE:
			symbols.push(&parser::Variavel_prime);
			break;
		case DIFERENTE:
			symbols.push(&parser::Variavel_prime);
			break;
		case MENOR:
			symbols.push(&parser::Variavel_prime);
			break;
		case MAIOR:
			symbols.push(&parser::Variavel_prime);
			break;
		case MENOR_IGUAL:
			symbols.push(&parser::Variavel_prime);
			break;
		case MAIOR_IGUAL:
			symbols.push(&parser::Variavel_prime);
			break;
		case MAIS:
			symbols.push(&parser::Variavel_prime);
			break;
		case SUB:
			symbols.push(&parser::Variavel_prime);
			break;
		case OU:
			symbols.push(&parser::Variavel_prime);
			break;
		case MUL:
			symbols.push(&parser::Variavel_prime);
			break;
		case BARRA:
			symbols.push(&parser::Variavel_prime);
			break;
		case DIV:
			symbols.push(&parser::Variavel_prime);
			break;
		case E:
			symbols.push(&parser::Variavel_prime);
			break;
		default:
			error(l);break;
	}
	return NULO;
}

token_t parser::Variavel_prime(lexeme& l){
	switch(l.get_tok() ){
		case PONTO_VIRG:
			break;
		case FECHA_PAR:
			break;
		case IGUAL:
			break;
		case ABRE_COL:
			symbols.push(&parser::fecha_col);
			symbols.push(&parser::ExprIter);
			symbols.push(&parser::abre_col);
			break;
		case FECHA_COL:
			break;
		case VIRG:
			break;
		case ATRIBUICAO:
			break;
		case ENTAO:
			break;
		case FACA:
			break;
		case PASSO:
			break;
		case ATE:
			break;
		case DIFERENTE:
			break;
		case MENOR:
			break;
		case MAIOR:
			break;
		case MENOR_IGUAL:
			break;
		case MAIOR_IGUAL:
			break;
		case MAIS:
			break;
		case SUB:
			break;
		case OU:
			break;
		case MUL:
			break;
		case DIV:
			break;
		case BARRA:
			break;
		case E:
			break;
		default:
			error(l);break;
	}
	return NULO;
}

token_t parser::Variavel(lexeme& l){
	switch(l.get_tok() ){
		case ID:
			symbols.push(&parser::Variavel_prime);
			symbols.push(&parser::id);
			break;
		default:
			error(l);break;
	}
	return NULO;
}

token_t parser::ExprIter_prime(lexeme& l){
	switch(l.get_tok() ){
		case FECHA_PAR:
			break;
		case FECHA_COL:
			break;
		case VIRG:
			symbols.push(&parser::ExprIter);
			symbols.push(&parser::virg);
			break;
		default:
			error(l);break;
	}
	return NULO;
}

token_t parser::ExprIter(lexeme& l){
	switch(l.get_tok() ){
		case ID:
			symbols.push(&parser::ExprIter_prime);
			symbols.push(&parser::Expressao);
			break;
		case ABRE_PAR:
			symbols.push(&parser::ExprIter_prime);
			symbols.push(&parser::Expressao);
			break;
		case NUM_INTEIRO:
			symbols.push(&parser::ExprIter_prime);
			symbols.push(&parser::Expressao);
			break;
		case DIFERENTE:
			symbols.push(&parser::ExprIter_prime);
			symbols.push(&parser::Expressao);
			break;
		case MENOR:
			symbols.push(&parser::ExprIter_prime);
			symbols.push(&parser::Expressao);
			break;
		case MENOR_IGUAL:
			symbols.push(&parser::ExprIter_prime);
			symbols.push(&parser::Expressao);
			break;
		case MAIOR_IGUAL:
			symbols.push(&parser::ExprIter_prime);
			symbols.push(&parser::Expressao);
			break;
		case MAIOR:
			symbols.push(&parser::ExprIter_prime);
			symbols.push(&parser::Expressao);
			break;
		case MAIS:
			symbols.push(&parser::ExprIter_prime);
			symbols.push(&parser::Expressao);
			break;
		case SUB:
			symbols.push(&parser::ExprIter_prime);
			symbols.push(&parser::Expressao);
			break;
		case NAO:
			symbols.push(&parser::ExprIter_prime);
			symbols.push(&parser::Expressao);
			break;
		case NUM_REAL:
			symbols.push(&parser::ExprIter_prime);
			symbols.push(&parser::Expressao);
			break;
		case VERDADEIRO:
			symbols.push(&parser::ExprIter_prime);
			symbols.push(&parser::Expressao);
			break;
		case FALSO:
			symbols.push(&parser::ExprIter_prime);
			symbols.push(&parser::Expressao);
			break;
		case STRING:
			symbols.push(&parser::ExprIter_prime);
			symbols.push(&parser::Expressao);
			break;
		default:
			error(l);break;
	}
	return NULO;
}

/*************************** TERMINAIS ***************************/
token_t parser::id(lexeme& l) { if(l.get_tok() != ID) error(l); return ID; }
token_t parser::num_inteiro(lexeme& l) { if(l.get_tok() != NUM_INTEIRO) error(l); return NUM_INTEIRO; }
token_t parser::num_real(lexeme& l) { if(l.get_tok() != NUM_REAL) error(l); return NUM_REAL; }
token_t parser::ponto(lexeme& l) { if(l.get_tok() != PONTO) error(l); return PONTO; }
token_t parser::e(lexeme& l) { if(l.get_tok() != E) error(l); return E;}
token_t parser::ate(lexeme& l) { if(l.get_tok() != ATE) error(l); return ATE; }
token_t parser::ou(lexeme& l) { if(l.get_tok() != OU) error(l); return OU;}
token_t parser::algoritmo(lexeme& l) { if(l.get_tok() != ALGORITMO) error(l); return ALGORITMO; }
token_t parser::para(lexeme& l) { if(l.get_tok() != PARA) error(l); return PARA; }
token_t parser::passo(lexeme& l) { if(l.get_tok() != PASSO) error(l); return PASSO; }
token_t parser::procedimento(lexeme& l) { if(l.get_tok() != PROCEDIMENTO) error(l); return PROCEDIMENTO; }
token_t parser::caractere(lexeme& l) { if(l.get_tok() != CARACTERE) error(l); return CARACTERE; }
token_t parser::real(lexeme& l) { if(l.get_tok() != REAL) error(l); return REAL; }
token_t parser::repita(lexeme& l) { if(l.get_tok() != REPITA) error(l); return REPITA; }
token_t parser::de(lexeme& l) { if(l.get_tok() != DE) error(l); return DE;}
token_t parser::div(lexeme& l) { if(l.get_tok() != DIV) error(l); return DIV; }
token_t parser::barra(lexeme& l) { if(l.get_tok() != BARRA) error(l); return BARRA; }
token_t parser::se(lexeme& l) { if(l.get_tok() != SE) error(l); return SE;}
token_t parser::senao(lexeme& l) { if(l.get_tok() != SENAO) error(l); return SENAO; }
token_t parser::variaveis(lexeme& l) { if(l.get_tok() != VARIAVEIS) error(l); return VARIAVEIS; }
token_t parser::verdadeiro(lexeme& l) { if(l.get_tok() != VERDADEIRO) error(l); return VERDADEIRO; }
token_t parser::tipo(lexeme& l) { if(l.get_tok() != TIPO) error(l); return TIPO; }
token_t parser::nao(lexeme& l) { if(l.get_tok() != NAO) error(l); return NAO; }
token_t parser::matriz(lexeme& l) { if(l.get_tok() != MATRIZ) error(l); return MATRIZ; }
token_t parser::falso(lexeme& l) { if(l.get_tok() != FALSO) error(l); return FALSO; }
token_t parser::faca(lexeme& l) { if(l.get_tok() != FACA) error(l); return FACA; }
token_t parser::fim(lexeme& l) { if(l.get_tok() != FIM) error(l); return FIM; }
token_t parser::funcao(lexeme& l) { if(l.get_tok() != FUNCAO) error(l); return FUNCAO; }
token_t parser::entao(lexeme& l) { if(l.get_tok() != ENTAO) error(l); return ENTAO; }
token_t parser::enquanto(lexeme& l) { if(l.get_tok() != ENQUANTO) error(l); return ENQUANTO; }
token_t parser::leia(lexeme& l) { if(l.get_tok() != LEIA) error(l); return LEIA; }
token_t parser::logico(lexeme& l) { if(l.get_tok() != LOGICO) error(l); return LOGICO; }
token_t parser::imprima(lexeme& l) { if(l.get_tok() != IMPRIMA) error(l); return IMPRIMA; }
token_t parser::inteiro(lexeme& l) { if(l.get_tok() != INTEIRO) error(l); return INTEIRO; }
token_t parser::maior(lexeme& l) { if(l.get_tok() != MAIOR) error(l); return MAIOR; }
token_t parser::menor(lexeme& l) { if(l.get_tok() != MENOR) error(l); return MENOR; }
token_t parser::mais(lexeme& l) { if(l.get_tok() != MAIS) error(l); return MAIS; }
token_t parser::sub(lexeme& l) { if(l.get_tok() != SUB) error(l); return SUB; }
token_t parser::mul(lexeme& l) { if(l.get_tok() != MUL) error(l); return MUL; }
token_t parser::maior_igual(lexeme& l) { if(l.get_tok() != MAIOR_IGUAL) error(l); return MAIOR_IGUAL; }
token_t parser::menor_igual(lexeme& l) { if(l.get_tok() != MENOR_IGUAL) error(l); return MENOR_IGUAL; }
token_t parser::string(lexeme& l) { if(l.get_tok() != STRING) error(l); return STRING; }
token_t parser::block_comment(lexeme& l) { if(l.get_tok() != BLOCK_COMMENT) error(l); return BLOCK_COMMENT; }
token_t parser::line_comment(lexeme& l) { if(l.get_tok() != LINE_COMMENT) error(l); return LINE_COMMENT; }
token_t parser::whitespace(lexeme& l) { if(l.get_tok() != WHITESPACE) error(l); return WHITESPACE; }
token_t parser::diferente(lexeme& l) { if(l.get_tok() != DIFERENTE) error(l); return DIFERENTE; }
token_t parser::atribuicao(lexeme& l) { if(l.get_tok() != ATRIBUICAO) error(l); return ATRIBUICAO; }
token_t parser::igual(lexeme& l) { if(l.get_tok() != IGUAL) error(l); return IGUAL; }
token_t parser::ponto_virg(lexeme& l) { if(l.get_tok() != PONTO_VIRG) error(l); return PONTO_VIRG; }
token_t parser::dois_pontos(lexeme& l) { if(l.get_tok() != DOIS_PONTOS) error(l); return DOIS_PONTOS; }
token_t parser::inicio(lexeme& l) { if(l.get_tok() != INICIO) error(l); return INICIO; }
token_t parser::virg(lexeme& l) { if(l.get_tok() != VIRG) error(l); return VIRG; }
token_t parser::abre_col(lexeme& l) { if(l.get_tok() != ABRE_COL) error(l); return ABRE_COL; }
token_t parser::fecha_col(lexeme& l) { if(l.get_tok() != FECHA_COL) error(l); return FECHA_COL; }
token_t parser::abre_par(lexeme& l) { if(l.get_tok() != ABRE_PAR) error(l); return ABRE_PAR; }
token_t parser::fecha_par(lexeme& l) { if(l.get_tok() != FECHA_PAR) error(l); return FECHA_PAR; }
token_t parser::vetor(lexeme& l) { if(l.get_tok() != VETOR) error(l); return VETOR; }
token_t parser::eof_tok(lexeme& l) { if(l.get_tok() != EOF_TOK) error(l); return EOF_TOK; }