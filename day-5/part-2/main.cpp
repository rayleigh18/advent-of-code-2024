#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <algorithm>

using namespace std;

bool compareWithRules(int a, int b, const unordered_map<int, vector<int>>& rules) {
    if (rules.count(a) > 0) {
        const auto& aRules = rules.at(a);
        if (find(aRules.begin(), aRules.end(), b) != aRules.end()) {
            return true;
        }
    }
    
    return false;
}

void sortBasedOnRules(vector<int>& numbers, const unordered_map<int, vector<int>>& rules) {
    sort(numbers.begin(), numbers.end(), 
        [&rules](int a, int b) { return compareWithRules(a, b, rules); });
}

void inputToRules(unordered_map<int, vector<int>>& rules, int key, int value) {
    if (rules.count(key) == 0) {
        rules[key] = vector<int>();
    }
    rules[key].push_back(value);
}

void printVector(vector<int> a) {
    for (auto b: a) {
        cout << b << " ";
    }
    cout << endl;
}

bool isRuleComply(int rule, int start, vector<int> numbers) {
    for (int i = start; i < numbers.size(); i++) {
        if (numbers[i] == rule) {
            return false;
        }
    }
    
    return true;
}

bool checkNumberComply(const vector<int>& numbers, const unordered_map<int, vector<int>>& rules) {
    for (int i = 0; i < numbers.size(); i++) {
        for (int j = i + 1; j < numbers.size(); j++) {
            int first = numbers[i];
            int second = numbers[j];
            
            if (rules.count(second) > 0) {
                const auto& secondRules = rules.at(second);
                if (find(secondRules.begin(), secondRules.end(), first) != secondRules.end()) {
                    return false;
                }
            }
        }
    }
    return true;
}

int findIndex(vector<int>& v, int val) {
    for (int i = 0; i < v.size(); i++) {
      
          // When the element is found
        if (v[i] == val) {
            return i;
        }
    }
      
      // When the element is not found
      return -1;
}

int fixNumberToComplyRulesAndReturnMiddle(vector<int> numbers, const unordered_map<int, vector<int>>& rules) {
    sortBasedOnRules(numbers, rules);
    return numbers[numbers.size() / 2];
}

int main() {
    ifstream inputFile("input.txt");

    unordered_map<int, vector<int>> rules;
    int result = 0;
    string line;
    int isRule = true;

    while (getline(inputFile, line)) {
        if (line == "") {
            isRule = false;
            continue;
        }
        if (isRule) {
            vector<int> rule = {};
            stringstream ss(line);
            string token;
            while (getline(ss, token, '|')) {
                rule.push_back(stoi(token));
            }
            inputToRules(rules, rule[0], rule[1]);
        } else {
            vector<int> numbers = {};
            stringstream ss(line);
            string token;
            while (getline(ss, token, ',')) {
                numbers.push_back(stoi(token));
            }
            if (!checkNumberComply(numbers, rules)) {
                result += fixNumberToComplyRulesAndReturnMiddle(numbers, rules);
            }
        }
    }

    cout << result << endl;
    return 0;
}