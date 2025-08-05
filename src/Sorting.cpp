#include "Sorting.h"
#include <iostream>
#include <algorithm>
#include <chrono>
#include <iomanip>

// Merge sort implementation
void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    std::vector<int> L(n1), R(n2);
    
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    
    int i = 0, j = 0, k = left;
    
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSortHelper(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortHelper(arr, left, mid);
        mergeSortHelper(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Heap sort implementation
void heapify(std::vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    if (left < n && arr[left] > arr[largest])
        largest = left;
    
    if (right < n && arr[right] > arr[largest])
        largest = right;
    
    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

// Quick sort implementation
int partition(std::vector<int>& arr, int low, int high) {
    // Median-of-three pivot selection
    int mid = low + (high - low) / 2;
    if (arr[mid] < arr[low]) std::swap(arr[low], arr[mid]);
    if (arr[high] < arr[low]) std::swap(arr[low], arr[high]);
    if (arr[high] < arr[mid]) std::swap(arr[mid], arr[high]);
    
    int pivot = arr[mid];
    std::swap(arr[mid], arr[high - 1]);
    
    int i = low;
    for (int j = low; j < high - 1; j++) {
        if (arr[j] <= pivot) {
            std::swap(arr[i], arr[j]);
            i++;
        }
    }
    std::swap(arr[i], arr[high - 1]);
    return i;
}

void quickSortHelper(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSortHelper(arr, low, pi - 1);
        quickSortHelper(arr, pi + 1, high);
    }
}

void Sorting::mergeSort(std::vector<int>& data) {
    std::cout << "[Sorting] Running Merge Sort\n";
    std::cout << "[Sorting] Time complexity: O(n log n)\n";
    std::cout << "[Sorting] Space complexity: O(n)\n";
    
    auto start = std::chrono::high_resolution_clock::now();
    mergeSortHelper(data, 0, data.size() - 1);
    auto end = std::chrono::high_resolution_clock::now();
    
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "[Sorting] Merge Sort completed in " << duration.count() << " microseconds\n";
}

void Sorting::heapSort(std::vector<int>& data) {
    std::cout << "[Sorting] Running Heap Sort\n";
    std::cout << "[Sorting] Time complexity: O(n log n)\n";
    std::cout << "[Sorting] Space complexity: O(1)\n";
    
    auto start = std::chrono::high_resolution_clock::now();
    
    int n = data.size();
    
    // Build heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(data, n, i);
    
    // Extract elements from heap one by one
    for (int i = n - 1; i > 0; i--) {
        std::swap(data[0], data[i]);
        heapify(data, i, 0);
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "[Sorting] Heap Sort completed in " << duration.count() << " microseconds\n";
}

void Sorting::quickSort(std::vector<int>& data) {
    std::cout << "[Sorting] Running Quick Sort (median-of-three)\n";
    std::cout << "[Sorting] Time complexity: O(n log n) average, O(n^2) worst case\n";
    std::cout << "[Sorting] Space complexity: O(log n) average\n";
    
    auto start = std::chrono::high_resolution_clock::now();
    quickSortHelper(data, 0, data.size() - 1);
    auto end = std::chrono::high_resolution_clock::now();
    
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "[Sorting] Quick Sort completed in " << duration.count() << " microseconds\n";
}

void Sorting::runAll(std::vector<int>& data) {
    std::cout << "[Sorting] Running all sorting algorithms on " << data.size() << " elements\n";
    std::cout << "Original array: ";
    for (int val : data) std::cout << val << " ";
    std::cout << "\n\n";
    
    // Create copies for each sort
    std::vector<int> data1 = data;
    std::vector<int> data2 = data;
    std::vector<int> data3 = data;
    
    mergeSort(data1);
    std::cout << "Merge Sort result: ";
    for (int val : data1) std::cout << val << " ";
    std::cout << "\n\n";
    
    heapSort(data2);
    std::cout << "Heap Sort result: ";
    for (int val : data2) std::cout << val << " ";
    std::cout << "\n\n";
    
    quickSort(data3);
    std::cout << "Quick Sort result: ";
    for (int val : data3) std::cout << val << " ";
    std::cout << "\n\n";
    
    std::cout << "[Sorting] All sorting algorithms completed successfully\n";
}
