#include "operations.hpp"
#include <iostream>

void printVector(std::vector<int>& vect) {
    for (int i = 0; i < vect.size(); i++) {
        std::cout << vect[i] << " ";
    }
    std::cout << "End \n";
}

int findDistance(std::vector<int> vect1, std::vector<int> vect2) {
    int total = 0;
    for (int i = 0; i < vect1.size(); i++) {
        if(vect1[i] > vect2[i]) {
            total += vect1[i] - vect2[i];
        }
        else {
            total += vect2[i] - vect1[i];
        }
    }
    return total;
}