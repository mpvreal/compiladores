#ifndef LEXER_HPP
#define LEXER_HPP

#include <list>
#include <string>

typedef enum tokens{
    ERROR, IF, THEN, ELSE, BEGIN, END, PRINT, SEMI, NUM, EQ, NL
} token;
typedef std::list<token> token_string;

const std::string lexemes[] = 
    {"", "if", "then", "else", "begin", "end", "print", ";", "num",
     "=", "quebra de linha"};

class parser{
  public:
    parser(std::string input);
    ~parser();
    int parse();
    void show_tokens();

  private:
    std::list<token_string> input;
    token tok;

    inline token getToken();
    inline void advance();
    inline void error(const std::string t);
    inline void error_unterminated_str();
    inline void eat(token t);
    inline void E();
    void S();
    void L();
    void seek_nl();
};

#endif