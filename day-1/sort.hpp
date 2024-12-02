#ifndef SORT_HPP
#define SORT_HPP

#include <vector>

void sortVector(std::vector<int>& vect);
void mergeSort(std::vector<int>& vect, int left, int right);
void merge(std::vector<int>& vect, int left, int mid, int right);

#endif 