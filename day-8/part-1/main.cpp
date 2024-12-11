#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <unordered_map>

using namespace std;

void pushToVisited(const vector<string>& grid, vector<pair<int, int>>& visited, int x, int y) {
    if (x < 0 || x >= grid.size() || y < 0 || y >= grid[0].size()) {
        return;
    }
    if (find(visited.begin(), visited.end(), make_pair(x, y)) != visited.end()) {
        return;
    }
    visited.push_back(make_pair(x, y));
}

int solve(const vector<string>& grid) {
    unordered_map<char, vector<pair<int, int>>> positions;

    vector<pair<int, int>> visited = {};

    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] != '.') {
                positions[grid[i][j]].push_back(make_pair(i, j));
            }
        }
    }

    for (auto& [key, value] : positions) {
        int size = value.size();
        for (int i = 0; i < size; i++) {
            for (int j = i + 1; j < size; j++) {
                int x1 = value[i].first;
                int y1 = value[i].second;
                int x2 = value[j].first;
                int y2 = value[j].second;
                if (value[i].first > value[j].first) {
                    x1 = value[j].first;
                    y1 = value[j].second;
                    x2 = value[i].first;
                    y2 = value[i].second;
                }

                int x1New = x1 - (x2 - x1);
                int y1New = y1 - (y2 - y1);
                pushToVisited(grid, visited, x1New, y1New);

                int x2New = x2 + (x2 - x1);
                int y2New = y2 + (y2 - y1);
                pushToVisited(grid, visited, x2New, y2New);

            }
        }
    }

    return visited.size();
}

int main() {
    auto start_time = chrono::high_resolution_clock::now();
    ifstream inputFile("input.txt");
    // ifstream inputFile("input-test.txt");
    string line;

    vector<string> grid;
    while (getline(inputFile, line)) {
        grid.push_back(line);
    }

    cout << solve(grid) << endl;

    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
    cout << "Time taken: " << duration.count() << " milliseconds" << endl;
    return 0;
}