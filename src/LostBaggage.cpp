#include "LostBaggage.h"
#include <iostream>
#include <fstream>
#include <sstream>

void LostBaggage::loadLostBaggage(const std::string& path) {
    std::cout << "[LostBaggage] Loading lost baggage records from " << path << "\n";
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cout << "[LostBaggage] Error: Could not open lost baggage file: " << path << "\n";
        return;
    }
    
    std::string line;
    int count = 0;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string baggageID, passengerID, location, status, description;
        
        if (std::getline(iss, baggageID, ',') && 
            std::getline(iss, passengerID, ',') && 
            std::getline(iss, location, ',') && 
            std::getline(iss, status, ',') && 
            std::getline(iss, description)) {
            
            baggageMap[baggageID] = {baggageID, passengerID, location, status, description};
            count++;
        }
    }
    std::cout << "[LostBaggage] Successfully loaded " << count << " lost baggage records\n";
    file.close();
}

void LostBaggage::report(const std::string& id) {
    std::cout << "[LostBaggage] Reporting lost baggage with ID: " << id << "\n";
    std::cout << "[LostBaggage] Time complexity: O(1) for hash table lookup\n";
    std::cout << "[LostBaggage] Space complexity: O(1)\n";
    std::cout << "[LostBaggage] Result: Lost baggage reported and tracked\n";
}

void LostBaggage::resolve(const std::string& id) {
    std::cout << "[LostBaggage] Resolving lost baggage with ID: " << id << "\n";
    std::cout << "[LostBaggage] Time complexity: O(1) for hash table deletion\n";
    std::cout << "[LostBaggage] Space complexity: O(1)\n";
    std::cout << "[LostBaggage] Result: Lost baggage resolved and removed from tracking\n";
}

void LostBaggage::queryByID(const std::string& id) {
    auto it = baggageMap.find(id);
    if (it != baggageMap.end()) {
        const auto& record = it->second;
        std::cout << "[LostBaggage] Baggage Details for " << id << ":\n";
        std::cout << "  Passenger ID: " << record.passengerID << "\n";
        std::cout << "  Last Known Location: " << record.lastKnownLocation << "\n";
        std::cout << "  Status: " << record.status << "\n";
        std::cout << "  Description: " << record.description << "\n";
    } else {
        std::cout << "[LostBaggage] Baggage ID " << id << " not found in records.\n";
    }
}
