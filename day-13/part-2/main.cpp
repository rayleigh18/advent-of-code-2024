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

bool isLinear(pair<int, int>& a, pair<int, int>& b) {
    return a.first * b.second == a.second * b.first;
}

long long solveLinear(pair<int, int>& a, pair<int, int>& b, pair<long long, long long>& p) {
    int maxbx = p.first * b.first;
    int naxbx = p.first * a.first;

    int mStart = 0;
    int mAxBxEnd = maxbx;

    if (maxbx * A_TOKEN > naxbx * B_TOKEN) {
        mStart = maxbx;
        mAxBxEnd = 0;
    }
    int realMStart = mStart / (a.first * b.first);
    int realMAxBxEnd = mAxBxEnd / (a.first * b.first);

    for (int mx = realMStart; mx <= realMAxBxEnd; mx++) {
        int nx = (p.first - mx * a.first) / b.first;
        if (p.first == mx * a.first + nx * b.first) {
            return mx * A_TOKEN + nx * B_TOKEN;
        }
    }
    return -1;
}


long long solve(pair<int, int>& a, pair<int, int>& b, pair<long long, long long>& p) {
    if (isLinear(a, b)) {
        return solveLinear(a, b, p);
    }
    int denom = (a.first * b.second - a.second * b.first);
    long long m = (p.first * b.second - p.second * b.first) / denom;
    long long n = (p.second * a.first - p.first * a.second) / denom;
    if (m < 0 || n < 0) {
        return -1;
    }
    // check x
    if (p.first != m * a.first + n * b.first) {
        return -1;
    }
    // check y
    if (p.second != m * a.second + n * b.second) {
        return -1;
    }

    return m * A_TOKEN + n * B_TOKEN;
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

pair<long long, long long> parsePrize(string line) {
    size_t xStart = line.find('X') + 2;  
    size_t yStart = line.find('Y') + 2;  
    
    size_t xEnd = line.find(' ', xStart);
    if (xEnd == string::npos) xEnd = line.length();
    size_t yEnd = line.length();
    long long x = stoi(line.substr(xStart, xEnd - xStart)) + 10000000000000;
    long long y = stoi(line.substr(yStart, yEnd - yStart)) + 10000000000000;
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
    long long result = 0;

    while (getline(inputFile, line1) && getline(inputFile, line2) && getline(inputFile, line3)) {
        auto a = parsePoint(line1);
        auto b = parsePoint(line2);
        auto prize = parsePrize(line3);
        getline(inputFile, emptyline);
        auto solved = solve(a, b, prize);   
        if (solved != -1) {
            result += solved;
        }
    }

    cout << "result " << result << endl;

    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
    cout << "Time taken: " << duration.count() << " milliseconds" << endl;
    return 0;
}