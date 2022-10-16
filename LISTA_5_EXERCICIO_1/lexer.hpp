#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>

#include "defs.hpp"

struct states{

  int _curr_state,
      _last_final,
      _init;
};

struct automaton{
    
  int  _transitions[ALPHABET_SIZE][STATES];
  bool _finals[STATES];
};

class lexer{

  public:
    lexer(int transitions[ALPHABET_SIZE][STATES], bool finals[STATES], size_t num_states);
    int get_last_final_state();
    void tokenize(std::string);
    int consume(char ch);
    void reset();

  private:
    struct automaton _automaton;
    struct states _state;

    size_t _num_states;
};

#endif