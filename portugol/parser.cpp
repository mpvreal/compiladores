#include <iostream>

#include "parser.hpp"

void parser::start_parsing(std::vector<lexeme> token_stream){
    cursor = token_stream.begin();
    symbols.push(&parser::S);

    while( !symbols.empty() ){                                       // enquanto a pilha não estiver vazia
        void (parser::*symbol)(lexeme&) = symbols.top();        // pegue o símbolo no topo da pilh
        symbols.pop();                                             // remova o símbolo do topo da pilha
        (this->*symbol)(*cursor);                                           // execute o símbolo
    }

    if(cursor != token_stream.end() )                               // se o cursor não apontar para o fim da cadeia
        error(*cursor);                                            // houve erro de sintaxe
    else
        std::cout << "PROGRAMA CORRETO.";
}