#include <iostream>
#include <list>

int main() {
    std::list<const void*> l;

    for(const void*& i : l) {
        *((int*) i);
    }

    return 0;
}