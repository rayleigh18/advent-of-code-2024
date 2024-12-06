#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <algorithm>

using namespace std;

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

bool checkNumberComply(vector<int> numbers, unordered_map<int, vector<int>> rules) {
    bool isPossible = true;
    for (int i = 0; i < numbers.size(); i++) {
        int number = numbers[i];
        if (rules.count(number) == 0) {
            continue;
        }
        bool isRuleBreak = false;
        auto ruleToApplied = rules[number];
        for (const auto rule: ruleToApplied) {
            if (!isRuleComply(rule, i, numbers)) {
                isRuleBreak = true;
                break;
            }
        }
        if (isRuleBreak) {
            isPossible = false;
            break;
        }
    }
    return isPossible;
}

// Custom comparison function for sorting based on rules
bool compareWithRules(int a, int b, const unordered_map<int, vector<int>>& rules) {
    // Check if a must come before b based on rules
    if (rules.count(a) > 0) {
        const auto& aRules = rules.at(a);
        if (find(aRules.begin(), aRules.end(), b) != aRules.end()) {
            return true;  // a should come before b
        }
    }
    
    // Check if b must come before a based on rules
    if (rules.count(b) > 0) {
        const auto& bRules = rules.at(b);
        if (find(bRules.begin(), bRules.end(), a) != bRules.end()) {
            return false;  // b should come before a
        }
    }
    
    // If no rules apply, maintain original order
    return false;
}

// Sort the numbers vector
void sortBasedOnRules(vector<int>& numbers, const unordered_map<int, vector<int>>& rules) {
    sort(numbers.begin(), numbers.end(), 
        [&rules](int a, int b) { return compareWithRules(a, b, rules); });
}

int main() {
    ifstream inputFile("input.txt");
    // ifstream inputFile("input-test.txt");

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
            // split by |
            vector<int> rule = {};
            stringstream ss(line);
            string token;
            while (getline(ss, token, '|')) {
                rule.push_back(stoi(token));
            }
            inputToRules(rules, rule[1], rule[0]);
        } else {
            vector<int> numbers = {};
            stringstream ss(line);
            string token;
            while (getline(ss, token, ',')) {
                numbers.push_back(stoi(token));
            }
            bool isPossible = checkNumberComply(numbers, rules);
            if (isPossible) {
                result += numbers[numbers.size() / 2];
            }
        }
    }

    cout << result << endl;
    return 0;
}