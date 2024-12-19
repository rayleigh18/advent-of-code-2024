#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <unordered_set>
using namespace std;

namespace std {
    template <>
    struct hash<pair<int, int>> {
        size_t operator()(const pair<int, int>& p) const {
            // Combine the hashes of the two integers
            return hash<int>()(p.first) ^ (hash<int>()(p.second) << 1);
        }
    };
}

pair<int, int> getNextPosition(pair<int, int> current, int x, int y) {
    return make_pair(current.first + x, current.second + y);
}

bool isInBounds(pair<int,int>& start, vector<vector<int>>& map, pair<int, int>& position) {
    return position.first >= 0 
    && position.first < map.size() 
    && position.second >= 0 
    && position.second < map[0].size() 
    && map[position.first][position.second] == map[start.first][start.second] + 1;
}

unordered_set<pair<int, int>> getFinalDestinations(
    vector<vector<int>>& map, vector<vector<bool>>& visited, 
    vector<vector<unordered_set<pair<int, int>>>>& unqiue_final_destinations, 
    pair<int, int> start) {
    if (visited[start.first][start.second]) {
        return unqiue_final_destinations[start.first][start.second];
    }
    visited[start.first][start.second] = true;
    if (map[start.first][start.second] == 9) {
        unqiue_final_destinations[start.first][start.second].insert(start);
        return unqiue_final_destinations[start.first][start.second];
    }
    vector<pair<int, int>> next_positions;
    next_positions.push_back(getNextPosition(start, 0, -1));
    next_positions.push_back(getNextPosition(start, 0, 1));
    next_positions.push_back(getNextPosition(start, -1, 0));
    next_positions.push_back(getNextPosition(start, 1, 0));

    for (pair<int, int> next_position : next_positions) {
        if (isInBounds(start, map, next_position)) {
            auto result = getFinalDestinations(map, visited, unqiue_final_destinations, next_position);
            for (pair<int, int> final_destination : result) {
                unqiue_final_destinations[start.first][start.second].insert(final_destination);
            }
        }
    }

    return unqiue_final_destinations[start.first][start.second];
}

int solve(vector<vector<int>> map) {
    int result = 0;
    vector<vector<bool>> visited(map.size(), vector<bool>(map[0].size(), false));
    
    vector<vector<unordered_set<pair<int, int>>>> unqiue_final_destinations(
        map.size(),
        vector<unordered_set<pair<int, int>>>(map[0].size())
    );

    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            if (map[i][j] == 0) {
                auto uniqueFinalDestinations = getFinalDestinations(map, visited, unqiue_final_destinations, make_pair(i, j));
                result += uniqueFinalDestinations.size();
            }
        }
    }

    return result;
}

int main() {
    auto start_time = chrono::high_resolution_clock::now();
    ifstream inputFile("input.txt");
    // ifstream inputFile("input-test.txt");

    vector<vector<int>> map;
    string line;
    int result = 0;

    while (getline(inputFile, line)) {
        vector<int> row;
        for (char c : line) {
            row.push_back(c - '0');
        }
        map.push_back(row);
    }

    

    cout << solve(map) << endl;

    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
    cout << "Time taken: " << duration.count() << " milliseconds" << endl;
    return 0;
}