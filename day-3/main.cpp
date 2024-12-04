#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

bool isNumber(char c) {
    return c >= '0' && c <= '9';
}

void resetState(int &state, string &firstNumberString, string &secondNumberString) {
    state = 0;
    firstNumberString = "";
    secondNumberString = "";
}

int main() {
    // ifstream inputFile("input-test.txt");
    ifstream inputFile("input.txt");

    int state = 0;
    string firstNumberString = "";
    string secondNumberString = "";
    string line;

    int result = 0;

    string mult = "mul";

    while (getline(inputFile, line)) {
        for (int i = 0; i < line.size(); i++) {
            if (state == 0) {
                if (line.substr(i, mult.size()) == mult) {
                    state = 1;
                    i += mult.size() - 1;
                    continue;
                }
            }
            else if (state == 1) {
                if (line[i] == '(') {
                    state = 2;
                    continue;
                }
                else {
                    resetState(state, firstNumberString, secondNumberString);
                    continue;
                }
            }
            else if (state == 2) {
                if (line[i] == ',') {
                    if (firstNumberString == "") {
                        resetState(state, firstNumberString, secondNumberString);
                        continue;
                    }
                    state = 3;
                    continue;
                }
                else if (!isNumber(line[i])) {
                    resetState(state, firstNumberString, secondNumberString);
                    continue;
                }
                firstNumberString += line[i];
            }
            else if (state == 3) {
                if (line[i] == ')') {
                    result += stoi(firstNumberString) * stoi(secondNumberString);
                    resetState(state, firstNumberString, secondNumberString);
                    continue;
                }
                else if (!isNumber(line[i])) {
                    resetState(state, firstNumberString, secondNumberString);
                    continue;
                }
                secondNumberString += line[i];
            }
        }

        resetState(state, firstNumberString, secondNumberString);
    }

    cout << result << endl;

    inputFile.close();
    return 0;
}

