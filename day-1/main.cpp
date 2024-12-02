#include <iostream>
#include <vector>
#include <fstream>
#include "operations.hpp"
#include "binary_search.hpp"
#include "sort.hpp"

int main() {
    std::ifstream inputFile("input.txt");
    std::vector<int> arr1, arr2;
    int num1, num2;
    
    while (inputFile >> num1 >> num2) {
        arr1.push_back(num1);
        arr2.push_back(num2);
    }
    
    sortVector(arr1);
    sortVector(arr2);

    std::cout << findDistance(arr1, arr2) << std::endl;
    std::cout << findSimilarityScore(arr1, arr2) << std::endl;
    
    return 0;
}

