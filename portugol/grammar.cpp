#include "parser.hpp"

/************************* NÃO TERMINAIS *************************/

token_t parser::S(lexeme& l){
	switch(l.get_tok() ){
		case ALGORITMO:
            symbols.push(&eof_tok);
            symbols.push(&Programa);
			break;
		default:
			error(l);
			break;
	}
	return NULO;
}

token_t parser::Programa(lexeme& l){
	switch(l.get_tok() ){
		case ALGORITMO:
			symbols.push(&ponto);
			symbols.push(&BlocoComandos);
			symbols.push(&ProcedimentoFuncao);
			symbols.push(&BlocoVariaveis);
			symbols.push(&ponto_virg);
			symbols.push(&id);
			symbols.push(&algoritmo);
			break;
		default:
			error(l);
			break;
	}
	return NULO;
}

token_t parser::ProcedimentoFuncao(lexeme& l){
	switch(l.get_tok() ){
		case PROCEDIMENTO:
			symbols.push(&ProcedimentoFuncao);
			symbols.push(&DeclaraProcedimento);
			break;
		default:
			error(l);
			return;
	}
	return NULO;
}

token_t parser::DeclaraProcedimento(lexeme& l){
	switch(l.get_tok() ){
		case PROCEDIMENTO:
			symbols.push(&BlocoComandos);
			symbols.push(&BlocoVariaveis);
			symbols.push(&DeclaraParametros);
			symbols.push(&ponto_virg);
			symbols.push(&Parametros);
			symbols.push(&id);
			symbols.push(&procedimento);
			break;
		default:
			error(l);
			break;
	}
	return NULO;
}

token_t parser::DeclaraFuncao(lexeme& l){
	switch(l.get_tok() ){
		case FUNCAO:
			symbols.push(&BlocoComandos);
			symbols.push(&BlocoVariaveis);
			symbols.push(&DeclaraParametros);
			symbols.push(&ponto_virg);
			symbols.push(&TipoBasico);
			symbols.push(&dois_pontos);
			symbols.push(&Parametros);
			symbols.push(&id);
			symbols.push(&funcao);
			break;
		default:
			error(l);
			break;
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
			symbols.push(&fecha_par);
			symbols.push(&DeclaraIdentificador);
			symbols.push(&abre_par);
			break;
		default:
			error(l);
			break;
	}
	return NULO;
}

token_t parser::DeclaraParametros(lexeme& l){
	switch(l.get_tok() ){
		case ID:
			symbols.push(&Declaracoes);
			break;
		case VARIAVEIS:	
			break;
		case TIPO:
			symbols.push(&Declaracoes);
			break;
		case INTEIRO:
			symbols.push(&Declaracoes);
			break;
		case REAL:
			symbols.push(&Declaracoes);
			break;
		case CARACTERE:
			symbols.push(&Declaracoes);
			break;
		case LOGICO:
			symbols.push(&Declaracoes);
			break;
		case INICIO:
			break;
		default:
			error(l);
			break;
	}
	return NULO;
}

token_t parser::BlocoVariaveis(lexeme& l){
	switch(l.get_tok() ){
		case PROCEDIMENTO:
			break;
		case VARIAVEIS:
			symbols.push(&Declaracoes);
			symbols.push(&variaveis);
			break;
		case INICIO:
			break;
		default:
			error(l);
			break;
	}
	return NULO;
}

token_t parser::Declaracoes_prime(lexeme& l){
	switch(l.get_tok() ){
		case ID:
			symbols.push(&Declaracoes);
			break;
		case PROCEDIMENTO:
			break;
		case VARIAVEIS:
			break;
		case TIPO:
			symbols.push(&Declaracoes);
			break;
		case INTEIRO:
			symbols.push(&Declaracoes);
			break;
		case REAL:
			symbols.push(&Declaracoes);
			break;
		case CARACTERE:
			symbols.push(&Declaracoes);
			break;
		case LOGICO:
			symbols.push(&Declaracoes);
			break;
		case INICIO:
			break;
		default:
			error(l);
			break;
	}
	return NULO;
}

