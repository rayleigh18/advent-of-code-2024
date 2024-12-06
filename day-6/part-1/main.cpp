#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <algorithm>

using namespace std;

void updateDirection(int& direction) {
    direction = (direction + 1) % 4;
}


int solve(vector<vector<char>> map, pair<int, int> start, unordered_map<int, vector<int>> rowObstacles, unordered_map<int, vector<int>> colObstacles) {
    int direction = 0; // 0: up, 1: right, 2: down, 3: left


    int rowSize = map.size();
    int colSize = map[0].size();
    auto current = start;

    vector<vector<bool>> visited(rowSize, vector<bool>(colSize, false));
    visited[start.first][start.second] = true;

    while (current.first != 0 && current.second != 0 && current.first != rowSize - 1 && current.second != colSize - 1) {
        pair<int, int> next;
        if (direction == 0) {
            next = make_pair(current.first - 1, current.second);
        }
        else if (direction == 1) {
            next = make_pair(current.first, current.second + 1);
        }
        else if (direction == 2) {
            next = make_pair(current.first + 1, current.second);
        }
        else {
            next = make_pair(current.first, current.second - 1);
        }

        if (map[next.first][next.second] == '#') {
            updateDirection(direction);
        }
        else {
            current = next;
            visited[current.first][current.second] = true;
        }
    }
    int result = 0;
    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < colSize; j++) {
            if (visited[i][j]) result++;
        }
    }
    return result;
}

int main() {
    ifstream inputFile("input.txt");
    // ifstream inputFile("input-test.txt");

    vector<vector<char>> map;
    string line;
    unordered_map<int, vector<int>> rowObstacles;
    unordered_map<int, vector<int>> colObstacles;
    pair<int, int> start;
    int i = 0;
    int direction = 0; // 0: up, 1: right, 2: down, 3: left
    while (getline(inputFile, line)) {
        vector<char> row;
        for (int j = 0; j < line.size(); j++) {
            row.push_back(line[j]);
            if (line[j] == '^') {
                start = make_pair(i, j);
            }
            else if (line[j] == '#') {
                rowObstacles[i].push_back(j);
                colObstacles[j].push_back(i);
            }
        }
        map.push_back(row);
        i++;
    }


    int result = solve(map, start, rowObstacles, colObstacles);
    cout << result << endl;



    return 0;
}