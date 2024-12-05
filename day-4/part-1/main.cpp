#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

string searchWords[] = {"XMAS", "SAMX"};


bool checkString(char a, char b, char c, char d) {
    if ((a != 'X' && a != 'S') || (d != 'S' && d != 'X')) {
        return false;
    }
    string s = string(1, a) + string(1, b) + string(1, c) + string(1, d);
    return s == "XMAS" || s == "SAMX";
}

void printVector(vector<char> v) {
    for (char c : v) {
        cout << c;
    }
    cout << endl;
}


int main() {    
    ifstream inputFile("input.txt");
    // ifstream inputFile("input-test.txt");

    vector<vector<char>> area = {};
    string line;

    while (getline(inputFile, line)) {
        vector<char> row = {};
        for (char c : line) {
            row.push_back(c);
        }
        area.push_back(row);
    }

    int result = 0;
    const int PATTERN_LENGTH = 4;
    
    int colSize = area[0].size();
    int rowSize = area.size();

    for (int row = 0; row < rowSize; row++) {
        for (int col = 0; col < colSize; col++) {
            if (col <= colSize - PATTERN_LENGTH) {
                if (checkString(
                    area[row][col],
                    area[row][col+1],
                    area[row][col+2],
                    area[row][col+3]
                )) {
                    result++;
                }
            }
            
            if (row <= rowSize - PATTERN_LENGTH) {
                if (checkString(
                    area[row][col],
                    area[row+1][col],
                    area[row+2][col],
                    area[row+3][col]
                )) {
                    result++;
                }
            }
            
            if (row <= rowSize - PATTERN_LENGTH && col <= colSize - PATTERN_LENGTH) {
                if (checkString(
                    area[row][col],
                    area[row+1][col+1],
                    area[row+2][col+2],
                    area[row+3][col+3]
                )) {
                    result++;
                }
            }
            
            if (row >= PATTERN_LENGTH - 1 && col <= colSize - PATTERN_LENGTH) {
                if (checkString(
                    area[row][col],
                    area[row-1][col+1],
                    area[row-2][col+2],
                    area[row-3][col+3]
                )) {
                    result++;
                }
            }
        }
    }

    cout << result << endl;
    return 0;
}