token_t parser::Declaracoes(lexeme& l){
	switch(l.get_tok() ){
		case ID:
			symbols.push(&Declaracoes_prime);
			symbols.push(&DeclaraVariaveis);
			break;
		case TIPO:
			symbols.push(&Declaracoes_prime);
			symbols.push(&DeclaraTipo);
			break;
		case INTEIRO:
			symbols.push(&Declaracoes_prime);
			symbols.push(&DeclaraVariaveis);
			break;
		case REAL:
			symbols.push(&Declaracoes_prime);
			symbols.push(&DeclaraVariaveis);
			break;
		case CARACTERE:
			symbols.push(&Declaracoes_prime);
			symbols.push(&DeclaraVariaveis);
			break;
		case LOGICO:
			symbols.push(&Declaracoes_prime);
			symbols.push(&DeclaraVariaveis);
			break;
		default:
			error(l);
			break;
	}
	return NULO;
}

token_t parser::DeclaraTipo(lexeme& l){
	switch(l.get_tok() ){
		case TIPO:
			symbols.push(&ponto_virg);
			symbols.push(&TipoBasico);
			symbols.push(&fecha_col);
			symbols.push(&Dimensao);
			symbols.push(&abre_col);
			symbols.push(&VetorMatriz);
			symbols.push(&igual);
			symbols.push(&id);
			symbols.push(&tipo);
			break;
		default:
			error(l);
			break;
	}
	return NULO;
}

token_t parser::DeclaraVariaveis(lexeme& l){
	switch(l.get_tok() ){
		case ID:
			symbols.push(&ponto_virg);
			symbols.push(&DeclaraIdentificador);
			symbols.push(&dois_pontos);
			symbols.push(&TipoBasico);
			break;
		case INTEIRO:
			symbols.push(&ponto_virg);
			symbols.push(&DeclaraIdentificador);
			symbols.push(&dois_pontos);
			symbols.push(&TipoBasico);
			break;
		case REAL:
			symbols.push(&ponto_virg);
			symbols.push(&DeclaraIdentificador);
			symbols.push(&dois_pontos);
			symbols.push(&TipoBasico);
			break;
		case CARACTERE:
			symbols.push(&ponto_virg);
			symbols.push(&DeclaraIdentificador);
			symbols.push(&dois_pontos);
			symbols.push(&TipoBasico);
			break;
		case LOGICO:
			symbols.push(&ponto_virg);
			symbols.push(&DeclaraIdentificador);
			symbols.push(&dois_pontos);
			symbols.push(&TipoBasico);
			break;
		default:
			error(l);
			break;
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
			symbols.push(&DeclaraIdentificador);
			symbols.push(&virg);
			break;
		default:
			error(l);
			break;
	}
	return NULO;
}

token_t parser::DeclaraIdentificador(lexeme& l){
	switch(l.get_tok() ){
		case ID:
			symbols.push(&DeclaraIdentificador_prime);
			symbols.push(&id);
			break;
		default:
			error(l);
			break;
	}
	return NULO;
}

token_t parser::VetorMatriz(lexeme& l){
	switch(l.get_tok() ){
		case VETOR:
			symbols.push(&vetor);
			symbols.push(&matriz);
		default:
			error(l);
			break;
	}
	return NULO;
}

token_t parser::Dimensao_prime(lexeme& l){
	switch(l.get_tok() ){
		case FECHA_COL:
			break;
		case VIRG:
			symbols.push(&Dimensao);
			symbols.push(&virg);
			break;
		default:
			error(l);
			break;
	}
	return NULO;
}

token_t parser::Dimensao(lexeme& l){
	switch(l.get_tok() ){
		case NUM_INTEIRO:
			symbols.push(&Dimensao_prime);
			symbols.push(&num_inteiro);
			symbols.push(&dois_pontos);
			symbols.push(&num_inteiro);
			break;
		default:
			error(l);
			break;
	}
	return NULO;
}

