/* ALUNO:   MATHEUS PIRES VILA REAL
 * Nº:      202000560352
 */
#include <iostream>
#include <queue>
#include <stdio.h>

#include "lexer.hpp"

static std::string strip(std::string &input){
    std::string::iterator start_it = input.begin();
    std::string::reverse_iterator end_it = input.rbegin();
    while (std::isspace(*start_it))
        ++start_it;
    while (std::isspace(*end_it))
        ++end_it;
    return std::string(start_it, end_it.base());
}

lexer::lexer(int transitions[ALPHABET_SIZE][STATES], 
    struct state states[STATES], size_t num_states){

    this->_num_states = num_states;

    for(int i = 0; i < ALPHABET_SIZE; i++){
        for(int j = 0; j < num_states; j++){

            this->_automaton._transitions[i][j] 
                = transitions[i][j];
                
            this->_state._states[j].final = states[j].final;
            this->_state._states[j].name = states[j].name;
        }
    }

    this->_state._init = INIT_STATE;
    this->_state._curr_state = INIT_STATE;
    this->_state._last_final = ERROR_STATE;
}

void lexer::tokenize(std::string str){

    std::queue<char> chars;
    std::string::iterator cursor = str.begin(),
                          cursor_buf = str.begin();
    std::string token = "";
    char ch = 0;
    bool print_ln = false;

    do{
        ch = *cursor;

        if(this->consume(ch)){
            chars.push(ch);

            if(this->_state._states[this->_state._curr_state]
                .final){

                while(!chars.empty()){
         
                    token.push_back(chars.front());
                    chars.pop();
                }
                cursor_buf = cursor;    
            }
            ++cursor;

        } else{
            if(!( ch <= ' ' && token.empty() && chars.empty() )){
         
                if(print_ln)
                    std::cout << '\n';

                std::cout << this->_state._states
                    [this->_state._last_final].name;

                if(this->_state._last_final == 19 || 
                    this->_state._last_final == 22)
                    std::cout << ' ' << token;
            }

            token.clear();
            while(!chars.empty())
                chars.pop();

            print_ln = true;

            cursor = ++cursor_buf;
            this->reset();
        }
    } while(ch != EOF);
}

int lexer::consume(char ch){

    if(ch < 0)
        return 0;

    this->_state._curr_state = this->   
        _automaton._transitions[ch][this->_state._curr_state];

    if(this->_state._states[this->_state._curr_state].final)
        this->_state._last_final = this->_state._curr_state;

    return this->_state._curr_state;
}

int lexer::get_last_final_state(){

    return this->_state._last_final;
}

void lexer::reset(){

    this->_state._curr_state = this->_state._init;
    this->_state._last_final = ERROR_STATE;
}