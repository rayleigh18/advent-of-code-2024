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

pair<int, int> getNext(pair<int, int> current, int direction) {
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
    return next;
}

bool isMapHaveLoop(pair<int, int> start, vector<vector<char>> map, vector<vector<vector<int>>> directionMap, int direction) {
    auto current = start;
    int rowSize = map.size();
    int colSize = map[0].size();
    
    while (true) {
        auto next = getNext(current, direction);
        if (next.first < 0 || next.first >= rowSize || next.second < 0 || next.second >= colSize) {
            return false;
        }

        if (map[next.first][next.second] == '#') {
            updateDirection(direction);
        }
        else {
            if (directionMap[next.first][next.second].size() > 0) {
                for (int dir : directionMap[next.first][next.second]) {
                    if (dir == direction) return true;
                }
            }
            current = next;
            directionMap[current.first][current.second].push_back(direction);
        }
    }
    return false;
}

int solve(vector<vector<char>> map, pair<int, int> start, unordered_map<int, vector<int>> rowObstacles, unordered_map<int, vector<int>> colObstacles) {
    int direction = 0; // 0: up, 1: right, 2: down, 3: left


    int rowSize = map.size();
    int colSize = map[0].size();
    auto current = start;

    int result = 0;

    vector<vector<vector<int>>> directionMap(rowSize, vector<vector<int>>(colSize, vector<int>(0)));

    vector<pair<int, int>> placedObstacles;

    while (true) {
        auto next = getNext(current, direction);
        if (next.first < 0 || next.first >= rowSize || next.second < 0 || next.second >= colSize) {
            break;
        }
        
        if (map[next.first][next.second] == '.') {
            bool isPlaceObstacle = false;
            for (auto obstacle : placedObstacles) {
                if (obstacle.first == next.first && obstacle.second == next.second) {
                    isPlaceObstacle = true;
                    break;
                }
            }
            if (!isPlaceObstacle) {
                auto tempMap = map;
                tempMap[next.first][next.second] = '#';
                
                if (isMapHaveLoop(current, tempMap, directionMap, direction)) {
                    // cout << next.first << " " << next.second << endl;
                    // for (auto row : tempMap) {
                    //     for (auto cell : row) {
                    //         cout << cell;
                    //     }
                    //     cout << endl;
                    // }
                    result++;
                }
                placedObstacles.push_back(next);
            }
        }
        if (map[next.first][next.second] == '#') {
            updateDirection(direction);
        }
        else {
            current = next;
            directionMap[current.first][current.second].push_back(direction);
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