token_t parser::TipoBasico(lexeme& l){
	switch(l.get_tok() ){
		case ID:
			symbols.push(&id);
			break;
		case INTEIRO:
			symbols.push(&inteiro);
			break;
		case REAL:
			symbols.push(&real);
			break;
		case CARACTERE:
			symbols.push(&caractere);
			break;
		case LOGICO:
			symbols.push(&logico);
			break;
		default:
			error(l);
			break;
	}
	return NULO;
}

token_t parser::BlocoComandos(lexeme& l){
	switch(l.get_tok() ){
		case INICIO:
			symbols.push(&fim);
			symbols.push(&ListaComandos);
			symbols.push(&inicio);
			break;
		default:
			error(l);
			break;
	}
	return NULO;
}

token_t parser::ListaComandos_prime(lexeme& l){
	switch(l.get_tok() ){
		case ID:
			symbols.push(&ListaComandos);
			break;
		case FIM:
			break;
		case SE:
			symbols.push(&ListaComandos);
			break;
		case SENAO:
			break;
		case ENQUANTO:
			symbols.push(&ListaComandos);
			break;
		case PARA:
			symbols.push(&ListaComandos);
			break;
		case ATE:
			break;
		case REPITA:
			symbols.push(&ListaComandos);
			break;
		case LEIA:
			symbols.push(&ListaComandos);
			break;
		case IMPRIMA:
			symbols.push(&ListaComandos);
			break;
		default:
			error(l);
			break;
	}
}

token_t parser::ListaComandos(lexeme& l){
	switch(l.get_tok() ){
		case ID:
			symbols.push(&ListaComandos_prime);
			symbols.push(&ponto_virg);
			symbols.push(&Comandos);
			break;
		case SE:
			symbols.push(&ListaComandos_prime);
			symbols.push(&ponto_virg);
			symbols.push(&Comandos);
			break;
		case ENQUANTO:
			symbols.push(&ListaComandos_prime);
			symbols.push(&ponto_virg);
			symbols.push(&Comandos);
			break;
		case PARA:
			symbols.push(&ListaComandos_prime);
			symbols.push(&ponto_virg);
			symbols.push(&Comandos);
			break;
		case REPITA:
			symbols.push(&ListaComandos_prime);
			symbols.push(&ponto_virg);
			symbols.push(&Comandos);
			break;
		case LEIA:
			symbols.push(&ListaComandos_prime);
			symbols.push(&ponto_virg);
			symbols.push(&Comandos);
			break;
		case IMPRIMA:
			symbols.push(&ListaComandos_prime);
			symbols.push(&ponto_virg);
			symbols.push(&Comandos);
			break;
		default:
			error(l);
			break;
	}
	return NULO;
}

token_t parser::Comandos_prime(lexeme& l){
	switch(l.get_tok() ){
		case PONTO_VIRG:
			break;
		case ABRE_PAR:
			symbols.push(&abre_par);
			symbols.push(&ExprIter);
			symbols.push(&fecha_par);
			break;
		default:
			error(l);
			break;
	}
	return NULO;
}

token_t parser::ComandosAux(lexeme& l){
	switch(l.get_tok() ){
		case PONTO_VIRG:
			symbols.push(&Comandos_prime);
		case ABRE_PAR:
			symbols.push(&Comandos_prime);
			break;
		case ABRE_COL:
			symbols.push(&Expressao);
			symbols.push(&atribuicao);
			symbols.push(&Variavel_prime);
		case ATRIBUICAO:
			symbols.push(&Expressao);
			symbols.push(&atribuicao);
			symbols.push(&Variavel_prime);
		default:
			error(l);
			break;
	}
	return NULO;
}

