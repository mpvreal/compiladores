#include <iostream>
#include <list>
#include <string>

// struct aaa {
//     std::list<int> l;

//     aaa(std::list<int>& ll) : l(ll) {};
//     ~aaa() {};
// };

// union bbb {
//     struct aaa a;

//     bbb() {};
//     ~bbb() {};
// };

union teste {
    const char* a;
    int b;
};

int main() {
    // inicialize aaa
    teste a;
    a.a = "TRSTE 1 2 3";
    std::cout << a.b << std::endl;

    return 0;
}