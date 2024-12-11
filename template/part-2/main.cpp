#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

int main() {

    auto start_time = chrono::high_resolution_clock::now();
    // ifstream inputFile("input.txt");
    ifstream inputFile("input-test.txt");
    string line;
    int result = 0;

    while (getline(inputFile, line)) {
    }

    cout << result << endl;

    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
    cout << "Time taken: " << duration.count() << " milliseconds" << endl;
    return 0;
}