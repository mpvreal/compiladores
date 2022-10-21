#include <iostream>

#include "parser.hpp"

// inline void parser::error(lexeme& l){
//     std::cout << "ERRO DE SINTAXE. Linha: " << l.get_line() 
//         << " Coluna: " << l.get_column() << " -> '" << 
//         l.get_content() << '\'';

//     exit(1);
// }

void parser::start_parsing(std::vector<lexeme> token_stream){
    cursor = token_stream.begin();
    symbols.push(&parser::S);

    while( !symbols.empty() ){                                       // enquanto a pilha não estiver vazia
        token_t (parser::*symbol)(lexeme&) = symbols.top();        // pegue o símbolo no topo da pilha
        symbols.pop();                                             // remova o símbolo do topo da pilha
        // std::cout << "Token: " << cursor->get_content();
        if( (this->*symbol)(*cursor) == cursor->get_tok() ){       // chame o símbolo, empilhando suas produções e compare seu valor de token
            ++cursor;                                              // se valor token == token na cadeia apontado pelo cursor, avance o cursor
        }
    }
    if(cursor != token_stream.end() )                               // se o cursor não apontar para o fim da cadeia
        error(*cursor);                                            // houve erro de sintaxe
    else
        std::cout << "CADEIA ACEITA";
}