token_t parser::Comandos(lexeme& l){
	switch(l.get_tok() ){
		case ID:
			symbols.push(&ComandosAux);
			symbols.push(&id);
			break;
		case SE:
			symbols.push(&ComandosFimSeSenao);
			symbols.push(&ListaComandos);
			symbols.push(&entao);
			symbols.push(&Expressao);
			symbols.push(&se);
			break;
		case ENQUANTO:
			symbols.push(&enquanto);
			symbols.push(&fim);
			symbols.push(&ListaComandos);
			symbols.push(&faca);
			symbols.push(&Expressao);
			symbols.push(&enquanto);
			break;
		case PARA:
			symbols.push(&ComandosParaPasso);
			symbols.push(&Expressao);
			symbols.push(&ate);
			symbols.push(&Expressao);
			symbols.push(&de);
			symbols.push(&id);
			symbols.push(&para);
			break;
		case REPITA:
			symbols.push(&Expressao);
			symbols.push(&ate);
			symbols.push(&ListaComandos);
			symbols.push(&repita);
			break;
		case LEIA:
			symbols.push(&fecha_par);
			symbols.push(&Variavel);
			symbols.push(&abre_par);
			symbols.push(&leia);
			break;
		case IMPRIMA:
			symbols.push(&fecha_par);
			symbols.push(&ExprIter);
			symbols.push(&abre_par);
			symbols.push(&imprima);
			break;
		default:
			error(l);
			break;
	}
	return NULO;
}

token_t parser::ComandosFimSeSenao(lexeme& l){
	switch(l.get_tok() ){
		case FIM:
			symbols.push(&se);
			symbols.push(&fim);
			break;
		case SENAO:
			symbols.push(&se);
			symbols.push(&fim);
			symbols.push(&ListaComandos);
			symbols.push(&senao);
			break;
		default:
			error(l);
			break;
	}
	return NULO;
}

token_t parser::ComandosParaPasso(lexeme& l){
	switch(l.get_tok() ){
		case FACA:
			symbols.push(&para);
			symbols.push(&fim);
			symbols.push(&ListaComandos);
			symbols.push(&faca);
			break;
		case PASSO:
			symbols.push(&para);
			symbols.push(&fim);
			symbols.push(&ListaComandos);
			symbols.push(&faca);
			symbols.push(&Expressao);
			symbols.push(&passo);
			break;
		default:
			error(l);
			break;
	}
	return NULO;
}

token_t parser::Expressao(lexeme& l){
	switch(l.get_tok() ){
		case ID:
			symbols.push(&Expressao_prime);
			symbols.push(&ExpressaoSimples);
			break;
		case ABRE_PAR:
			symbols.push(&Expressao_prime);
			symbols.push(&ExpressaoSimples);
			break;
		case NUM_INTEIRO:
			symbols.push(&Expressao_prime);
			symbols.push(&ExpressaoSimples);
			break;
		case DIFERENTE:
			symbols.push(&Expressao_prime);
			symbols.push(&ExpressaoSimples);
			symbols.push(&diferente);
			break;
		case MENOR:
			symbols.push(&Expressao_prime);
			symbols.push(&ExpressaoSimples);
			symbols.push(&menor);
			break;
		case MENOR_IGUAL:
			symbols.push(&Expressao_prime);
			symbols.push(&ExpressaoSimples);
			symbols.push(&menor_igual);
			break;
		case MAIOR_IGUAL:
			symbols.push(&Expressao_prime);
			symbols.push(&ExpressaoSimples);
			symbols.push(&maior_igual);
			break;
		case MAIOR:
			symbols.push(&Expressao_prime);
			symbols.push(&ExpressaoSimples);
			symbols.push(&maior);
			break;
		case MAIS:
			symbols.push(&Expressao_prime);
			symbols.push(&ExpressaoSimples);
			break;
		case SUB:
			symbols.push(&Expressao_prime);
			symbols.push(&ExpressaoSimples);
			break;
		case NAO:
			symbols.push(&Expressao_prime);
			symbols.push(&ExpressaoSimples);
			break;
		case NUM_REAL:
			symbols.push(&Expressao_prime);
			symbols.push(&ExpressaoSimples);
			break;
		case VERDADEIRO:
			symbols.push(&Expressao_prime);
			symbols.push(&ExpressaoSimples);
			break;
		case FALSO:
			symbols.push(&Expressao_prime);
			symbols.push(&ExpressaoSimples);
			break;
		case STRING:
			symbols.push(&Expressao_prime);
			symbols.push(&ExpressaoSimples);
			break;
		default:
			error(l);
			break;
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
			symbols.push(&Expressao_prime);
			symbols.push(&ExpressaoSimples);
			symbols.push(&igual);
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
		default:
			error(l);
			break;
	}
	return NULO;
}

