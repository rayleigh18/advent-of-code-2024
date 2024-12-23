#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <queue>
#include <set>
using namespace std;

pair<int, int> findNext(pair<int, int> &current, int x, int y) {
    return make_pair(current.first + x, current.second + y);
}

vector<pair<int, int>> findNexts(pair<int, int> &current) {
    return {findNext(current, 0, 1), findNext(current, 0, -1), findNext(current, -1, 0), findNext(current, 1, 0)};
}

bool isInBound(vector<string>& map, pair<int, int> &current) {
    return current.first >= 0 && current.first < map.size() && current.second >= 0 && current.second < map[0].size();
}

bool isValid(vector<string> map, pair<int, int> &current, pair<int, int> &next) {
    if (next.first < 0 || next.first >= map.size() || next.second < 0 || next.second >= map[0].size()) {
        return false;
    }
    if (map[current.first][current.second] != map[next.first][next.second]) {
        return false;
    }
    return true;
}

void bfs(vector<string> map, vector<vector<bool>> &visited, pair<int, int> &start, set<pair<int, int>>& area) {
    if (visited[start.first][start.second]) {
        return;
    }
    visited[start.first][start.second] = true;
    area.insert(start);
    auto nexts = findNexts(start);
    for (auto next : nexts) {
        if (isValid(map, start, next)) {
            bfs(map, visited, next, area);
        }
    }
}

int findPerimeter(set<pair<int, int>> &area, pair<int, int> &current) {
    auto nexts = findNexts(current);
    bool isBoundary = false;
    int perimeterCount = 0;
    for (auto next : nexts) {
        if (area.find(next) == area.end()) {
            perimeterCount++;
        }
    }
    return perimeterCount;
}

int solve(vector<string> map) {
    int result = 0;
    vector<vector<bool>> visited(map.size(), vector<bool>(map[0].size(), false));
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            if (visited[i][j]) {
                continue;
            }
            auto start = make_pair(i, j);
            set<pair<int, int>> area;
            bfs(map, visited, start, area);
            auto perimeter = 0;
            for (auto next : area) {
                perimeter += findPerimeter(area, next);
            }
            int theArea = area.size();
            result += perimeter * theArea;

        }
    }
    return result;
}

int main() {
    auto start_time = chrono::high_resolution_clock::now();
    ifstream inputFile("input.txt");
    // ifstream inputFile("input-test.txt");
    string line;
    vector<string> map;

    while (getline(inputFile, line)) {
        map.push_back(line);
    }

    cout << solve(map) << endl;

    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
    cout << "Time taken: " << duration.count() << " milliseconds" << endl;
    return 0;
}