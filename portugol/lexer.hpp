#include <queue>
#include <string>
#include <vector>

#include "defs.hpp"
#include "lexeme.hpp"

struct state{
	const char* lexeme;
	token_t tok;
	bool is_final;
};

class lexer{
    public:
        lexer(transition_t (&matrix)[STATES][ALPHABET_SIZE], 
            state_t (&state_list)[STATES]);
        lexeme& tokenize(std::istream& src, lexeme& l);
        void start_lexing(std::istream& src);
        void get_tokens(std::vector<lexeme>& tokens);
        void show_transition_table();
        void show_states();

    private:
        inline transition_t consume(int ch);
        inline void error(char err_ch);
        void reset_state(std::istream& src, size_t& line, 
            size_t& column);

        std::vector<lexeme> tokens;
        std::queue<char> buf;
        transition_t transitions[STATES][ALPHABET_SIZE],
                     current,
                     last_final;
        state_t states[STATES];
        size_t line = 1,
               column = 1;
};