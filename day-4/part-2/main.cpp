#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

string searchWords[] = {"XMAS", "SAMX"};

string getString(char a, char b, char c) {
    return string(1, a) + string(1, b) + string(1, c);
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

    int colSize = area[0].size();
    int rowSize = area.size();

    string stringToSearch[] = {"MAS", "SAM"};

    for (int row = 1; row < rowSize - 1; row++) {
        for (int col = 1; col < colSize - 1; col++) {
            if (area[row][col] == 'A') {
                // positive diagonal
                string pos = getString(area[row-1][col-1], area[row][col], area[row+1][col+1]);
                string neg = getString(area[row-1][col+1], area[row][col], area[row+1][col-1]);
                if ((pos == stringToSearch[0] || pos == stringToSearch[1]) && (neg == stringToSearch[0] || neg == stringToSearch[1])) {
                    result++;
                }
            }
        }
    }
    

    cout << result << endl;
    return 0;
}

