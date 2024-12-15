#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int charToInt(char &val) { return val - '0'; }

int main() {
  auto start_time = chrono::high_resolution_clock::now();
  ifstream inputFile("input.txt");
  // ifstream inputFile("input-test.txt");
  string line;

  getline(inputFile, line);
  int lineSize = line.size();
  vector<int> vect;
  int vectorSize = 0;
  long result = 0;
  int left = 0;
  int right = lineSize - 1;
  int rightSize = right % 2 ? 0 : charToInt(line[right]);
  int emptyLeft = 0; // number of empty left

  auto addToVector = [&](int &pos) {
    int id = pos / 2;
    result += id * vectorSize;
    vectorSize++;
    // vect.push_back(id);
  };

  while (true) {
    if (left > right) {
      break;
    }
    if (left == right && rightSize != 0) {
      for (int i = 0; i < rightSize; i++) {
        addToVector(right);
      }
      break;
    }

    if (left % 2 == 0) {
      int leftVal = charToInt(line[left]);
      for (int i = 0; i < leftVal; i++) {
        addToVector(left);
      }
      left++;
      emptyLeft = charToInt(line[left]);
    } else {
      // fill empty
      if (emptyLeft == 0) {
        left++;
        continue;
      }
      if (rightSize == 0) {
        right--;
        rightSize = right % 2 == 0 ? charToInt(line[right]) : 0;
        continue;
      }
      int smaller = emptyLeft < rightSize ? emptyLeft : rightSize;
      for (int i = 0; i < smaller; i++) {
        addToVector(right);
        emptyLeft--;
        rightSize--;
      }
    }
  }
  cout << result << endl;
  for (int i = 0; i < vect.size(); i++) {
    cout << vect[i] << " ";
  }
  cout << endl;

  auto end_time = chrono::high_resolution_clock::now();
  auto duration =
      chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
  cout << "Time taken: " << duration.count() << " milliseconds" << endl;
  return 0;
}
