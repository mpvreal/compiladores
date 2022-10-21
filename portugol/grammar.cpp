#include "parser.hpp"

/************************* NÃO TERMINAIS *************************/

void parser::S(lexeme& l){
	switch(l.get_tok() ){
		case ALGORITMO:
            symbols.push(&parser::eof_tok);
            symbols.push(&parser::Programa);
			break;
		default:
			error(l);break;
	}
}

void parser::Programa(lexeme& l){
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
}

void parser::ProcedimentoFuncao(lexeme& l){
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
}

void parser::DeclaraProcedimento(lexeme& l){
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
}

void parser::DeclaraFuncao(lexeme& l){
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
}

void parser::Parametros(lexeme& l){
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
}

void parser::DeclaraParametros(lexeme& l){
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
}

void parser::BlocoVariaveis(lexeme& l){
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
}

void parser::Declaracoes_prime(lexeme& l){
	switch(l.get_tok() ){
		case ID:
			symbols.push(&parser::Declaracoes);
			break;
		case PROCEDIMENTO:
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
}

void parser::Declaracoes(lexeme& l){
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
}

void parser::DeclaraTipo(lexeme& l){
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
}

void parser::DeclaraVariaveis(lexeme& l){
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
}

void parser::DeclaraIdentificador_prime(lexeme& l){
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
}

void parser::DeclaraIdentificador(lexeme& l){
	switch(l.get_tok() ){
		case ID:
			symbols.push(&parser::DeclaraIdentificador_prime);
			symbols.push(&parser::id);
			break;
		default:
			error(l);break;
	}
}

void parser::VetorMatriz(lexeme& l){
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
}

void parser::Dimensao_prime(lexeme& l){
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
}

void parser::Dimensao(lexeme& l){
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
}

void parser::TipoBasico(lexeme& l){
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
}

void parser::BlocoComandos(lexeme& l){
	switch(l.get_tok() ){
		case INICIO:
			symbols.push(&parser::fim);
			symbols.push(&parser::ListaComandos);
			symbols.push(&parser::inicio);
			break;
		default:
			error(l);break;
	}
}

void parser::ListaComandos_prime(lexeme& l){
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
}

void parser::ListaComandos(lexeme& l){
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
}

void parser::Comandos_prime(lexeme& l){
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
}

void parser::ComandosAux(lexeme& l){
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
}

void parser::Comandos(lexeme& l){
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
}

void parser::ComandosFimSeSenao(lexeme& l){
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
}

void parser::ComandosParaPasso(lexeme& l){
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
}

void parser::Expressao(lexeme& l){
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
}

void parser::Expressao_prime(lexeme& l){
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
}

void parser::ExpressaoSimples(lexeme& l){
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
}

void parser::ExpressaoSimples_prime(lexeme& l){
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
}

void parser::Termo(lexeme& l){
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
}

void parser::Termo_prime(lexeme& l){
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
}

void parser::Fator(lexeme& l){
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
}

void parser::FatorAux(lexeme& l){
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
}

void parser::Variavel_prime(lexeme& l){
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
}

void parser::Variavel(lexeme& l){
	switch(l.get_tok() ){
		case ID:
			symbols.push(&parser::Variavel_prime);
			symbols.push(&parser::id);
			break;
		default:
			error(l);break;
	}
}

void parser::ExprIter_prime(lexeme& l){
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
}

void parser::ExprIter(lexeme& l){
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
}

/*************************** TERMINAIS ***************************/
void parser::id(lexeme& l){
	switch(l.get_tok() ){
		case ID:
			++cursor;break;
		default:
			error(l);break;
	}
}
void parser::num_inteiro(lexeme& l){
	switch(l.get_tok() ){
		case NUM_INTEIRO:
			++cursor;break;
		default:
			error(l);break;
	}
}
void parser::num_real(lexeme& l){
	switch(l.get_tok() ){
		case NUM_REAL:
			++cursor;break;
		default:
			error(l);break;
	}
}
void parser::ponto(lexeme& l){
	switch(l.get_tok() ){
		case PONTO:
			++cursor;break;
		default:
			error(l);break;
	}
}
void parser::e(lexeme& l){
	switch(l.get_tok() ){
		case E:
			++cursor;break;
		default:
			error(l);break;
	}
}
void parser::ate(lexeme& l){
	switch(l.get_tok() ){
		case ATE:
			++cursor;break;
		default:
			error(l);break;
	}
}
void parser::ou(lexeme& l){
	switch(l.get_tok() ){
		case OU:
			++cursor;break;
		default:
			error(l);break;
	}
}
void parser::algoritmo(lexeme& l){
	switch(l.get_tok() ){
		case ALGORITMO:
			++cursor;break;
		default:
			error(l);break;
	}
}
void parser::para(lexeme& l){
	switch(l.get_tok() ){
		case PARA:
			++cursor;break;
		default:
			error(l);break;
	}
}
void parser::passo(lexeme& l){
	switch(l.get_tok() ){
		case PASSO:
			++cursor;break;
		default:
			error(l);break;
	}
}
void parser::procedimento(lexeme& l){
	switch(l.get_tok() ){
		case PROCEDIMENTO:
			++cursor;break;
		default:
			error(l);break;
	}
}
void parser::caractere(lexeme& l){
	switch(l.get_tok() ){
		case CARACTERE:
			++cursor;break;
		default:
			error(l);break;
	}
}
void parser::real(lexeme& l){
	switch(l.get_tok() ){
		case REAL:
			++cursor;break;
		default:
			error(l);break;
	}
}
void parser::repita(lexeme& l){
	switch(l.get_tok() ){
		case REPITA:
			++cursor;break;
		default:
			error(l);break;
	}
}
void parser::de(lexeme& l){
	switch(l.get_tok() ){
		case DE:
			++cursor;break;
		default:
			error(l);break;
	}
}
void parser::div(lexeme& l){
	switch(l.get_tok() ){
		case DIV:
			++cursor;break;
		default:
			error(l);break;
	}
}
void parser::barra(lexeme& l){
	switch(l.get_tok() ){
		case BARRA:
			++cursor;break;
		default:
			error(l);break;
	}
}
void parser::se(lexeme& l){
	switch(l.get_tok() ){
		case SE:
			++cursor;break;
		default:
			error(l);break;
	}
}
void parser::senao(lexeme& l){
	switch(l.get_tok() ){
		case SENAO:
			++cursor;break;
		default:
			error(l);break;
	}
}
void parser::variaveis(lexeme& l){
	switch(l.get_tok() ){
		case VARIAVEIS:
			++cursor;break;
		default:
			error(l);break;
	}
}
void parser::verdadeiro(lexeme& l){
	switch(l.get_tok() ){
		case VERDADEIRO:
			++cursor;break;
		default:
			error(l);break;
	}
}
void parser::tipo(lexeme& l){
	switch(l.get_tok() ){
		case TIPO:
			++cursor;break;
		default:
			error(l);break;
	}
}
void parser::nao(lexeme& l){
	switch(l.get_tok() ){
		case NAO:
			++cursor;break;
		default:
			error(l);break;
	}
}
void parser::matriz(lexeme& l){
	switch(l.get_tok() ){
		case MATRIZ:
			++cursor;break;
		default:
			error(l);break;
	}
}
void parser::falso(lexeme& l){
	switch(l.get_tok() ){
		case FALSO:
			++cursor;break;
		default:
			error(l);break;
	}
}
void parser::faca(lexeme& l){
	switch(l.get_tok() ){
		case FACA:
			++cursor;break;
		default:
			error(l);break;
	}
}
void parser::fim(lexeme& l){
	switch(l.get_tok() ){
		case FIM:
			++cursor;break;
		default:
			error(l);break;
	}
}
void parser::funcao(lexeme& l){
	switch(l.get_tok() ){
		case FUNCAO:
			++cursor;break;
		default:
			error(l);break;
	}
}
void parser::entao(lexeme& l){
	switch(l.get_tok() ){
		case ENTAO:
			++cursor;break;
		default:
			error(l);break;
	}
}
void parser::enquanto(lexeme& l){
	switch(l.get_tok() ){
		case ENQUANTO:
			++cursor;break;
		default:
			error(l);break;
	}
}
void parser::leia(lexeme& l){
	switch(l.get_tok() ){
		case LEIA:
			++cursor;break;
		default:
			error(l);break;
	}
}
void parser::logico(lexeme& l){
	switch(l.get_tok() ){
		case LOGICO:
			++cursor;break;
		default:
			error(l);break;
	}
}
void parser::imprima(lexeme& l){
	switch(l.get_tok() ){
		case IMPRIMA:
			++cursor;break;
		default:
			error(l);break;
	}
}
void parser::inteiro(lexeme& l){
	switch(l.get_tok() ){
		case INTEIRO:
			++cursor;break;
		default:
			error(l);break;
	}
}
void parser::maior(lexeme& l){
	switch(l.get_tok() ){
		case MAIOR:
			++cursor;break;
		default:
			error(l);break;
	}
}
void parser::menor(lexeme& l){
	switch(l.get_tok() ){
		case MENOR:
			++cursor;break;
		default:
			error(l);break;
	}
}
void parser::mais(lexeme& l){
	switch(l.get_tok() ){
		case MAIS:
			++cursor;break;
		default:
			error(l);break;
	}
}
void parser::sub(lexeme& l){
	switch(l.get_tok() ){
		case SUB:
			++cursor;break;
		default:
			error(l);break;
	}
}
void parser::mul(lexeme& l){
	switch(l.get_tok() ){
		case MUL:
			++cursor;break;
		default:
			error(l);break;
	}
}
void parser::maior_igual(lexeme& l){
	switch(l.get_tok() ){
		case MAIOR_IGUAL:
			++cursor;break;
		default:
			error(l);break;
	}
}
void parser::menor_igual(lexeme& l){
	switch(l.get_tok() ){
		case MENOR_IGUAL:
			++cursor;break;
		default:
			error(l);break;
	}
}
void parser::string(lexeme& l){
	switch(l.get_tok() ){
		case STRING:
			++cursor;break;
		default:
			error(l);break;
	}
}
void parser::block_comment(lexeme& l){
	switch(l.get_tok() ){
		case BLOCK_COMMENT:
			++cursor;break;
		default:
			error(l);break;
	}
}
void parser::line_comment(lexeme& l){
	switch(l.get_tok() ){
		case LINE_COMMENT:
			++cursor;break;
		default:
			error(l);break;
	}
}
void parser::whitespace(lexeme& l){
	switch(l.get_tok() ){
		case WHITESPACE:
			++cursor;break;
		default:
			error(l);break;
	}
}
void parser::diferente(lexeme& l){
	switch(l.get_tok() ){
		case DIFERENTE:
			++cursor;break;
		default:
			error(l);break;
	}
}
void parser::atribuicao(lexeme& l){
	switch(l.get_tok() ){
		case ATRIBUICAO:
			++cursor;break;
		default:
			error(l);break;
	}
}
void parser::igual(lexeme& l){
	switch(l.get_tok() ){
		case IGUAL:
			++cursor;break;
		default:
			error(l);break;
	}
}
void parser::ponto_virg(lexeme& l){
	switch(l.get_tok() ){
		case PONTO_VIRG:
			++cursor;break;
		default:
			error(l);break;
	}
}
void parser::dois_pontos(lexeme& l){
	switch(l.get_tok() ){
		case DOIS_PONTOS:
			++cursor;break;
		default:
			error(l);break;
	}
}
void parser::inicio(lexeme& l){
	switch(l.get_tok() ){
		case INICIO:
			++cursor;break;
		default:
			error(l);break;
	}
}
void parser::virg(lexeme& l){
	switch(l.get_tok() ){
		case VIRG:
			++cursor;break;
		default:
			error(l);break;
	}
}
void parser::abre_col(lexeme& l){
	switch(l.get_tok() ){
		case ABRE_COL:
			++cursor;break;
		default:
			error(l);break;
	}
}
void parser::fecha_col(lexeme& l){
	switch(l.get_tok() ){
		case FECHA_COL:
			++cursor;break;
		default:
			error(l);break;
	}
}
void parser::abre_par(lexeme& l){
	switch(l.get_tok() ){
		case ABRE_PAR:
			++cursor;break;
		default:
			error(l);break;
	}
}
void parser::fecha_par(lexeme& l){
	switch(l.get_tok() ){
		case FECHA_PAR:
			++cursor;break;
		default:
			error(l);break;
	}
}
void parser::vetor(lexeme& l){
	switch(l.get_tok() ){
		case VETOR:
			++cursor;break;
		default:
			error(l);break;
	}
}
void parser::eof_tok(lexeme& l){
	switch(l.get_tok() ){
		case EOF_TOK:
			++cursor;break;
		default:
			error(l);break;
	}
}