token_t parser::ExpressaoSimples(lexeme& l){
	switch(l.get_tok() ){
		case ID:
			symbols.push(&ExpressaoSimples_prime);
			symbols.push(&Termo);
			break;
		case ABRE_PAR:
			symbols.push(&ExpressaoSimples_prime);
			symbols.push(&Termo);
			break;
		case NUM_INTEIRO:
			symbols.push(&ExpressaoSimples_prime);
			symbols.push(&Termo);
			break;
		case MAIS:
			symbols.push(&ExpressaoSimples_prime);
			symbols.push(&Termo);
			symbols.push(&mais);
			break;
		case SUB:
			symbols.push(&ExpressaoSimples_prime);
			symbols.push(&Termo);
			symbols.push(&sub);
			break;
		case NAO:
			symbols.push(&ExpressaoSimples_prime);
			symbols.push(&Termo);
			break;
		case NUM_REAL:
			symbols.push(&ExpressaoSimples_prime);
			symbols.push(&Termo);
			break;
		case VERDADEIRO:
			symbols.push(&ExpressaoSimples_prime);
			symbols.push(&Termo);
			break;
		case FALSO:
			symbols.push(&ExpressaoSimples_prime);
			symbols.push(&Termo);
			break;
		case STRING:
			symbols.push(&ExpressaoSimples_prime);
			symbols.push(&Termo);
			break;
		default:
			error(l);
			break;
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
		case MAIS:
			symbols.push(&ExpressaoSimples_prime);
			symbols.push(&Termo);
			symbols.push(&mais);
			break;
		case SUB:
			symbols.push(&ExpressaoSimples_prime);
			symbols.push(&Termo);
			symbols.push(&sub);
			break;
		case OU:
			symbols.push(&ExpressaoSimples_prime);
			symbols.push(&Termo);
			symbols.push(&ou);
			break;
		default:
			error(l);
			break;
	}
	return NULO;
}

token_t parser::Termo(lexeme& l){
	switch(l.get_tok() ){
		case ID:
			symbols.push(&Termo_prime);
			symbols.push(&Fator);
			break;
		case ABRE_PAR:
			symbols.push(&Termo_prime);
			symbols.push(&Fator);
			break;
		case NUM_INTEIRO:
			symbols.push(&Termo_prime);
			symbols.push(&Fator);
			break;
		case NAO:
			symbols.push(&Termo_prime);
			symbols.push(&Fator);
			break;
		case NUM_REAL:
			symbols.push(&Termo_prime);
			symbols.push(&Fator);
			break;
		case VERDADEIRO:
			symbols.push(&Termo_prime);
			symbols.push(&Fator);
			break;
		case FALSO:
			symbols.push(&Termo_prime);
			symbols.push(&Fator);
			break;
		case STRING:
			symbols.push(&Termo_prime);
			symbols.push(&Fator);
			break;
		default:
			error(l);
			break;
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
		case MAIS:
			break;
		case SUB:
			break;
		case OU:
			break;
		case MUL:
			symbols.push(&Termo_prime);
			symbols.push(&Fator);
			symbols.push(&mul);
			break;
		case DIV:
			symbols.push(&Termo_prime);
			symbols.push(&Fator);
			symbols.push(&div);
			break;
		case BARRA:
			symbols.push(&Termo_prime);
			symbols.push(&Fator);
			symbols.push(&barra);
			break;
		case E:
			symbols.push(&Termo_prime);
			symbols.push(&Fator);
			symbols.push(&e);
			break;
		default:
			error(l);
			break;
	}
	return NULO;
}

token_t parser::Fator(lexeme& l){
	switch(l.get_tok() ){
		case ID:
			symbols.push(&FatorAux);
			symbols.push(&id);
			break;
		case ABRE_PAR:
			symbols.push(&fecha_par);
			symbols.push(&Expressao);
			symbols.push(&abre_par);
		case NUM_INTEIRO:
			symbols.push(&num_inteiro);
			break;
		case NAO:
			symbols.push(&Fator);
			symbols.push(&nao);
		case NUM_REAL:
			symbols.push(&num_real);
			break;
		case VERDADEIRO:
			symbols.push(&verdadeiro);
			break;
		case FALSO:
			symbols.push(&falso);
			break;
		case STRING:
			symbols.push(&string);
			break;
		default:
			error(l);
			break;
	}
	return NULO;
}

