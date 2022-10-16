#include "my_string.hpp"

static inline void strip(std::string &input){
    std::string::iterator start_it = input.begin();
    std::string::reverse_iterator end_it = input.rbegin();
    while (std::isspace(*start_it))
        ++start_it;
    while (std::isspace(*end_it))
        ++end_it;
    
    input.assign(start_it, end_it.base());
}