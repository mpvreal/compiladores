#include <iostream>
#include <cstdlib>

#include "lexer.hpp"

lexer::lexer(transition_t (&matrix)[STATES][ALPHABET_SIZE], 
    state_t (&state_list)[STATES]){
    for(int i = 0; i < STATES; i++){
        for(int j = 0; j < ALPHABET_SIZE; j++){
            transitions[i][j] = matrix[i][j];
        }
        states[i] = state_list[i];
    }
    current = INITIAL_STATE;
    last_final = ERROR_STATE;
}

void lexer::start_lexing(std::istream& src){
    std::string text;
    token_t tok;
    size_t line = 1,
           column = 1;
    char ch;

    do{
        ch = src.get();
        buf.push(ch);
        if(consume(ch)){
            while(states[current].is_final && !buf.empty()){
                switch(buf.front()){
                    case '\n':
                        line++;
                        column = 1;
                        break;
                    case '\t':
                        column += 4;
                        break;
                    default:
                        column++;
                }
                text.push_back(buf.front());
                buf.pop();
            }
        }
        else{
            tok = states[last_final].tok;

            if(tok == NULO){
                error(ch);
                reset_state(src, line, column);
                return;
            }

            if( !(tok == WHITESPACE || tok == LINE_COMMENT || tok == BLOCK_COMMENT) )
                tokens.push_back(lexeme(text, tok, this->line, this->column));

            reset_state(src, line, column);
            text.clear();
        }
    } while(ch != EOF);

    tokens.push_back(lexeme(EOF_TOK, line, column));
}

inline transition_t lexer::consume(int ch){
    if(ch < 0 || ch >= ALPHABET_SIZE)
        return ERROR_STATE;

    // std::cout << (int) current << '-' << (char) ch;  // debug jajajajajaja
    current = transitions[current][ch];
    // std::cout << "->" << (int) current << std::endl; // debug jajajajajaj

    if(states[current].is_final == true)
        last_final = current;

    return current;
}

void lexer::get_tokens(std::vector<lexeme>& tokens){
    tokens = this->tokens;
}

void lexer::reset_state(std::istream& src, size_t& line, 
    size_t& column){
    size_t buf_size = buf.size();
    int next_cursor_pos;
    char ch_buf[buf_size];

    for(int i = 0; i < buf_size; i++){
        ch_buf[i] = buf.front();
        buf.pop();
    }

    next_cursor_pos = (last_final)? 0 : 1;
    for(int i = buf_size - 1; i >= next_cursor_pos; i--)
        src.putback(ch_buf[i]);

    this->line = line;
    this->column = column;
    current = INITIAL_STATE;
    last_final = ERROR_STATE;
}

inline void lexer::error(char err_ch){
    std::cout << "ERRO LEXICO. Linha: " << line <<" Coluna: " << 
        column << " -> \'" << err_ch << "\'";
    std::exit(1);
}

void lexer::show_transition_table(){
    for(int i = 0; i < STATES; i++){
        for(int j = 0; j < ALPHABET_SIZE; j++){
            std::cout << (int) transitions[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void lexer::show_states(){
    for(int i = 0; i < STATES; i++){
        std::cout << "{ " << states[i].lexeme << ", " << 
        states[i].is_final << " }" << std::endl;
    }
}