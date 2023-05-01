#include <iostream>
#include <iomanip>

#include "graph.h"

int main() {
    regalloc::interference_graph g = regalloc::interference_graph::from(std::cin);
    bool attempts[g.k - 1];

    std::cout << "Graph " << g.title << " -> Physical Registers: " << g.k << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    
    for(int i = g.k; i > 1; i--) {
        regalloc::interference_graph f = g;
        attempts[i - 2] = f.allocate(i, std::cout);
    }

    std::cout 
        << "----------------------------------------\n----------------------------------------";
    std::cout.fill(' ');
    for(int i = g.k; i > 1; i--) {
        std::cout << "\n" << "Graph " << g.title << " -> K = " << std::setw(2) << i 
            << (attempts[i - 2] ? ": Successful Allocation" : ": SPILL");
    }

    return 0;
}