token_t parser::FatorAux(lexeme& l){
	switch(l.get_tok() ){
		case PONTO_VIRG:
			symbols.push(&Variavel_prime);
			break;
		case ABRE_PAR:
			symbols.push(&fecha_par);
			symbols.push(&ExprIter);
			symbols.push(&abre_par);
			break;
		case FECHA_PAR:
			symbols.push(&Variavel_prime);
			break;
		case IGUAL:
			symbols.push(&Variavel_prime);
			break;
		case ABRE_COL:
			symbols.push(&Variavel_prime);
			break;
		case FECHA_COL:
			symbols.push(&Variavel_prime);
			break;
		case VIRG:
			symbols.push(&Variavel_prime);
			break;
		case ENTAO:
			symbols.push(&Variavel_prime);
			break;
		case FACA:
			symbols.push(&Variavel_prime);
			break;
		case PASSO:
			symbols.push(&Variavel_prime);
			break;
		case ATE:
			symbols.push(&Variavel_prime);
			break;
		case MAIS:
			symbols.push(&Variavel_prime);
			break;
		case SUB:
			symbols.push(&Variavel_prime);
			break;
		case OU:
			symbols.push(&Variavel_prime);
			break;
		case MUL:
			symbols.push(&Variavel_prime);
			break;
		case BARRA:
			symbols.push(&Variavel_prime);
			break;
		case DIV:
			symbols.push(&Variavel_prime);
			break;
		case E:
			symbols.push(&Variavel_prime);
			break;
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
			symbols.push(&fecha_col);
			symbols.push(&ExprIter);
			symbols.push(&abre_col);
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
			error(l);
			break;
	}
	return NULO;
}

token_t parser::Variavel(lexeme& l){
	switch(l.get_tok() ){
		case ID:
			symbols.push(&Variavel_prime);
			symbols.push(&id);
			break;
		default:
			error(l);
			break;
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
			symbols.push(&ExprIter);
			symbols.push(&virg);
			break;
		default:
			error(l);
			break;
	}
	return NULO;
}

token_t parser::ExprIter(lexeme& l){
	switch(l.get_tok() ){
		case ID:
			symbols.push(&ExprIter_prime);
			symbols.push(&Expressao);
			break;
		case ABRE_PAR:
			symbols.push(&ExprIter_prime);
			symbols.push(&Expressao);
			break;
		case NUM_INTEIRO:
			symbols.push(&ExprIter_prime);
			symbols.push(&Expressao);
			break;
		case DIFERENTE:
			symbols.push(&ExprIter_prime);
			symbols.push(&Expressao);
			break;
		case MENOR:
			symbols.push(&ExprIter_prime);
			symbols.push(&Expressao);
			break;
		case MENOR_IGUAL:
			symbols.push(&ExprIter_prime);
			symbols.push(&Expressao);
			break;
		case MAIOR_IGUAL:
			symbols.push(&ExprIter_prime);
			symbols.push(&Expressao);
			break;
		case MAIOR:
			symbols.push(&ExprIter_prime);
			symbols.push(&Expressao);
			break;
		case MAIS:
			symbols.push(&ExprIter_prime);
			symbols.push(&Expressao);
			break;
		case SUB:
			symbols.push(&ExprIter_prime);
			symbols.push(&Expressao);
			break;
		case NAO:
			symbols.push(&ExprIter_prime);
			symbols.push(&Expressao);
			break;
		case NUM_REAL:
			symbols.push(&ExprIter_prime);
			symbols.push(&Expressao);
			break;
		case VERDADEIRO:
			symbols.push(&ExprIter_prime);
			symbols.push(&Expressao);
			break;
		case FALSO:
			symbols.push(&ExprIter_prime);
			symbols.push(&Expressao);
			break;
		case STRING:
			symbols.push(&ExprIter_prime);
			symbols.push(&Expressao);
			break;
		default:
			error(l);
			break;
	}
	return NULO;
}

