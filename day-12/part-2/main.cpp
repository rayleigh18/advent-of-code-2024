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

bool isInBound(vector<string>& map, pair<int, int> &current) {
    return current.first >= 0 && current.first < map.size() && current.second >= 0 && current.second < map[0].size();
}

vector<pair<int, int>> findNexts(vector<string>& map, pair<int, int> &current) {
    auto directions = {make_pair(0, 1), make_pair(0, -1), make_pair(-1, 0), make_pair(1, 0)};
    vector<pair<int, int>> result;
    for (auto direction : directions) {
        auto next = findNext(current, direction.first, direction.second);
        if (isInBound(map, next)) {
            result.push_back(next);
        }
    }
    return result;
}

vector<pair<int, int>> findNextsWithInvalid(vector<string>& map, pair<int, int> &current) {
    auto directions = {make_pair(0, 1), make_pair(0, -1), make_pair(-1, 0), make_pair(1, 0)};
    vector<pair<int, int>> result;
    for (auto direction : directions) {
        auto next = findNext(current, direction.first, direction.second);
        result.push_back(next);
    }
    return result;
}

bool isValid(vector<string> map, pair<int, int> &current, pair<int, int> &next) {
    if (map[current.first][current.second] != map[next.first][next.second]) {
        return false;
    }
    return true;
}

void bfs(vector<string> &map, vector<vector<bool>> &visited, pair<int, int> &start, set<pair<int, int>>& area) {
    if (visited[start.first][start.second]) {
        return;
    }
    visited[start.first][start.second] = true;
    area.insert(start);
    auto nexts = findNexts(map, start);
    for (auto next : nexts) {
        if (isValid(map, start, next)) {
            bfs(map, visited, next, area);
        }
    }
}

int findSides(vector<string>& map, set<pair<int, int>> &area) {
    int result = 0;
    set<pair<pair<int,int>, pair<int,int>>> visited;
    for (auto point : area) {
        auto nexts = findNextsWithInvalid(map, point);
        for (auto next : nexts) {
            if (area.find(next) != area.end()) {
                continue;
            }
            auto direction = make_pair(next.first - point.first, next.second - point.second);
            auto directionTranspose = make_pair(direction.second, direction.first);
            auto directionTransposeOpposite = make_pair(-directionTranspose.first, -directionTranspose.second);
            if (visited.find(make_pair(point, direction)) != visited.end()) {
                continue;
            }
            visited.insert(make_pair(point, direction));
            result++;

            auto nextTranspose = make_pair(point.first + directionTranspose.first, point.second + directionTranspose.second);
            auto nextTransposePointLimit = make_pair(nextTranspose.first + direction.first, nextTranspose.second + direction.second);
            while (isInBound(map, nextTranspose) && area.find(nextTranspose) != area.end() && area.find(nextTransposePointLimit) == area.end()) {
                visited.insert(make_pair(nextTranspose, direction));
                nextTranspose = make_pair(nextTranspose.first + directionTranspose.first, nextTranspose.second + directionTranspose.second);
                nextTransposePointLimit = make_pair(nextTranspose.first + direction.first, nextTranspose.second + direction.second);
            }

            auto nextTransposeOpposite = make_pair(point.first + directionTransposeOpposite.first, point.second + directionTransposeOpposite.second);
            auto nextTransposeOppositePointLimit = make_pair(nextTransposeOpposite.first + direction.first, nextTransposeOpposite.second + direction.second);
            while (isInBound(map, nextTransposeOpposite) && area.find(nextTransposeOpposite) != area.end() && area.find(nextTransposeOppositePointLimit) == area.end()) {
                visited.insert(make_pair(nextTransposeOpposite, direction));
                nextTransposeOpposite = make_pair(nextTransposeOpposite.first + directionTransposeOpposite.first, nextTransposeOpposite.second + directionTransposeOpposite.second);
                nextTransposeOppositePointLimit = make_pair(nextTransposeOpposite.first + direction.first, nextTransposeOpposite.second + direction.second);
            }
        }
    }

    return result;
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
            auto perimeter = findSides(map, area);
            int theArea = area.size();
            result += perimeter * theArea;
        }
    }
    return result;
}

int main() {
    auto start_time = chrono::high_resolution_clock::now();
    // ifstream inputFile("input-other.txt");
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