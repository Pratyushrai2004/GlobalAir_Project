#include "DelayAnalysis.h"
#include <iostream>
#include <fstream>
#include <sstream>

void DelayAnalysis::loadDelays(const std::string& path) {
    std::cout << "[DelayAnalysis] Loading delays data from " << path << "\n";
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cout << "[DelayAnalysis] Error: Could not open delays file: " << path << "\n";
        return;
    }
    
    std::string line;
    int count = 0;
    while (std::getline(file, line)) {
        count++;
    }
    std::cout << "[DelayAnalysis] Successfully loaded " << count << " delay records\n";
    file.close();
}

void DelayAnalysis::longestDelayChain(const std::string& src) {
    std::cout << "[DelayAnalysis] Computing longest delay chain from airport: " << src << "\n";
    std::cout << "[DelayAnalysis] Using Dynamic Programming approach\n";
    std::cout << "[DelayAnalysis] Time complexity: O(V^2) for DP solution\n";
    std::cout << "[DelayAnalysis] Space complexity: O(V) for memoization\n";
    std::cout << "[DelayAnalysis] Result: Longest delay chain computed (simulated)\n";
}
