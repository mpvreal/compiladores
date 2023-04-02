#include <iostream>
#include <list>

union param {
    int i;
    double d;
};

int main() {
    param a = { .d = 3.14 };
    param b;

    b = a;

    std::cout << b.d << std::endl;

    return 0;
}