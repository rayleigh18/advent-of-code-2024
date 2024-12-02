#include "sort.hpp"

void merge(std::vector<int>& vect, int left, int mid, int right) {
    std::vector<int> leftArr(vect.begin() + left, vect.begin() + mid + 1);
    std::vector<int> rightArr(vect.begin() + mid + 1, vect.begin() + right + 1);
    
    int i = 0;
    int j = 0;
    int k = left;
    
    while (i < leftArr.size() && j < rightArr.size()) {
        if (leftArr[i] <= rightArr[j]) {
            vect[k] = leftArr[i];
            i++;
        } else {
            vect[k] = rightArr[j];
            j++;
        }
        k++;
    }
    
    while (i < leftArr.size()) {
        vect[k] = leftArr[i];
        i++;
        k++;
    }
    
    while (j < rightArr.size()) {
        vect[k] = rightArr[j];
        j++;
        k++;
    }
}

void mergeSort(std::vector<int>& vect, int left, int right) {
    if (left >= right) {
        return;
    }

    int mid = (left + right) / 2;
    mergeSort(vect, left, mid);
    mergeSort(vect, mid + 1, right);
    merge(vect, left, mid, right);
}

void sortVector(std::vector<int>& vect) {
    mergeSort(vect, 0, vect.size() - 1);
} 