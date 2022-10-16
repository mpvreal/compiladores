/* ALUNO:   MATHEUS PIRES VILA REAL
 * Nº:      202000560352
 */
#include <iostream>
#include <queue>

#include "lexer.hpp"

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
                    
                    if(chars.front() != '\n')
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

                if(this->_state._last_final != 12)
                    std::cout << token << ' ' ;

                std::cout << this->_state._states
                    [this->_state._last_final].name;

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

// void lexer::tokenize(std::string str){

//     std::string::iterator cursor = str.begin(),
//                           cursor_buf = cursor;

//     std::string token;
//     int tokens = 0;
//     char ch = 0;

//     while(true){

//         ch = *cursor;

//         if(ch == '\n' || this->consume(ch)){
//             ++cursor;

//         } else{
//             if(this->_state._last_final != 13){
//                 if(this->_state._last_final != 12){
//                     token.assign(cursor_buf, cursor);

//                     if(*(token.end() - 1) >= 0 && 
//                         *(token.end() - 1) <= 32){

//                         token.pop_back();
//                     }

//                 } else {
//                     token.assign("");
//                 }
//             } else{

//                 token.assign("");
//             }

//             if(tokens)
//                 std::cout << '\n';

//             std::cout << token;

//             if(token.size() > 0)
//                 std::cout << ' ';

//             std::cout << this->_state.
//                 _states[this->_state._last_final].name;

//             cursor_buf = cursor;
//             this->reset();
//             ++tokens;

//             if(ch == EOF)
//                 break;
//         }
//     };

//     this->reset();
// }

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
    this->_state._last_final = 0;
}