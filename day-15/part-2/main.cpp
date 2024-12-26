#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <set>

using namespace std;

pair<int, int> translateDirection(char& direction) {
    switch (direction) {
        case 'v':
            return make_pair(1, 0);
        case '>':
            return make_pair(0, 1);
        case '^':
            return make_pair(-1, 0);
        case '<':
            return make_pair(0, -1);
    }
    return make_pair(0, 0);
}

bool moveObstacle(set<pair<int, int>>& movableObstacles, pair<int, int>& position, pair<int, int>& direction, vector<string>& warehouse) {
    if (movableObstacles.find(position) != movableObstacles.end()) {
        return true;
    }
    pair<int, int> pairObstacle;
    if (warehouse[position.first][position.second] == '[') {
        pairObstacle = make_pair(position.first, position.second + 1);
    } else if (warehouse[position.first][position.second] == ']') {
        pairObstacle = make_pair(position.first, position.second - 1);
    }
    movableObstacles.insert(position);
    movableObstacles.insert(pairObstacle);

    for (auto& obstacle : {position, pairObstacle}) {
        auto newPos = make_pair(obstacle.first + direction.first, obstacle.second + direction.second);
        if (warehouse[newPos.first][newPos.second] == '#') {
            return false;
        }
        if (warehouse[newPos.first][newPos.second] == '[' || warehouse[newPos.first][newPos.second] == ']') {
            auto canMoveObstacle = moveObstacle(movableObstacles, newPos, direction, warehouse);
            if (!canMoveObstacle) {
                return false;
            }
        }
    }

    return true;
}

void move(pair<int, int>& position, pair<int, int>& direction, vector<string>& warehouse) {
    auto newPos = make_pair(position.first + direction.first, position.second + direction.second);
    if (warehouse[newPos.first][newPos.second] == '.') {
        position = newPos;
        return;
    }
    if (warehouse[newPos.first][newPos.second] == '#') {
        return;
    }
    // case '[]'
    set<pair<int, int>> movableObstacles;
    bool canMove = moveObstacle(movableObstacles, newPos, direction, warehouse);
    if (canMove) {
        // move movable obstacles
        // save warehouse char
        vector<pair<pair<int, int>, char>> warehouseChars;
        for (auto& obstacle : movableObstacles) {
            warehouseChars.push_back(make_pair(obstacle, warehouse[obstacle.first][obstacle.second]));
        }
        // move movable obstacles
        for (auto& obstacle : movableObstacles) {
            warehouse[obstacle.first][obstacle.second] = '.';
            warehouse[obstacle.first + direction.first][obstacle.second + direction.second] = '.';
        }

        // restore warehouse char
        for (auto& warehouseChar : warehouseChars) {
            warehouse[warehouseChar.first.first + direction.first][warehouseChar.first.second + direction.second] = warehouseChar.second;
        }

        position = newPos;
    }
}

void printWarehouse(vector<string>& warehouse, pair<int, int>& position) {
    for (int i = 0; i < warehouse.size(); i++) {
        for (int j = 0; j < warehouse[i].size(); j++) {
            if (i == position.first && j == position.second) {
                cout << '@';
            } else {
                cout << warehouse[i][j];
            }
        }
        cout << endl;
    }
}

string transformLine(string& line) {
    string result;
    for (char c : line) {
        switch (c) {
            case '#':
                result += "##";
                break;
            case '.':
                result += "..";
                break;
            case 'O':
                result += "[]";
                break;
            case '@':
                result += "@.";
                break;
            default:
                // wont happened
                result += c * 2;
        }
    }
    return result;
}

int main() {
    auto start_time = chrono::high_resolution_clock::now();
    ifstream inputFile("input.txt");
    // ifstream inputFile("input-test.txt");
    string line;
    int result = 0;
    vector<string> warehouse;

    while (getline(inputFile, line)) {
        if (line.empty()) {
            break;
        }
        warehouse.push_back(transformLine(line));
    }

    pair<int, int> start;
    for (int i = 0; i < warehouse.size(); i++) {
        for (int j = 0; j < warehouse[i].size(); j++) {
            if (warehouse[i][j] == '@') {
                start = make_pair(i, j);
                warehouse[i][j] = '.';
                break;
            }
        }
    }


    string directions;
    while (getline(inputFile, directions)) {
        for (char dirChar : directions) {
            auto dir = translateDirection(dirChar);
            move(start, dir, warehouse);
        }
    }

    for (int i = 0; i < warehouse.size(); i++) {
        for (int j = 0; j < warehouse[i].size(); j++) {
            if (warehouse[i][j] == '[') {
                result += (i * 100 + j);
            }
        }
    }

    cout << result << endl;

    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
    cout << "Time taken: " << duration.count() << " milliseconds" << endl;
    return 0;
}