/*************************** TERMINAIS ***************************/

token_t parser::id(lexeme& l){ return ID; }
token_t parser::num_inteiro(lexeme& l){ return NUM_INTEIRO; }
token_t parser::num_real(lexeme& l){ return NUM_REAL; }
token_t parser::verdadeiro(lexeme& l){ return VERDADEIRO; }
token_t parser::falso(lexeme& l){ return FALSO; }
token_t parser::string(lexeme& l){ return STRING; }
token_t parser::abre_par(lexeme& l){ return ABRE_PAR; }
token_t parser::fecha_par(lexeme& l){ return FECHA_PAR; }
token_t parser::abre_col(lexeme& l){ return ABRE_COL; }
token_t parser::fecha_col(lexeme& l){ return FECHA_COL; }
token_t parser::ponto_virg(lexeme& l){ return PONTO_VIRG; }
token_t parser::virg(lexeme& l){ return VIRG; }
token_t parser::igual(lexeme& l){ return IGUAL; }
token_t parser::atribuicao(lexeme& l){ return ATRIBUICAO; }
token_t parser::entao(lexeme& l){ return ENTAO; }
token_t parser::faca(lexeme& l){ return FACA; }
token_t parser::passo(lexeme& l){ return PASSO; }
token_t parser::ate(lexeme& l){ return ATE; }
token_t parser::mais(lexeme& l){ return MAIS; }
token_t parser::sub(lexeme& l){ return SUB; }
token_t parser::ou(lexeme& l){ return OU; }
token_t parser::mul(lexeme& l){ return MUL; }
token_t parser::div(lexeme& l){ return DIV; }
token_t parser::barra(lexeme& l){ return BARRA; }
token_t parser::e(lexeme& l){ return E; }
token_t parser::nao(lexeme& l){ return NAO; }
token_t parser::menor(lexeme& l){ return MENOR; }
token_t parser::menor_igual(lexeme& l){ return MENOR_IGUAL; }
token_t parser::maior(lexeme& l){ return MAIOR; }
token_t parser::maior_igual(lexeme& l){ return MAIOR_IGUAL; }
token_t parser::igual(lexeme& l){ return IGUAL; }
token_t parser::diferente(lexeme& l){ return DIFERENTE; }
token_t parser::se(lexeme& l){ return SE; }
token_t parser::senao(lexeme& l){ return SENAO; }
token_t parser::enquanto(lexeme& l){ return ENQUANTO; }
token_t parser::para(lexeme& l){ return PARA; }
token_t parser::de(lexeme& l){ return DE; }
token_t parser::ate(lexeme& l){ return ATE; }
token_t parser::passo(lexeme& l){ return PASSO; }
token_t parser::fim(lexeme& l){ return FIM; }
token_t parser::leia(lexeme& l){ return LEIA; }
token_t parser::imprima(lexeme& l){ return IMPRIMA; }
token_t parser::algoritmo(lexeme& l){ return ALGORITMO; }
token_t parser::inteiro(lexeme& l){ return INTEIRO; }
token_t parser::real(lexeme& l){ return REAL; }
token_t parser::logico(lexeme& l){ return LOGICO; }
token_t parser::caractere(lexeme& l){ return CARACTERE; }
token_t parser::ponto_virg(lexeme& l){ return PONTO_VIRG; }
token_t parser::dois_pontos(lexeme& l){ return DOIS_PONTOS; }
token_t parser::repita(lexeme& l){ return REPITA; }
token_t parser::procedimento(lexeme& l){ return PROCEDIMENTO; }
token_t parser::funcao(lexeme& l){ return FUNCAO; }
token_t parser::vetor(lexeme& l){ return VETOR; }
token_t parser::matriz(lexeme& l){ return MATRIZ; }
token_t parser::inicio(lexeme& l){ return INICIO; }
token_t parser::fim(lexeme& l){ return FIM; }
token_t parser::se(lexeme& l){ return EOF_TOK; }