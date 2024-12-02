#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

bool isDifferenceSafe(int num1, int num2) {
    int diff = abs(num1 - num2);
    return diff >= 1 && diff <= 3;
}

bool isDecreasing(int num1, int num2) {
    return num2 < num1;    
}

void printVector(vector<int> vec) {
    for (int num : vec) {
        cout << num << " ";
    }
    cout << endl;
}

bool isSafe(vector<int> numbers) {
    bool decreaseConst = isDecreasing(numbers[0], numbers[1]);
    for (int i = 0; i < numbers.size() - 1; i++) {
        if (decreaseConst != isDecreasing(numbers[i], numbers[i + 1]) || !isDifferenceSafe(numbers[i], numbers[i + 1])) return false;
    }
    return true;
}

int main() {
    // ifstream inputFile("input-test.txt");
    ifstream inputFile("input.txt");
    string line;

    int safeCount = 0;
    
    while (getline(inputFile, line)) {
        vector<int> numbers;
        stringstream ss(line);
        string number;
        
        while (ss >> number) {
            numbers.push_back(stoi(number));
        }

        if (isSafe(numbers)) safeCount++;
    }

    cout << safeCount << endl;


    inputFile.close();
    return 0;
}

