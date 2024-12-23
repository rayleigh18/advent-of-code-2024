#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <set>

using namespace std;
pair<int, int> parsePoint(string s) {
    string pos = s.substr(0, s.find(' '));
    pos = pos.substr(2);
    int x = stoi(pos.substr(0, pos.find(',')));
    int y = stoi(pos.substr(pos.find(',') + 1));
    return make_pair(x, y);
}

pair<int, int> parseVelocity(string s) {
    string vel = s.substr(s.find("v=") + 2);
    int x = stoi(vel.substr(0, vel.find(',')));
    int y = stoi(vel.substr(vel.find(',') + 1));
    return make_pair(x, y);
}

int main() {
    // this is so fucking stupid 
    auto start_time = chrono::high_resolution_clock::now();
    ifstream inputFile("input.txt");
    // ifstream inputFile("input-test.txt");
    string line;
    long long result = 1;

    vector<int> numOfPointsInQuadrant(4, 0);
    int height = 103;
    int width = 101;
    vector<pair<pair<int, int>, pair<int, int>>> pointsWithPositionAndVelocity;
    while (getline(inputFile, line)) {
        auto start = parsePoint(line);
        auto velocity = parseVelocity(line);
        pointsWithPositionAndVelocity.push_back(make_pair(start, velocity));
    }

    bool isFound = false;
    int timeFound = 1;
    double avgPairwiseDistance = 1000000000000000000;
    set<pair<int, int>> pointsToCheck;
    int time = 1;

    while (!isFound && time < 10000) {
        if (time % 1000 == 0) {
            cout << time << endl;
        }
        for (auto &point : pointsWithPositionAndVelocity) {
            point.first.first += point.second.first;
            point.first.second += point.second.second;
            if (point.first.first < 0) {
                int widthToAdd = (0 - point.first.first) / width;
                point.first.first += (widthToAdd + 1) * width;
            }
            if (point.first.first >= width) {
                int widthToSubtract = point.first.first / width;
                point.first.first -= widthToSubtract * width;
            }

            if (point.first.second < 0) {
                int heightToAdd = (0 - point.first.second) / height;
                point.first.second += (heightToAdd + 1) * height;
            }
            if (point.first.second >= height) {
                int heightToSubtract = point.first.second / height;
                point.first.second -= heightToSubtract * height;
            }
        }
        double tempAvgPairwiseDistance = 0;
        for (int i = 0; i < pointsWithPositionAndVelocity.size(); i++) {
            for (int j = i + 1; j < pointsWithPositionAndVelocity.size(); j++) {
                tempAvgPairwiseDistance += abs(pointsWithPositionAndVelocity[i].first.first - pointsWithPositionAndVelocity[j].first.first) + abs(pointsWithPositionAndVelocity[i].first.second - pointsWithPositionAndVelocity[j].first.second);
            }
        }
        double temp = tempAvgPairwiseDistance / (pointsWithPositionAndVelocity.size() );
        if (temp < avgPairwiseDistance) {
            for (auto &point : pointsWithPositionAndVelocity) {
                pointsToCheck.insert(point.first);
            }
            avgPairwiseDistance = temp;
            timeFound = time;
        }
        time++;
    }

    cout << timeFound << " " << avgPairwiseDistance << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (pointsToCheck.find(make_pair(j, i)) != pointsToCheck.end()) {
                cout << "#";
            } else {
                cout << ".";
            }
        }
        cout << endl;
    }


    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
    cout << "Time taken: " << duration.count() << " milliseconds" << endl;
    return 0;
}