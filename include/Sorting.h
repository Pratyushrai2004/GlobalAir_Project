#pragma once
#include <vector>

class Sorting {
public:
    // Merge sort
    void mergeSort(std::vector<int>& data);
    // Heap sort
    void heapSort(std::vector<int>& data);
    // Quick sort (median-of-three)
    void quickSort(std::vector<int>& data);
    // Run all sorts and display timings
    void runAll(std::vector<int>& data);
};
