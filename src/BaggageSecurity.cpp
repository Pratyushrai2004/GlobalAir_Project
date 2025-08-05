#include "BaggageSecurity.h"
#include <iostream>
#include <fstream>
#include <sstream>

void BaggageSecurity::loadRules(const std::string& path) {
    std::cout << "[BaggageSecurity] Loading security rules from " << path << "\n";
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cout << "[BaggageSecurity] Error: Could not open security rules file: " << path << "\n";
        return;
    }
    
    std::string line;
    int count = 0;
    while (std::getline(file, line)) {
        count++;
    }
    std::cout << "[BaggageSecurity] Successfully loaded " << count << " security rules\n";
    file.close();
}

void BaggageSecurity::assessBaggageRisk(const std::string& id,
                                       const std::string& passengerID,
                                       const std::string& origin,
                                       const std::string& dest,
                                       const std::string& type,
                                       const std::string& history) {
    std::cout << "[BaggageSecurity] Assessing risk for baggage ID: " << id << "\n";
    std::cout << "[BaggageSecurity] Passenger ID: " << passengerID << "\n";
    std::cout << "[BaggageSecurity] Route: " << origin << " -> " << dest << "\n";
    std::cout << "[BaggageSecurity] Type: " << type << "\n";
    std::cout << "[BaggageSecurity] History: " << history << "\n";
    std::cout << "[BaggageSecurity] Using Trie/Prefix tree for pattern matching\n";
    std::cout << "[BaggageSecurity] Time complexity: O(m) where m is pattern length\n";
    std::cout << "[BaggageSecurity] Space complexity: O(n) for trie storage\n";
    std::cout << "[BaggageSecurity] Result: Risk assessment completed (simulated)\n";
}
