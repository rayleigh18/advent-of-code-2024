#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <algorithm>

using namespace std;

long long handleOperator(const long long result, const long long number, char& op) {
    if (op == '|') {
        string resultStr = to_string(result);
        string numberStr = to_string(number);
        return stol(resultStr + numberStr);
    }

    switch (op) {
        case '+':
            return result + number;
        case '*':
            return result * number;

        default:
            return result;
    }
}

bool isPossible(const long long result, const vector<long long>& numbers, vector<char>& operators) {
    if (operators.size() == numbers.size() - 1) {
        long long current = numbers[0];
        for (int i = 0; i < operators.size(); i++) {
            current = handleOperator(current, numbers[i + 1], operators[i]);
        }
        return current == result;
    }
    operators.push_back('+');
    if (isPossible(result, numbers, operators)) {
        return true;
    }
    operators.pop_back();
    operators.push_back('*');
    if (isPossible(result, numbers, operators)) {
        return true;
    }
    operators.pop_back();

    operators.push_back('|');
    if (isPossible(result, numbers, operators)) {
        return true;
    }
    operators.pop_back();
    return false;
}

long long solve(string line) {
    stringstream ss(line);
    string token;
    getline(ss, token, ':');
    long long result = stol(token);

    vector<long long> numbers;
    getline(ss, token);
    stringstream ss2(token);
    while (ss2 >> token) {
        numbers.push_back(stol(token));
    }

    vector<char> operators = {};
    bool possible = isPossible(result, numbers, operators);

    return possible ? result : 0;
}


int main() {
    ifstream inputFile("input.txt");
    // ifstream inputFile("input-test.txt");
    long long result = 0;

    string line;

    while (getline(inputFile, line)) {
        result += solve(line);
    }

    cout << result << endl;
    return 0;
}