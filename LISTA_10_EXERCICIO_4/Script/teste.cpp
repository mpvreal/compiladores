#include <iostream>

int main(){
    char ch;

    for(int i = 50; i < 55; i++){
        std::cin.putback(i);
    }

    while( (ch = std::cin.get()) != EOF){
        std::cout << ch << std::endl;
    }

    return 0;
}