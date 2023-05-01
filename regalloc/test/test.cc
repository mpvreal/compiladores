#include <iostream>
#include <sstream>
#include <string>

int main() {
    std::string line;
    std::getline(std::cin, line);

    std::istringstream iss(line);

    int a, b, c;

    iss >> line;
    iss >> a >> b >> c;

    std::cout << a << ' ' << b << ' ' << c << std::endl;

    return 0;
}