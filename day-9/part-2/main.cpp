#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

struct File {
    int id;
    int size;
    int position;
};

int main() {
    auto start_time = chrono::high_resolution_clock::now();
    // ifstream inputFile("input.txt");
    ifstream inputFile("input-test.txt");

    vector<int> nums;
    vector<File> files;
    vector<bool> disk;
    int currentPosition = 0;
    int fileId = 0;

    // Read input
    char temp;
    while (inputFile >> temp) {
        int val = temp - '0';
        nums.push_back(val);
    }

    for (int i = 0; i < nums.size(); i += 2) {
        File file;
        file.id = fileId++;
        file.size = nums[i];
        file.position = currentPosition;
        files.push_back(file);
        
        disk.resize(currentPosition + nums[i] + nums[i+1], false);
        for (int j = 0; j < nums[i]; j++) {
            disk[currentPosition + j] = true;
        }
        currentPosition += nums[i] + nums[i+1];
    }

    for (int id = files.size() - 1; id >= 0; id--) {
        File& currentFile = files[id];
        int bestPosition = currentFile.position;

        // Find leftmost position where file can fit
        for (int pos = 0; pos < currentFile.position; pos++) {
            bool canFit = true;
            for (int j = 0; j < currentFile.size; j++) {
                if (pos + j >= disk.size() || disk[pos + j]) {
                    canFit = false;
                    break;
                }
            }
            if (canFit) {
                bestPosition = pos;
                break;
            }
        }

        if (bestPosition != currentFile.position) {
            for (int j = 0; j < currentFile.size; j++) {
                disk[currentFile.position + j] = false;
            }
            for (int j = 0; j < currentFile.size; j++) {
                disk[bestPosition + j] = true;
            }
            currentFile.position = bestPosition;
        }
    }

    // Calculate checksum
    long long checksum = 0;
    for (const File& file : files) {
        for (int i = 0; i < file.size; i++) {
            checksum += (long long)(file.position + i) * file.id;
        }
    }

    cout << "Checksum: " << checksum << endl;

    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
    cout << "Time taken: " << duration.count() << " milliseconds" << endl;
    return 0;
}
