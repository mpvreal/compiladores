#include <iostream>
#include <bits/stdc++.h>

#include "parser.hpp"

static void strip(std::string &input){
    std::string buffer = input;
    std::string::iterator start_it = buffer.begin();
    std::string::reverse_iterator end_it = buffer.rbegin();
    
    while (std::isspace(*start_it) || *start_it == EOF)
        ++start_it;
    while (std::isspace(*end_it) || *end_it == EOF)
        ++end_it;

    input.assign(start_it, end_it.base());
}

static bool is_number(const std::string& s){
    std::string::const_iterator it = s.begin();

    while(it != s.end() && (std::isdigit(*it) | *it == '+' | 
        *it == '-') ) 
        ++it;

    return !s.empty() && it == s.end();
}

static std::string error_tok = "";
static std::string error_expected_tok = "";
static int strings = 0;
static bool valid = true;

parser::parser(std::string input){
    strip(input);
    input.push_back(' ');
    std::stringstream stream = std::stringstream(input);
    std::stringstream buf_stream;
    std::string buffer, tok;
    token_string line;
    char ch;

    while(true){
        while( (ch = stream.get()) != '\n' && ch != EOF)
            buffer.push_back(ch);
        
        buf_stream = std::stringstream(buffer);
        while(buf_stream >> tok){
            strip(tok);
            if(tok == "if")
                line.push_back(IF);
            else
            if(tok == "then")
                line.push_back(THEN);
            else
            if(tok == "else")
                line.push_back(ELSE);
            else
            if(tok == "begin")
                line.push_back(BEGIN);
            else
            if(tok == "end")
                line.push_back(END);
            else
            if(tok == "print")
                line.push_back(PRINT);
            else
            if(tok == ";")
                line.push_back(SEMI);
            else
            if(tok == "=")
                line.push_back(EQ);
            else
                if(is_number(tok))
                    line.push_back(NUM);
        }
        this->input.push_back(line);

        line.clear();
        buffer.clear();

        if(ch == EOF)
            break;
    }
    this->tok = getToken();
}

parser::~parser(){}

inline token parser::getToken(){
    token output = ERROR;

        // while(!this->input.empty() && this->input.front().empty())
        //     this->input.pop_front();
    if(this->input.empty() == false){
        if(this->input.front().empty() == false){
            output = this->input.front().front();
            this->input.front().pop_front();    
        }
        else{
            output = NL;
            this->input.pop_front();
        }
    }
    return output;
}

inline void parser::advance(){
    this->tok = getToken();
}

inline void parser::eat(token t){
    if(valid){
        if(this->tok == NL){
            error_unterminated_str();
            return;
        }else{
            if(t == this->tok)
                advance();
            else
                error(lexemes[t]);
        }
    }
}

inline void parser::error(const std::string t){
    if(valid){
        valid = false;
        if(strings > 0)
                std::cout << '\n';
        std::cout << "ERRO SINTATICO EM: " << lexemes[this->tok] 
            << " ESPERADO: " << t;
        // error_tok.assign(lexemes[this->tok]);
        // error_expected_tok.assign(_expected_tok);

        this->input.pop_front();
        this->tok = getToken();
    }
}

inline void parser::error_unterminated_str(){
    if(valid){
        if(strings > 0)
                std::cout << '\n';
        std::cout << "ERRO SINTATICO: CADEIA INCOMPLETA";

        // this->input.pop_front();
        this->tok = getToken();
    }
}

int parser::parse(){
    while(this->input.empty() == false){
        S();
        if(valid){
            if(strings > 0)
                std::cout << '\n';

            std::cout << "CADEIA ACEITA";
        }
        ++strings;
        valid = true;
        if(this->tok == NL)
            advance();
    }
    return 0;
}

inline void parser::E(){
    // std::cout << 'E';
    switch(this->tok){
        case ERROR:
            return;
        case NL:
            error_unterminated_str();
            break;
        default:
            if(valid){
                eat(NUM); eat(EQ); eat(NUM);
            }
            break;
    }
}

void parser::S(){
    // std::cout << 'S' << this->tok;
    if(valid)
    switch(this->tok){
        case IF: 
            eat(IF); E(); eat(THEN); S(); eat(ELSE); S(); 
            break;
        case BEGIN: 
            eat(BEGIN); S(); L(); 
            break;
        case PRINT:
            eat(PRINT); E(); 
            break;
        case NL:
            error_unterminated_str();
            break;
        case ERROR:
            break;
        default:
            error("if, begin, print");
    }
}

void parser::L(){
    // std::cout << 'L';
    if(valid)
    switch(this->tok){
        case END: 
            eat(END); 
            break;
        case SEMI: 
            eat(SEMI); S(); L(); 
            break;
        case ERROR:
            break;
        case NL:
            error_unterminated_str();
            break;
        default:
            error("end, ;"); 
    }
}

void parser::show_tokens(){
    for(auto i : this->input){
        for(auto j : i){
            std::cout << lexemes[j] << ' ';
        }
        std::cout << '\n';
    }
}