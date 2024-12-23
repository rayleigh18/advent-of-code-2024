#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>
#define A_TOKEN 3
#define B_TOKEN 1

using namespace std;

int findToken(int a, int b) {
    return a * A_TOKEN + b * B_TOKEN;
}


int solve(pair<int, int> curr, pair<int, int>& a, pair<int, int>& b, pair<int, int>& prize, map<pair<int, int>, int>& cache) {
    if (cache.find(curr) != cache.end()) {
        return cache[curr];
    }
    if (curr == prize) {
        return 0;
    }
    if (curr.first > prize.first || curr.second > prize.second) {
        cache[curr] = -1;
        return -1;
    }

    int token1 = solve(make_pair(curr.first + a.first, curr.second + a.second), a, b, prize, cache);
    int token2 = solve(make_pair(curr.first + b.first, curr.second + b.second), a, b, prize, cache);

    if (token1 == -1 && token2 == -1) {
        cache[curr] = -1;
        return cache[curr];
    }

    if (token1 == -1) {
        cache[curr] = token2 + 1;
    } else if (token2 == -1) {
        cache[curr] = token1 + 3;
    } else {
        cache[curr] = min(token1 + 3, token2 + 1);
    }
    return cache[curr];
}

pair<int, int> parsePoint(string line) {
    size_t xStart = line.find('X') + 2;  
    size_t yStart = line.find('Y') + 2;  
    
    size_t xEnd = line.find(',', xStart);
    size_t yEnd = line.length();
    
    int x = stoi(line.substr(xStart, xEnd - xStart));
    int y = stoi(line.substr(yStart, yEnd - yStart));
    return make_pair(x, y);
}

pair<int, int> parsePrize(string line) {
    size_t xStart = line.find('X') + 2;  
    size_t yStart = line.find('Y') + 2;  
    
    size_t xEnd = line.find(' ', xStart);
    if (xEnd == string::npos) xEnd = line.length();
    size_t yEnd = line.length();
    
    int x = stoi(line.substr(xStart, xEnd - xStart));
    int y = stoi(line.substr(yStart, yEnd - yStart));
    return make_pair(x, y);
}

int main() {
    auto start_time = chrono::high_resolution_clock::now();
    ifstream inputFile("input.txt");
    // ifstream inputFile("input-test.txt");
    string line1;
    string line2;
    string line3;
    string emptyline;
    int result = 0;

    while (getline(inputFile, line1) && getline(inputFile, line2) && getline(inputFile, line3)) {
        pair<int, int> a = parsePoint(line1);
        pair<int, int> b = parsePoint(line2);
        pair<int, int> prize = parsePrize(line3);
        getline(inputFile, emptyline);
        map<pair<int, int>, int> cache;
        int solved = solve(make_pair(0, 0), a, b, prize, cache);   
        if (solved != -1) {
            result += solved;
        }
    }

    cout << result << endl;

    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
    cout << "Time taken: " << duration.count() << " milliseconds" << endl;
    return 0;
}