#include "binary_search.hpp"
#include <iostream>


int binaryLeftmostSearch(int value, std::vector<int> vect) {
    int left = 0;
    int right = vect.size() - 1;
    int result = -1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (vect[mid] == value) {
            result = mid;
            right = mid - 1;
        }
        else if (vect[mid] < value) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    return result;
}

int binaryRightmostSearch(int value, std::vector<int> vect) {
    int left = 0;
    int right = vect.size() - 1;
    int result = -1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (vect[mid] == value) {
            result = mid;
            left = mid + 1;
        }
        else if (vect[mid] < value) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    return result;
}

int findSimilarityScore(std::vector<int> vect1, std::vector<int> vect2) {
    int result = 0;
    for (int i = 0; i < vect1.size(); i++) {
        int leftMost = binaryLeftmostSearch(vect1[i], vect2);
        int rightMost = binaryRightmostSearch(vect1[i], vect2);

        if (leftMost == -1) {
            continue;
        }
        result += (rightMost - leftMost + 1) * vect1[i];
    }
    return result;
} 