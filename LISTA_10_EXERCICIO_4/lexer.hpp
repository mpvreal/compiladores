#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>

#include "defs.hpp"

#define ALPHABET_SIZE 128
#define STATES 23

struct state{

  std::string name;
  bool final;
};

struct states{

  struct state _states[STATES];

  int curr_state,
      last_final,
      init;
};

class lexer{

  public:
    lexer(int transitions[ALPHABET_SIZE][STATES], 
      struct state states[STATES], size_t num_states);
    int get_last_final_state();
    void tokenize(std::string);
    int consume(char ch);
    void reset();

  private:
    int transitions[ALPHABET_SIZE][STATES];
    struct states _state;

    // size_t _num_states;
};

#endif