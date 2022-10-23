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
		inline void error(lexeme& l){
			std::cout << "ERRO DE SINTAXE. Linha: " << l.get_line() 
				<< " Coluna: " << l.get_column() << " -> '" << 
				l.get_content() << '\'';

			exit(1);
		};
        std::stack<token_t (parser::*)(lexeme&)> symbols;
        std::vector<lexeme>::iterator cursor;
		
		token_t S(lexeme& l),
                Programa(lexeme& l),
                ProcedimentoFuncao(lexeme& l),
                DeclaraProcedimento(lexeme& l),
                DeclaraFuncao(lexeme& l),
                Parametros(lexeme& l),
                DeclaraParametros(lexeme& l),
                BlocoVariaveis(lexeme& l),
                Declaracoes_prime(lexeme& l),
                Declaracoes(lexeme& l),
                DeclaraTipo(lexeme& l),
                DeclaraVariaveis(lexeme& l),
                DeclaraIdentificador(lexeme& l),
                DeclaraIdentificador_prime(lexeme& l),
                VetorMatriz(lexeme& l),
                Dimensao_prime(lexeme& l),
                Dimensao(lexeme& l),
                TipoBasico(lexeme& l),
                BlocoComandos(lexeme& l),
                BlocoComandos_prime(lexeme& l),
                ListaComandos_prime(lexeme& l),
                ListaComandos(lexeme& l),
                Comandos_prime(lexeme& l),
                ComandosAux(lexeme& l),
                Comandos(lexeme& l),
                ComandosFimSeSenao(lexeme& l),
                ComandosParaPasso(lexeme& l),
                Expressao(lexeme& l),
                Expressao_prime(lexeme& l),
                ExpressaoSimples(lexeme& l),
                ExpressaoSimples_prime(lexeme& l),
                Termo(lexeme& l),
                Termo_prime(lexeme& l),
                Fator(lexeme& l),
                FatorAux(lexeme& l),
                Variavel_prime(lexeme& l),
                Variavel(lexeme& l),
                ExprIter_prime(lexeme& l),
                ExprIter(lexeme& l),
                id(lexeme& l),
	            num_inteiro(lexeme& l),
	            num_real(lexeme& l),
	            ponto(lexeme& l),
	            e(lexeme& l),
	            ate(lexeme& l),
	            ou(lexeme& l),
	            algoritmo(lexeme& l),
	            para(lexeme& l),
	            passo(lexeme& l),
	            procedimento(lexeme& l),
	            caractere(lexeme& l),
	            real(lexeme& l),
	            repita(lexeme& l),
	            de(lexeme& l),
	            div(lexeme& l),
				barra(lexeme& l),
	            se(lexeme& l),
	            senao(lexeme& l),
	            variaveis(lexeme& l),
	            verdadeiro(lexeme& l),
	            tipo(lexeme& l),
	            nao(lexeme& l),
	            matriz(lexeme& l),
	            falso(lexeme& l),
	            faca(lexeme& l),
	            fim(lexeme& l),
	            funcao(lexeme& l),
	            entao(lexeme& l),
	            enquanto(lexeme& l),
	            leia(lexeme& l),
	            logico(lexeme& l),
	            imprima(lexeme& l),
	            inteiro(lexeme& l),
	            maior(lexeme& l),
	            menor(lexeme& l),
	            mais(lexeme& l),
	            sub(lexeme& l),
	            mul(lexeme& l),
	            maior_igual(lexeme& l),
	            menor_igual(lexeme& l),
	            string(lexeme& l),
	            block_comment(lexeme& l),
	            line_comment(lexeme& l),
	            whitespace(lexeme& l),
	            diferente(lexeme& l),
	            atribuicao(lexeme& l),
	            igual(lexeme& l),
	            ponto_virg(lexeme& l),
	            dois_pontos(lexeme& l),
	            inicio(lexeme& l),
	            virg(lexeme& l),
	            abre_col(lexeme& l),
	            fecha_col(lexeme& l),
	            abre_par(lexeme& l),
	            fecha_par(lexeme& l),
				vetor(lexeme& l),
                eof_tok(lexeme& l);
};

#endif  