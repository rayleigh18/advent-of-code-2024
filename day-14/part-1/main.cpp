#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

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

int findQuadrant(pair<int, int> point, int height, int width) {
    int placeX = point.first / width;
    int placeY = point.second / height;


    int realX = point.first - (placeX * width);
    int realY = point.second - (placeY * height);
    if (realX < 0) {
        realX += width;
    }
    if (realY < 0) {
        realY += height;
    }

    if (realX < width / 2 && realY < height / 2) {
        return 0;
    }
    if (realX < width / 2 && realY > height / 2) {
        return 3;
    }
    if (realX > width / 2 && realY < height / 2) {
        return 1;
    }
    if (realX > width / 2 && realY > height / 2) {
        return 2;
    }
    return -1;
}

int main() {
    auto start_time = chrono::high_resolution_clock::now();
    ifstream inputFile("input.txt");
    // ifstream inputFile("input-test.txt");
    string line;
    long long result = 1;

    vector<int> numOfPointsInQuadrant(4, 0);
    int height = 103;
    int width = 101;
    while (getline(inputFile, line)) {
        auto start = parsePoint(line);
        auto velocity = parseVelocity(line);

        auto end = make_pair(start.first + velocity.first * 100, start.second + velocity.second * 100);
        int quadrant = findQuadrant(end, height, width);
        if (quadrant != -1) {
            numOfPointsInQuadrant[quadrant]++;
        }
    }


    for (int i = 0; i < 4; i++) {
        cout << numOfPointsInQuadrant[i] << " ";
        result *= numOfPointsInQuadrant[i];
    }

    cout << result << endl;

    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
    cout << "Time taken: " << duration.count() << " milliseconds" << endl;
    return 0;
}