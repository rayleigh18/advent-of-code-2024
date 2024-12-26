#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

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

bool moveObstacle(pair<int, int>& position, pair<int, int>& direction, vector<string>& warehouse) {
    auto newPos = make_pair(position.first + direction.first, position.second + direction.second);
    if (warehouse[newPos.first][newPos.second] == '.') {
        warehouse[newPos.first][newPos.second] = 'O';
        warehouse[position.first][position.second] = '.';
        return true;
    }
    if (warehouse[newPos.first][newPos.second] == 'O') {
        auto result = moveObstacle(newPos, direction, warehouse);
        if (result) {
            warehouse[position.first][position.second] = '.';
            warehouse[newPos.first][newPos.second] = 'O';
            return true;
        }
    }
    return false;
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
    // case '0'
    bool canMove = moveObstacle(newPos, direction, warehouse);
    if (canMove) {
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
        warehouse.push_back(line);
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
    // printWarehouse(warehouse, start);

    for (int i = 0; i < warehouse.size(); i++) {
        for (int j = 0; j < warehouse[i].size(); j++) {
            if (warehouse[i][j] == 'O') {
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