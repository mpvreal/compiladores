/* ALUNO:   MATHEUS PIRES VILA REAL
 * Nº:      202000560352
 */
#include <iostream>

#include "lexer.hpp"

#define DEAD_STATE 0

lexer::lexer(int transitions[ALPHABET_SIZE][STATES], 
    bool finals[STATES], size_t num_states){

    this->_num_states = num_states;

    for(int i = 0; i < ALPHABET_SIZE; i++){
        for(int j = 0; j < num_states; j++){

            this->_automaton._transitions[i][j] 
                = transitions[i][j];
            this->_automaton._finals[j] = finals[j];
        }
    }

    this->_state._init = 1;
    this->_state._curr_state = 1;
}

void lexer::tokenize(std::string str){

    std::string::iterator cursor = str.begin(),
                          cursor_buf = cursor;

    std::string token;
    int tokens = 0;
    char ch = 0;

    while(true){

        ch = *cursor;

        if(this->consume(ch)){
            ++cursor;

        } else{
            if(this->_state._last_final != 9)
                token.assign(cursor_buf, cursor);
            else
                token.assign("ERRO");

            if(*(token.rbegin()) == '\n')
                token.pop_back();
            if(tokens)
                std::cout << '\n';
            std::cout << token;
            
            tokens++;
            cursor_buf = cursor;
            this->reset();

            if(ch == EOF)
                break;
        }
    };

    this->reset();
}

int lexer::consume(char ch){

    if(ch < 0)
        return 0;

    this->_state._curr_state = this->
        _automaton._transitions[ch][this->_state._curr_state];

    if(this->_automaton._finals[this->_state._curr_state])
        this->_state._last_final = this->_state._curr_state;

    return this->_state._curr_state;
}

int lexer::get_last_final_state(){

    return this->_state._last_final;
}

void lexer::reset(){

    this->_state._curr_state = this->_state._init;
    this->_state._last_final = 0;
}