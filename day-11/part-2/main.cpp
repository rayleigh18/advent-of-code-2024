#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>
using namespace std;


map<pair<long long, int>, long long> dp;

long long solve(long long value, int repetitions) {
    if (repetitions == 0) {
        return 1;
    }
    if (value == 0) {
        return solve(1, repetitions - 1);
    }
    if (dp.find(make_pair(value, repetitions)) != dp.end()) {
        return dp[make_pair(value, repetitions)];
    }

    string valueStr = to_string(value);
    int strValue = valueStr.size();
    if (strValue % 2 == 0) {
        int half = strValue / 2;
        long long left = stoll(valueStr.substr(0, half));
        long long right = stoll(valueStr.substr(half, strValue));
        dp[make_pair(value, repetitions)] = solve(left, repetitions - 1) + solve(right, repetitions - 1);
    } else {
        dp[make_pair(value, repetitions)] = solve(value * 2024, repetitions - 1);
    }
    return dp[make_pair(value, repetitions)];
}

int main() {
    auto start_time = chrono::high_resolution_clock::now();
    ifstream inputFile("input.txt");
    // ifstream inputFile("input-test.txt");
    string line;
    long long result = 0;
    getline(inputFile, line);
    stringstream ss(line);
    string value;
    while (getline(ss, value, ' ')) {
        result += solve(stoll(value), 75);
    }

    cout << result << endl;


    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
    cout << "Time taken: " << duration.count() << " milliseconds" << endl;
    return 0;
}