#include <iostream>
#include <vector>

int offset(const std::vector<int>& dimensions, const std::vector<int>& indexes) {
    int sum = 0,
        product = 1;

    for(int k = 0; k < dimensions.size(); k++) {
        for(int l = k + 1; l < dimensions.size(); l++) {
            product *= dimensions[l];
        }
        sum += indexes[k] * product;
        product = 1;
    }

    return sum;
}

int main() {
    int teste[3][3][3] = { { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} }, 
                            { {10, 11, 12}, {13, 14, 15}, {16, 17, 18} }, 
                            { {19, 20, 21}, {22, 23, 24}, {25, 26, 27} } };
    int flat[27] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 
        23, 24, 25, 26, 27 };

    std::cout << flat[offset({3, 3, 3}, {1, 2, 1})] << " = " << teste[1][2][1] << std::endl;

    return 0;
}