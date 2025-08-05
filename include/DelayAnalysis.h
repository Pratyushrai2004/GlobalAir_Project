#pragma once
#include <string>

class DelayAnalysis {
public:
    // Load delays data (IATA, delayMinutes)
    void loadDelays(const std::string& path);
    // Compute longest delay chain starting from an airport
    void longestDelayChain(const std::string& src);
};
